#include <math.h>
#include <stdlib.h>

#include "s21_string_internal.h"

// Превращает число в текстовые цифры, используя заданную систему
// счисления (10, 16...).
static void s21_utoa_base(unsigned long long value, char* buffer, int base,
                          int upper) {
  const char* digits = upper ? "0123456789ABCDEF" : "0123456789abcdef";
  char temp[64];
  int n = 0;

  if (value == 0) {
    temp[n++] = '0';
  } else {
    while (value > 0) {
      temp[n++] = digits[value % base];
      value /= base;
    }
  }

  int pos = 0;

  while (n > 0) {
    buffer[pos++] = temp[--n];
  }

  buffer[pos] = '\0';
}

// Добавляет нули перед цифрами, если числу нужно больше цифр (это и
// есть «точность» для целых чисел вроде %d).
static void s21_apply_int_precision(char* digits, int precision) {
  if (precision < 0) {
    return;
  }

  int len = s21_strlen_local(digits);

  if (precision == 0 && len == 1 && digits[0] == '0') {
    digits[0] = '\0';
    return;
  }

  if (len < precision) {
    s21_shift_right(digits, precision - len, '0');
  }
}

// Проверяет, отрицательное ли v. Также учитывает особый случай
// отрицательного нуля.
static int s21_ld_is_neg(long double v) {
  return v < 0 || (v == 0 && (1.0L / v) < 0);
}

// Собирает вместе знак, префикс и цифры, добавляя пробелы или нули,
// чтобы результат соответствовал нужной ширине.
static int s21_build_num_field(char* out, const char* sign, const char* prefix,
                               const char* digits, const s21_format* f,
                               int zero_ok) {
  int slen = s21_strlen_local(sign);
  int plen = s21_strlen_local(prefix);
  int dlen = s21_strlen_local(digits);
  int content = slen + plen + dlen;
  int pad = f->width - content;

  if (pad < 0) {
    pad = 0;
  }

  int use_zero = f->zero && zero_ok && !f->minus;
  int pos = 0;

  if (!f->minus && !use_zero) {
    for (int i = 0; i < pad; i++) {
      out[pos++] = ' ';
    }
  }

  for (int i = 0; i < slen; i++) {
    out[pos++] = sign[i];
  }
  for (int i = 0; i < plen; i++) {
    out[pos++] = prefix[i];
  }

  if (use_zero) {
    for (int i = 0; i < pad; i++) {
      out[pos++] = '0';
    }
  }

  for (int i = 0; i < dlen; i++) {
    out[pos++] = digits[i];
  }

  if (f->minus) {
    for (int i = 0; i < pad; i++) {
      out[pos++] = ' ';
    }
  }

  return pos;
}

// Считывает флаги, ширину, точность и букву типа из формата %
// (например, часть «05.2f» в «%05.2f»).
static void s21_parse_format(const char** format, s21_format* f) {
  f->minus = 0;
  f->plus = 0;
  f->space = 0;
  f->hash = 0;
  f->zero = 0;
  f->width = 0;
  f->precision = -1;
  f->width_star = 0;
  f->prec_star = 0;
  f->length = '\0';
  f->specifier = '\0';

  int reading = 1;

  while (reading) {
    switch (**format) {
      case '-':
        f->minus = 1;
        break;
      case '+':
        f->plus = 1;
        break;
      case ' ':
        f->space = 1;
        break;
      case '#':
        f->hash = 1;
        break;
      case '0':
        f->zero = 1;
        break;
      default:
        reading = 0;
        break;
    }

    if (reading) {
      (*format)++;
    }
  }

  if (**format == '*') {
    f->width_star = 1;
    (*format)++;
  } else {
    while (**format >= '0' && **format <= '9') {
      f->width = f->width * 10 + (**format - '0');
      (*format)++;
    }
  }

  if (**format == '.') {
    (*format)++;
    f->precision = 0;

    if (**format == '*') {
      f->prec_star = 1;
      (*format)++;
    } else {
      while (**format >= '0' && **format <= '9') {
        f->precision = f->precision * 10 + (**format - '0');
        (*format)++;
      }
    }
  }

  if (**format == 'h' || **format == 'l' || **format == 'L') {
    f->length = **format;
    (*format)++;
  }

  f->specifier = **format;
}

