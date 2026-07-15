#include <math.h>
#include <stdlib.h>

#include "s21_string_internal.h"

int s21_strlen_local(const char* str) {
  int len = 0;

  while (str[len]) {
    len++;
  }

  return len;
}

void s21_shift_right(char* buffer, int count, char fill) {
  int len = s21_strlen_local(buffer);

  for (int i = len; i >= 0; i--) {
    buffer[i + count] = buffer[i];
  }

  for (int i = 0; i < count; i++) {
    buffer[i] = fill;
  }
}

static void s21_strip_trailing_zeros(char* s) {
  int has_dot = 0;
  int epos = -1;

  for (int i = 0; s[i]; i++) {
    if (s[i] == '.') {
      has_dot = 1;
    }
    if (s[i] == 'e' || s[i] == 'E') {
      epos = i;
      break;
    }
  }

  if (!has_dot) {
    return;
  }

  int end = (epos >= 0) ? epos : s21_strlen_local(s);
  int i = end - 1;

  while (i >= 0 && s[i] == '0') {
    i--;
  }

  if (i >= 0 && s[i] == '.') {
    i--;
  }

  int w = i + 1;

  if (epos >= 0) {
    int j = epos;

    while (s[j]) {
      s[w++] = s[j++];
    }
  }

  s[w] = '\0';
}

/* Writes the base-10 digits of a nonnegative integral long double into
 * `digits` without ever casting through a fixed-width integer type, so
 * magnitudes beyond ULLONG_MAX (~1.8e19) don't hit undefined behavior on
 * the cast. Returns the digit count. */
static int s21_extract_int_digits(long double ip, char* digits) {
  int n = 0;

  if (ip == 0.0L) {
    digits[n++] = '0';
  } else {
    char tmp[S21_MAX_INT_DIGITS];
    int tn = 0;

    while (ip >= 1.0L && tn < S21_MAX_INT_DIGITS) {
      long double q = floorl(ip / 10.0L);
      int d = (int)(ip - q * 10.0L);

      if (d < 0) {
        d = 0;
      }
      if (d > 9) {
        d = 9;
      }

      tmp[tn++] = (char)('0' + d);
      ip = q;
    }

    while (tn > 0) {
      digits[n++] = tmp[--tn];
    }
  }

  digits[n] = '\0';
  return n;
}

/* Extracts `count` base-10 digits from a fractional value 0 <= *frac < 1,
 * consuming *frac in place so the caller can inspect what (if anything)
 * remains after the requested digits for exact-tie detection. */

static void s21_extract_frac_digits(long double* frac, char* digits,
                                    int count) {
  for (int i = 0; i < count; i++) {
    *frac *= 10.0L;
    int d = (int)(*frac);

    if (d < 0) {
      d = 0;
    }
    if (d > 9) {
      d = 9;
    }

    digits[i] = (char)('0' + d);
    *frac -= d;
  }
}

/* Round-half-to-even decision for the digit immediately after the last
 * kept one: `next_digit` is that digit's value, `has_more` says whether
 * any nonzero digits follow it, and `last_kept_digit` is the digit that
 * would need bumping to break a tie. */

static int s21_round_up_half_even(int next_digit, int has_more,
                                  int last_kept_digit) {
  int round_up;

  if (next_digit > 5) {
    round_up = 1;
  } else if (next_digit < 5) {
    round_up = 0;
  } else if (has_more) {
    round_up = 1;
  } else {
    round_up = (last_kept_digit % 2) == 1;
  }

  return round_up;
}

/* Adds 1 to a most-significant-first decimal digit string in place.
 * Returns 1 if the carry propagated past the leading digit (e.g. "99"
 * becomes "00" with a carry out that the caller must prepend a '1' for). */

static int s21_digits_add_one(char* digits, int len) {
  int carry = 1;

  for (int i = len - 1; i >= 0 && carry; i--) {
    int d = (digits[i] - '0') + 1;

    if (d == 10) {
      digits[i] = '0';
    } else {
      digits[i] = (char)('0' + d);
      carry = 0;
    }
  }

  return carry;
}

