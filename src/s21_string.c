#include "s21_string.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>

static char error_buffer[128];

#if !defined(__APPLE__) && !defined(__MACH__)
static const char *s21_errors_linux[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error",
};

#endif

#if defined(__APPLE__) || defined(__MACH__)
static const char *s21_errors_mac[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "Multihop attempted",
    "No message available on STREAM",
    "Link has been severed",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full",
};
#endif

#if defined(__APPLE__) || defined(__MACH__)
#define S21_ERRLIST s21_errors_mac
#else
#define S21_ERRLIST s21_errors_linux
#endif

#define S21_ERRLIST_SIZE (sizeof(S21_ERRLIST) / sizeof(S21_ERRLIST[0]))

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  while (str[len] != '\0') {
    len++;
  }

  return len;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  unsigned char value = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = value;
  }

  return str;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  int result = 0;

  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if (s1[i] != s2[i]) {
      result = s1[i] - s2[i];
    }
  }

  return result;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  void *result = S21_NULL;

  for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
    if (ptr[i] == (unsigned char)c) {
      result = (void *)(ptr + i);
    }
  }

  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }

  dest[dest_len + i] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;

  while (*str != '\0' && result == S21_NULL) {
    if (*str == (char)c) {
      result = (char *)str;
    }
    str++;
  }

  if (result == S21_NULL && (char)c == '\0') {
    result = (char *)str;
  }

  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;

  while (i < n && result == 0) {
    unsigned char c1 = (unsigned char)str1[i];
    unsigned char c2 = (unsigned char)str2[i];

    if (c1 != c2) {
      result = c1 - c2;
    } else if (c1 == '\0') {
      break;
    }

    i++;
  }

  return result;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;

  while (str1[count] != '\0') {
    s21_size_t j = 0;
    int found = 0;

    while (str2[j] != '\0' && !found) {
      if (str1[count] == str2[j]) {
        found = 1;
      }
      j++;
    }

    if (found) {
      break;
    }

    count++;
  }

  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;

  while (*str1 != '\0' && result == S21_NULL) {
    const char *tmp = str2;

    while (*tmp != '\0' && result == S21_NULL) {
      if (*str1 == *tmp) {
        result = (char *)str1;
      }
      tmp++;
    }

    str1++;
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      result = (char *)str;
    }
    str++;
  }

  if ((char)c == '\0') {
    result = (char *)str;
  }

  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    while (*haystack != '\0' && result == S21_NULL) {
      s21_size_t i = 0;

      while (needle[i] != '\0' && haystack[i] == needle[i]) {
        i++;
      }

      if (needle[i] == '\0') {
        result = (char *)haystack;
      }

      haystack++;
    }
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next = S21_NULL;

  if (str != S21_NULL) {
    next = str;
  }

  if (next == S21_NULL) {
    return S21_NULL;
  }

  while (*next != '\0' && s21_strchr(delim, *next) != S21_NULL) {
    next++;
  }

  if (*next == '\0') {
    next = S21_NULL;
    return S21_NULL;
  }

  char *token = next;

  while (*next != '\0' && s21_strchr(delim, *next) == S21_NULL) {
    next++;
  }

  if (*next != '\0') {
    *next = '\0';
    next++;
  } else {
    next = S21_NULL;
  }

  return token;
}

static void s21_write_unknown_error(int errnum, char *out) {
  const char *prefix = "Unknown error ";
  int pos = 0;

  while (prefix[pos] != '\0') {
    out[pos] = prefix[pos];
    pos++;
  }

  unsigned int mag;

  if (errnum < 0) {
    out[pos++] = '-';
    mag = (unsigned int)(-(errnum + 1)) + 1u;
  } else {
    mag = (unsigned int)errnum;
  }

  char digits[16];
  int n = 0;

  if (mag == 0) {
    digits[n++] = '0';
  } else {
    while (mag > 0) {
      digits[n++] = (char)('0' + mag % 10);
      mag /= 10;
    }
  }

  while (n > 0) {
    out[pos++] = digits[--n];
  }

  out[pos] = '\0';
}

char *s21_strerror(int errnum) {
  char *result = error_buffer;

  if (errnum >= 0 && errnum < (int)S21_ERRLIST_SIZE) {
    result = (char *)S21_ERRLIST[errnum];
  } else {
    s21_write_unknown_error(errnum, error_buffer);
  }

  return result;
}

static int s21_strlen_local(const char *str) {
  int len = 0;

  while (str[len]) {
    len++;
  }

  return len;
}