// Считывает знаковый числовой аргумент из списка переменных аргументов,
// используя нужный размер (short, int или long) по букве длины формата.
static long long s21_read_signed(va_list args, char length) {
  long long value;

  if (length == 'h') {
    value = (short)va_arg(args, int);
  } else if (length == 'l') {
    value = va_arg(args, long);
  } else {
    value = va_arg(args, int);
  }

  return value;
}

// То же самое, что s21_read_signed, но для беззнаковых чисел.
static unsigned long long s21_read_unsigned(va_list args, char length) {
  unsigned long long value;

  if (length == 'h') {
    value = (unsigned short)va_arg(args, unsigned int);
  } else if (length == 'l') {
    value = va_arg(args, unsigned long);
  } else {
    value = va_arg(args, unsigned int);
  }

  return value;
}

// Превращает аргумент %d или %i в текст.
static int s21_format_signed(char* out, va_list args, s21_format* f) {
  long long value = s21_read_signed(args, f->length);
  int neg = value < 0;
  unsigned long long mag;

  if (neg) {
    mag = (unsigned long long)(-(value + 1)) + 1ULL;
  } else {
    mag = (unsigned long long)value;
  }

  size_t dcap = (f->precision > 0 ? (size_t)f->precision : 0) + 64;
  char* digits = malloc(dcap);
  if (digits == S21_NULL) {
    return 0;
  }
  s21_utoa_base(mag, digits, 10, 0);
  s21_apply_int_precision(digits, f->precision);

  const char* sign = neg ? "-" : (f->plus ? "+" : (f->space ? " " : ""));

  int written = s21_build_num_field(out, sign, "", digits, f, f->precision < 0);
  free(digits);
  return written;
}

// Превращает аргумент %u, %o, %x или %X в текст.
static int s21_format_unsigned(char* out, va_list args, s21_format* f) {
  unsigned long long value = s21_read_unsigned(args, f->length);
  int base = 10;
  int upper = 0;
  char prefix[3] = "";

  if (f->specifier == 'o') {
    base = 8;
  } else if (f->specifier == 'x' || f->specifier == 'X') {
    base = 16;
    upper = (f->specifier == 'X');
  }

  size_t dcap = (f->precision > 0 ? (size_t)f->precision : 0) + 64;
  char* digits = malloc(dcap);
  if (digits == S21_NULL) {
    return 0;
  }
  s21_utoa_base(value, digits, base, upper);
  s21_apply_int_precision(digits, f->precision);

  if (f->hash && f->specifier == 'o' && digits[0] != '0') {
    s21_shift_right(digits, 1, '0');
  } else if (f->hash && (f->specifier == 'x' || f->specifier == 'X') &&
             value != 0) {
    prefix[0] = '0';
    prefix[1] = upper ? 'X' : 'x';
    prefix[2] = '\0';
  }

  int written =
      s21_build_num_field(out, "", prefix, digits, f, f->precision < 0);
  free(digits);
  return written;
}

// Превращает аргумент %p (адрес указателя) в текст.
static int s21_format_pointer(char* out, va_list args, s21_format* f) {
  void* ptr = va_arg(args, void*);

  if (ptr == S21_NULL) {
    return s21_build_num_field(out, "", "", "(nil)", f, 0);
  }

  char digits[1024];
  s21_utoa_base((unsigned long long)(s21_size_t)ptr, digits, 16, 0);

  return s21_build_num_field(out, "", "0x", digits, f, f->precision < 0);
}

// Превращает аргумент %f, %e, %g в текст. Также обрабатывает особые
// значения вроде бесконечности и «не число».
static int s21_format_float(char* out, va_list args, s21_format* f) {
  long double value;
  int is_nan;
  int is_inf;

  if (f->length == 'L') {
    value = va_arg(args, long double);
    is_nan = isnan(value);
    is_inf = isinf(value);
  } else {
    double dvalue = va_arg(args, double);
    is_nan = isnan(dvalue);
    is_inf = isinf(dvalue);
    value = dvalue;
  }

  if (is_nan || is_inf) {
    int neg = signbit(value);
    int upper_word = (f->specifier == 'E' || f->specifier == 'G');
    const char* word;

    if (is_nan) {
      word = upper_word ? "NAN" : "nan";
    } else {
      word = upper_word ? "INF" : "inf";
    }

    const char* sign = neg ? "-" : (f->plus ? "+" : (f->space ? " " : ""));

    return s21_build_num_field(out, sign, "", word, f, 0);
  }

  int neg = s21_ld_is_neg(value);
  long double mag = neg ? -value : value;
  int prec = f->precision < 0 ? 6 : f->precision;

  size_t dcap = (prec > 0 ? (size_t)prec : 0) + S21_MAX_INT_DIGITS + 64;
  char* digits = malloc(dcap);
  if (digits == S21_NULL) {
    return 0;
  }

  if (f->specifier == 'f') {
    s21_build_fixed(mag, prec, f->hash, digits);
  } else if (f->specifier == 'e' || f->specifier == 'E') {
    s21_build_sci(mag, prec, f->specifier == 'E' ? 'E' : 'e', f->hash, digits);
  } else {
    s21_build_g(mag, prec, f->specifier == 'G', f->hash, digits);
  }

  const char* sign = neg ? "-" : (f->plus ? "+" : (f->space ? " " : ""));

  int written = s21_build_num_field(out, sign, "", digits, f, !f->minus);
  free(digits);
  return written;
}