void s21_build_fixed(long double v, int precision, int hash, char* out) {
  long double ip_ld = floorl(v);
  long double frac = v - ip_ld;

  char ip_digits[S21_MAX_INT_DIGITS + 2];
  int ip_n = s21_extract_int_digits(ip_ld, ip_digits);

  char* frac_digits = malloc((size_t)precision + 2);
  if (frac_digits == S21_NULL) {
    out[0] = '\0';
    return;
  }

  s21_extract_frac_digits(&frac, frac_digits, precision + 1);

  int guard = frac_digits[precision] - '0';
  int has_more = frac > 0.0L;
  int last_kept = (precision > 0) ? (frac_digits[precision - 1] - '0')
                                  : (ip_digits[ip_n - 1] - '0');

  if (s21_round_up_half_even(guard, has_more, last_kept)) {
    int carry =
        (precision > 0) ? s21_digits_add_one(frac_digits, precision) : 1;

    if (carry && s21_digits_add_one(ip_digits, ip_n)) {
      s21_shift_right(ip_digits, 1, '1');
      ip_n++;
    }
  }

  int pos = 0;

  for (int i = 0; i < ip_n; i++) {
    out[pos++] = ip_digits[i];
  }

  if (precision > 0) {
    out[pos++] = '.';

    for (int i = 0; i < precision; i++) {
      out[pos++] = frac_digits[i];
    }
  } else if (hash) {
    out[pos++] = '.';
  }

  out[pos] = '\0';
  free(frac_digits);
}

void s21_build_sci(long double v, int precision, char expchar, int hash,
                   char* out) {
  int exp = 0;

  if (v != 0) {
    int guard = S21_MAX_INT_DIGITS;

    while (v >= 10.0L && guard-- > 0) {
      v /= 10.0L;
      exp++;
    }
    guard = S21_MAX_INT_DIGITS;
    while (v < 1.0L && guard-- > 0) {
      v *= 10.0L;
      exp--;
    }
  }

  int lead = (int)v;

  if (lead < 0) {
    lead = 0;
  }
  if (lead > 9) {
    lead = 9;
  }

  long double frac = v - lead;

  char* frac_digits = malloc((size_t)precision + 2);
  if (frac_digits == S21_NULL) {
    out[0] = '\0';
    return;
  }

  s21_extract_frac_digits(&frac, frac_digits, precision + 1);

  int guard = frac_digits[precision] - '0';
  int has_more = frac > 0.0L;
  int last_kept = (precision > 0) ? (frac_digits[precision - 1] - '0') : lead;

  if (s21_round_up_half_even(guard, has_more, last_kept)) {
    int carry =
        (precision > 0) ? s21_digits_add_one(frac_digits, precision) : 1;

    if (carry) {
      lead++;
      if (lead == 10) {
        lead = 1;
        exp++;
      }
    }
  }

  int pos = 0;
  out[pos++] = (char)('0' + lead);

  if (precision > 0) {
    out[pos++] = '.';

    for (int i = 0; i < precision; i++) {
      out[pos++] = frac_digits[i];
    }
  } else if (hash) {
    out[pos++] = '.';
  }

  free(frac_digits);

  out[pos++] = expchar;

  if (exp < 0) {
    out[pos++] = '-';
    exp = -exp;
  } else {
    out[pos++] = '+';
  }

  char edig[16];
  int en = 0;

  if (exp == 0) {
    edig[en++] = '0';
  } else {
    while (exp > 0) {
      edig[en++] = (char)('0' + exp % 10);
      exp /= 10;
    }
  }

  while (en < 2) {
    edig[en++] = '0';
  }

  while (en > 0) {
    out[pos++] = edig[--en];
  }

  out[pos] = '\0';
}

void s21_build_g(long double v, int precision, int upper, int hash, char* out) {
  if (precision == 0) {
    precision = 1;
  }

  int exp = 0;
  long double m = v;

  if (m != 0) {
    int guard = S21_MAX_INT_DIGITS;

    while (m >= 10.0L && guard-- > 0) {
      m /= 10.0L;
      exp++;
    }
    guard = S21_MAX_INT_DIGITS;
    while (m < 1.0L && guard-- > 0) {
      m *= 10.0L;
      exp--;
    }
  }

  long double rounding = 0.5L;

  for (int i = 0; i < precision - 1; i++) {
    rounding /= 10.0L;
  }

  m += rounding;

  if (m >= 10.0L) {
    m /= 10.0L;
    exp++;
  }

  if (exp >= -4 && exp < precision) {
    s21_build_fixed(v, precision - 1 - exp, hash, out);
  } else {
    s21_build_sci(v, precision - 1, upper ? 'E' : 'e', hash, out);
  }

  if (!hash) {
    s21_strip_trailing_zeros(out);
  }
}