static void s21_utoa_base(unsigned long long value, char *buffer, int base,
                          int upper) {
  const char *digits = upper ? "0123456789ABCDEF" : "0123456789abcdef";
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

static void s21_shift_right(char *buffer, int count, char fill) {
  int len = s21_strlen_local(buffer);

  for (int i = len; i >= 0; i--) {
    buffer[i + count] = buffer[i];
  }

  for (int i = 0; i < count; i++) {
    buffer[i] = fill;
  }
}

static void s21_apply_int_precision(char *digits, int precision) {
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

static void s21_strip_trailing_zeros(char *s) {
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

static int s21_ld_is_neg(long double v) {
  return v < 0 || (v == 0 && (1.0L / v) < 0);
}

#define S21_MAX_INT_DIGITS (LDBL_MAX_10_EXP + 8)

/* Writes the base-10 digits of a nonnegative integral long double into
 * `digits` without ever casting through a fixed-width integer type, so
 * magnitudes beyond ULLONG_MAX (~1.8e19) don't hit undefined behavior on
 * the cast. Returns the digit count. */
static int s21_extract_int_digits(long double ip, char *digits) {
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
static void s21_extract_frac_digits(long double *frac, char *digits,
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
static int s21_digits_add_one(char *digits, int len) {
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

static void s21_build_fixed(long double v, int precision, int hash, char *out) {
  long double ip_ld = floorl(v);
  long double frac = v - ip_ld;

  char ip_digits[S21_MAX_INT_DIGITS + 2];
  int ip_n = s21_extract_int_digits(ip_ld, ip_digits);

  char *frac_digits = malloc((size_t)precision + 2);
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

static void s21_build_sci(long double v, int precision, char expchar, int hash,
                          char *out) {
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

  char *frac_digits = malloc((size_t)precision + 2);
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

static void s21_build_g(long double v, int precision, int upper, int hash,
                        char *out) {
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

static int s21_build_num_field(char *out, const char *sign, const char *prefix,
                               const char *digits, const s21_format *f,
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

static void s21_parse_format(const char **format, s21_format *f) {
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

static int s21_format_signed(char *out, va_list args, s21_format *f) {
  long long value = s21_read_signed(args, f->length);
  int neg = value < 0;
  unsigned long long mag;

  if (neg) {
    mag = (unsigned long long)(-(value + 1)) + 1ULL;
  } else {
    mag = (unsigned long long)value;
  }

  size_t dcap = (f->precision > 0 ? (size_t)f->precision : 0) + 64;
  char *digits = malloc(dcap);
  if (digits == S21_NULL) {
    return 0;
  }
  s21_utoa_base(mag, digits, 10, 0);
  s21_apply_int_precision(digits, f->precision);

  const char *sign = neg ? "-" : (f->plus ? "+" : (f->space ? " " : ""));

  int written = s21_build_num_field(out, sign, "", digits, f, f->precision < 0);
  free(digits);
  return written;
}

static int s21_format_unsigned(char *out, va_list args, s21_format *f) {
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
  char *digits = malloc(dcap);
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

static int s21_format_pointer(char *out, va_list args, s21_format *f) {
  void *ptr = va_arg(args, void *);

  if (ptr == S21_NULL) {
    return s21_build_num_field(out, "", "", "(nil)", f, 0);
  }

  char digits[1024];
  s21_utoa_base((unsigned long long)(s21_size_t)ptr, digits, 16, 0);

  return s21_build_num_field(out, "", "0x", digits, f, f->precision < 0);
}

static int s21_format_float(char *out, va_list args, s21_format *f) {
  long double value;
  int is_nan;
  int is_inf;

  if (f->length == 'L') {
    value = va_arg(args, long double);
    is_nan = isnan(value);
    is_inf = isinf(value);
  } else {
    /* Classify on the narrower double *before* widening: some platforms'
     * isnan/isinf are less reliable on long double than on double. */
    double dvalue = va_arg(args, double);
    is_nan = isnan(dvalue);
    is_inf = isinf(dvalue);
    value = dvalue;
  }

  if (is_nan || is_inf) {
    int neg = signbit(value);
    int upper_word = (f->specifier == 'E' || f->specifier == 'G');
    const char *word;

    if (is_nan) {
      word = upper_word ? "NAN" : "nan";
    } else {
      word = upper_word ? "INF" : "inf";
    }

    const char *sign = neg ? "-" : (f->plus ? "+" : (f->space ? " " : ""));

    return s21_build_num_field(out, sign, "", word, f, 0);
  }

  int neg = s21_ld_is_neg(value);
  long double mag = neg ? -value : value;
  int prec = f->precision < 0 ? 6 : f->precision;

  size_t dcap = (prec > 0 ? (size_t)prec : 0) + S21_MAX_INT_DIGITS + 64;
  char *digits = malloc(dcap);
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

  const char *sign = neg ? "-" : (f->plus ? "+" : (f->space ? " " : ""));

  int written = s21_build_num_field(out, sign, "", digits, f, !f->minus);
  free(digits);
  return written;
}

static char *s21_format_char(char *str, va_list args, s21_format *f) {
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

static char *s21_format_string(char *str, va_list args, s21_format *f) {
  char *src = va_arg(args, char *);

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

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *start = str;

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
    /* f/e/g/G can format long double magnitudes with thousands of integer
     * digits (see S21_MAX_INT_DIGITS); this buffer has to be large enough
     * to hold that, not just width/precision. */
    size_t float_cap =
        (spec == 'f' || spec == 'e' || spec == 'E' || spec == 'g' ||
         spec == 'G')
            ? S21_MAX_INT_DIGITS
            : 0;
    char *out = malloc(width_cap + prec_cap + float_cap + 128);
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
