#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_string.h"

enum { LEN_NONE, LEN_H, LEN_HH, LEN_L, LEN_LL, LEN_CAPL };

enum { FAIL_NONE, FAIL_MATCH, FAIL_INPUT };

typedef struct {
  const char *base;
  const char *p;
  va_list *ap;
  int count;
  int fail;
} scan_t;

typedef struct {
  int suppress;
  int width;
  int length;
  char spec;
} fmt_t;

static int is_space(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' ||
         c == '\v';
}

static void skip_ws(scan_t *st) {
  while (*st->p && is_space(*st->p)) st->p++;
}

static int digit_val(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}

static void set_fail(scan_t *st) {
  st->fail = (*st->p == '\0') ? FAIL_INPUT : FAIL_MATCH;
}

static void store_int(scan_t *st, fmt_t *f, unsigned long long v,
                      int is_signed) {
  switch (f->length) {
    case LEN_HH:
      if (is_signed)
        *va_arg(*st->ap, signed char *) = (signed char)v;
      else
        *va_arg(*st->ap, unsigned char *) = (unsigned char)v;
      break;
    case LEN_H:
      if (is_signed)
        *va_arg(*st->ap, short *) = (short)v;
      else
        *va_arg(*st->ap, unsigned short *) = (unsigned short)v;
      break;
    case LEN_L:
      if (is_signed)
        *va_arg(*st->ap, long *) = (long)v;
      else
        *va_arg(*st->ap, unsigned long *) = (unsigned long)v;
      break;
    case LEN_LL:
      if (is_signed)
        *va_arg(*st->ap, long long *) = (long long)v;
      else
        *va_arg(*st->ap, unsigned long long *) = (unsigned long long)v;
      break;
    default:
      if (is_signed)
        *va_arg(*st->ap, int *) = (int)v;
      else
        *va_arg(*st->ap, unsigned int *) = (unsigned int)v;
      break;
  }
}

static void scan_int(scan_t *st, fmt_t *f, int base, int is_signed) {
  skip_ws(st);
  int w = f->width > 0 ? f->width : INT_MAX;
  const char *p = st->p;
  int used = 0;
  int neg = 0;
  unsigned long long val = 0;
  int digits = 0;

  if (used < w && (*p == '+' || *p == '-')) {
    neg = (*p == '-');
    p++;
    used++;
  }
  if (base == 16) {
    if (used + 1 < w && *p == '0' && (p[1] == 'x' || p[1] == 'X') &&
        digit_val(p[2]) >= 0) {
      p += 2;
      used += 2;
    }
  } else if (base == 0) {
    if (used + 1 < w && *p == '0' && (p[1] == 'x' || p[1] == 'X') &&
        digit_val(p[2]) >= 0) {
      p += 2;
      used += 2;
      base = 16;
    } else if (*p == '0') {
      base = 8;
    } else {
      base = 10;
    }
  }
  while (used < w) {
    int d = digit_val(*p);
    if (d < 0 || d >= base) break;
    val = val * (unsigned)base + (unsigned)d;
    p++;
    used++;
    digits++;
  }
  if (digits == 0) {
    set_fail(st);
    return;
  }
  st->p = p;
  if (!f->suppress) {
    unsigned long long out = neg ? (unsigned long long)(-(long long)val) : val;
    store_int(st, f, out, is_signed);
    st->count++;
  }
}

static void scan_ptr(scan_t *st, fmt_t *f) {
  skip_ws(st);
  int w = f->width > 0 ? f->width : INT_MAX;
  const char *p = st->p;
  int used = 0;
  unsigned long long val = 0;
  int digits = 0;

  if (used + 1 < w && *p == '0' && (p[1] == 'x' || p[1] == 'X') &&
      digit_val(p[2]) >= 0) {
    p += 2;
    used += 2;
  }
  while (used < w) {
    int d = digit_val(*p);
    if (d < 0 || d >= 16) break;
    val = val * 16u + (unsigned)d;
    p++;
    used++;
    digits++;
  }
  if (digits == 0) {
    set_fail(st);
    return;
  }
  st->p = p;
  if (!f->suppress) {
    *va_arg(*st->ap, void **) = (void *)(uintptr_t)val;
    st->count++;
  }
}

static void store_float(scan_t *st, fmt_t *f, const char *buf) {
  long double v = strtold(buf, NULL);
  switch (f->length) {
    case LEN_L:
      *va_arg(*st->ap, double *) = (double)v;
      break;
    case LEN_CAPL:
      *va_arg(*st->ap, long double *) = v;
      break;
    default:
      *va_arg(*st->ap, float *) = (float)v;
      break;
  }
}