// Превращает аргумент %c в текст, добавляя пробелы для нужной ширины.
static char* s21_format_char(char* str, va_list args, s21_format* f) {
  char ch = (char)va_arg(args, int);
  int len = 1;

  while (!f->minus && len < f->width) {
    *str++ = ' ';
    len++;
  }

  *str++ = ch;

  while (f->minus && len < f->width) {
    *str++ = ' ';
    len++;
  }

  return str;
}

// Превращает аргумент %s в текст, применяя правила ширины и точности.
static char* s21_format_string(char* str, va_list args, s21_format* f) {
  char* src = va_arg(args, char*);

  if (src == S21_NULL) {
    src = "(null)";
  }

  int len = s21_strlen_local(src);

  if (f->precision >= 0 && f->precision < len) {
    len = f->precision;
  }

  int pad = f->width - len;

  if (pad < 0) {
    pad = 0;
  }

  while (!f->minus && pad > 0) {
    *str++ = ' ';
    pad--;
  }

  for (int i = 0; i < len; i++) {
    *str++ = src[i];
  }

  while (f->minus && pad > 0) {
    *str++ = ' ';
    pad--;
  }

  return str;
}

// Формирует строку по формату в str, точно как стандартная функция
// sprintf. Это главная функция этого файла.
int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  char* start = str;

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    }

    format++;

    s21_format fmt;
    s21_parse_format(&format, &fmt);

    if (fmt.width_star) {
      int w = va_arg(args, int);

      if (w < 0) {
        fmt.minus = 1;
        fmt.width = -w;
      } else {
        fmt.width = w;
      }
    }

    if (fmt.prec_star) {
      int p = va_arg(args, int);
      fmt.precision = (p < 0) ? -1 : p;
    }

    char spec = fmt.specifier;
    size_t width_cap = fmt.width > 0 ? (size_t)fmt.width : 0;
    size_t prec_cap = fmt.precision > 0 ? (size_t)fmt.precision : 0;
    size_t float_cap = (spec == 'f' || spec == 'e' || spec == 'E' ||
                        spec == 'g' || spec == 'G')
                           ? S21_MAX_INT_DIGITS
                           : 0;
    char* out = malloc(width_cap + prec_cap + float_cap + 128);
    if (out == S21_NULL) {
      va_end(args);
      return -1;
    }
    int wrote = 0;

    if (spec == '%') {
      *str++ = '%';
    } else if (spec == 'c') {
      str = s21_format_char(str, args, &fmt);
    } else if (spec == 's') {
      str = s21_format_string(str, args, &fmt);
    } else if (spec == 'd' || spec == 'i') {
      wrote = s21_format_signed(out, args, &fmt);
    } else if (spec == 'u') {
      wrote = s21_format_unsigned(out, args, &fmt);
    } else if (spec == 'o' || spec == 'x' || spec == 'X') {
      wrote = s21_format_unsigned(out, args, &fmt);
    } else if (spec == 'p') {
      wrote = s21_format_pointer(out, args, &fmt);
    } else if (spec == 'f' || spec == 'e' || spec == 'E' || spec == 'g' ||
               spec == 'G') {
      wrote = s21_format_float(out, args, &fmt);
    } else {
      *str++ = '%';
      if (spec) {
        *str++ = spec;
      }
    }

    for (int i = 0; i < wrote; i++) {
      *str++ = out[i];
    }

    free(out);

    if (spec) {
      format++;
    }
  }

  *str = '\0';

  va_end(args);

  return (int)(str - start);
}