static void scan_float(scan_t *st, fmt_t *f) {
  skip_ws(st);
  int w = f->width > 0 ? f->width : INT_MAX;
  const char *p = st->p;
  int used = 0;
  int digits = 0;
  char buf[512];
  const int cap = (int)sizeof(buf) - 1;
  int bi = 0;

  if (used < w && (*p == '+' || *p == '-')) {
    if (bi < cap) {
      buf[bi++] = *p;
    }
    p++;
    used++;
  }
  while (used < w && *p >= '0' && *p <= '9') {
    if (bi < cap) {
      buf[bi++] = *p;
    }
    p++;
    used++;
    digits++;
  }
  if (used < w && *p == '.') {
    if (bi < cap) {
      buf[bi++] = *p;
    }
    p++;
    used++;
    while (used < w && *p >= '0' && *p <= '9') {
      if (bi < cap) {
        buf[bi++] = *p;
      }
      p++;
      used++;
      digits++;
    }
  }
  if (digits > 0 && used < w && (*p == 'e' || *p == 'E')) {
    int save_bi = bi;
    const char *save_p = p;
    int save_used = used;
    if (bi < cap) {
      buf[bi++] = *p;
    }
    p++;
    used++;
    if (used < w && (*p == '+' || *p == '-')) {
      if (bi < cap) {
        buf[bi++] = *p;
      }
      p++;
      used++;
    }
    int edig = 0;
    while (used < w && *p >= '0' && *p <= '9') {
      if (bi < cap) {
        buf[bi++] = *p;
      }
      p++;
      used++;
      edig++;
    }
    if (edig == 0) {
      bi = save_bi;
      p = save_p;
      used = save_used;
    }
  }
  if (digits == 0) {
    set_fail(st);
    return;
  }
  buf[bi] = '\0';
  st->p = p;
  if (!f->suppress) {
    store_float(st, f, buf);
    st->count++;
  }
}

static void scan_str(scan_t *st, fmt_t *f) {
  skip_ws(st);
  if (*st->p == '\0') {
    st->fail = FAIL_INPUT;
    return;
  }
  int w = f->width > 0 ? f->width : INT_MAX;
  char *dst = f->suppress ? NULL : va_arg(*st->ap, char *);
  int n = 0;
  while (*st->p && !is_space(*st->p) && n < w) {
    if (dst) dst[n] = *st->p;
    st->p++;
    n++;
  }
  if (dst) dst[n] = '\0';
  if (!f->suppress) st->count++;
}

static void scan_char(scan_t *st, fmt_t *f) {
  if (*st->p == '\0') {
    st->fail = FAIL_INPUT;
    return;
  }
  int w = f->width > 0 ? f->width : 1;
  char *dst = f->suppress ? NULL : va_arg(*st->ap, char *);
  int n = 0;
  while (*st->p && n < w) {
    if (dst) dst[n] = *st->p;
    st->p++;
    n++;
  }
  if (!f->suppress) st->count++;
}

static void scan_n(scan_t *st, fmt_t *f) {
  int consumed = (int)(st->p - st->base);
  if (f->suppress) return;
  switch (f->length) {
    case LEN_HH:
      *va_arg(*st->ap, signed char *) = (signed char)consumed;
      break;
    case LEN_H:
      *va_arg(*st->ap, short *) = (short)consumed;
      break;
    case LEN_L:
      *va_arg(*st->ap, long *) = (long)consumed;
      break;
    case LEN_LL:
      *va_arg(*st->ap, long long *) = (long long)consumed;
      break;
    default:
      *va_arg(*st->ap, int *) = consumed;
      break;
  }
}

static void scan_percent(scan_t *st) {
  skip_ws(st);
  if (*st->p == '%') {
    st->p++;
  } else {
    set_fail(st);
  }
}

static void parse_fmt(const char **fp, fmt_t *f) {
  const char *p = *fp;
  f->suppress = 0;
  f->width = 0;
  f->length = LEN_NONE;
  f->spec = 0;
  if (*p == '*') {
    f->suppress = 1;
    p++;
  }
  while (*p >= '0' && *p <= '9') {
    f->width = f->width * 10 + (*p - '0');
    p++;
  }
  if (*p == 'h') {
    p++;
    if (*p == 'h') {
      f->length = LEN_HH;
      p++;
    } else {
      f->length = LEN_H;
    }
  } else if (*p == 'l') {
    p++;
    if (*p == 'l') {
      f->length = LEN_LL;
      p++;
    } else {
      f->length = LEN_L;
    }
  } else if (*p == 'L') {
    f->length = LEN_CAPL;
    p++;
  }
  f->spec = *p;
  if (*p) p++;
  *fp = p;
}

static void dispatch(scan_t *st, fmt_t *f) {
  switch (f->spec) {
    case 'd':
      scan_int(st, f, 10, 1);
      break;
    case 'i':
      scan_int(st, f, 0, 1);
      break;
    case 'u':
      scan_int(st, f, 10, 0);
      break;
    case 'o':
      scan_int(st, f, 8, 0);
      break;
    case 'x':
    case 'X':
      scan_int(st, f, 16, 0);
      break;
    case 'p':
      scan_ptr(st, f);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      scan_float(st, f);
      break;
    case 's':
      scan_str(st, f);
      break;
    case 'c':
      scan_char(st, f);
      break;
    case 'n':
      scan_n(st, f);
      break;
    case '%':
      scan_percent(st);
      break;
    default:
      st->fail = FAIL_MATCH;
      break;
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  scan_t st;
  st.base = str;
  st.p = str;
  st.count = 0;
  st.fail = FAIL_NONE;

  va_list ap;
  va_start(ap, format);
  st.ap = &ap;

  const char *fp = format;
  while (*fp && st.fail == FAIL_NONE) {
    if (is_space(*fp)) {
      while (is_space(*fp)) fp++;
      skip_ws(&st);
    } else if (*fp == '%') {
      fp++;
      fmt_t f;
      parse_fmt(&fp, &f);
      dispatch(&st, &f);
    } else {
      if (*st.p == *fp) {
        st.p++;
        fp++;
      } else {
        set_fail(&st);
      }
    }
  }

  va_end(ap);

  if (st.count == 0 && st.fail == FAIL_INPUT) return -1;
  return st.count;
}
