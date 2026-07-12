#include "s21_string.h"

#include <stdio.h>

static char error_buffer[128];

static const char *linux_errors[] = {
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

#define S21_ERRLIST_SIZE (sizeof(linux_errors) / sizeof(linux_errors[0]))

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

char *s21_strerror(int errnum) {
  char *result = error_buffer;

  if (errnum >= 0 && errnum < (int)S21_ERRLIST_SIZE) {
    result = (char *)linux_errors[errnum];
  } else {
    sprintf(error_buffer, "Unknown error %d", errnum);
  }

  return result;
}

static void s21_int_to_str(int value, char *buffer) {
  char temp[32];
  int i = 0;
  int negative = 0;

  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }

  if (value < 0) {
    negative = 1;
    value = -value;
  }

  while (value > 0) {
    temp[i++] = (value % 10) + '0';
    value /= 10;
  }

  if (negative) {
    temp[i++] = '-';
  }

  int j = 0;

  while (i > 0) {
    buffer[j++] = temp[--i];
  }

  buffer[j] = '\0';
}

static void s21_uint_to_str(unsigned int value, char *buffer) {
  char temp[32];
  int i = 0;

  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }

  while (value > 0) {
    temp[i++] = (char)(value % 10 + '0');
    value /= 10;
  }

  int j = 0;

  while (i > 0) {
    buffer[j++] = temp[--i];
  }

  buffer[j] = '\0';
}

static void s21_double_to_str(double value, char *buffer, int precision) {
  int negative = 0;

  if (value < 0) {
    negative = 1;
    value = -value;
  }

  if (precision < 0) {
    precision = 6;
  }

  int integer = (int)value;
  double fraction = value - integer;

  fraction += 0.0000005;

  char temp[64];
  s21_int_to_str(integer, temp);

  char *p = buffer;

  if (negative) {
    *p++ = '-';
  }

  char *q = temp;
  while (*q) {
    *p++ = *q++;
  }

  if (precision > 0) {
    *p++ = '.';

    for (int i = 0; i < precision; i++) {
      fraction *= 10;
      int digit = (int)fraction;
      *p++ = (char)(digit + '0');
      fraction -= digit;
    }
  }
  *p = '\0';
}

static void s21_parse_format(const char **format, s21_format *f) {
  f->minus = 0;
  f->plus = 0;
  f->space = 0;
  f->hash = 0;
  f->zero = 0;
  f->width = 0;
  f->precision = -1;
  f->length = '\0';
  f->specifier = '\0';

  while (**format == '-' || **format == '+' || **format == ' ') {
    if (**format == '-') {
      f->minus = 1;
    } else if (**format == '+') {
      f->plus = 1;
    } else if (**format == ' ') {
      f->space = 1;
    }

    (*format)++;
  }

  while (**format >= '0' && **format <= '9') {
    f->width = f->width * 10 + (**format - '0');
    (*format)++;
  }

  if (**format == '.') {
    (*format)++;

    f->precision = 0;

    while (**format >= '0' && **format <= '9') {
      f->precision = f->precision * 10 + (**format - '0');
      (*format)++;
    }
  }
  if (**format == 'h' || **format == 'l') {
    f->length = **format;
    (*format)++;
  }

  f->specifier = **format;
}

static int s21_strlen_local(const char *str) {
  int len = 0;

  while (str[len]) {
    len++;
  }

  return len;
}

static void s21_add_leading_zeros(char *buffer, int precision) {
  int negative = 0;
  int len = s21_strlen_local(buffer);

  if (buffer[0] == '-') {
    negative = 1;
    len--;
  }

  if (precision <= len) {
    return;
  }

  char temp[64];
  int pos = 0;

  if (negative) {
    temp[pos++] = '-';
  }

  for (int i = 0; i < precision - len; i++) {
    temp[pos++] = '0';
  }

  int start = negative;

  while (buffer[start]) {
    temp[pos++] = buffer[start++];
  }

  temp[pos] = '\0';

  int i = 0;
  while ((buffer[i] = temp[i]) != '\0') {
    i++;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *start = str;

  while (*format) {
    if (*format == '%') {
      format++;

      s21_format fmt;
      s21_parse_format(&format, &fmt);

      if (fmt.specifier == '%') {
        *str++ = '%';
        format++;

      } else if (fmt.specifier == 'c') {
        char buffer[2];

        buffer[0] = (char)va_arg(args, int);
        buffer[1] = '\0';

        int len = s21_strlen_local(buffer);

        while (!fmt.minus && len < fmt.width) {
          *str++ = ' ';
          len++;
        }

        *str++ = buffer[0];

        while (fmt.minus && len < fmt.width) {
          *str++ = ' ';
          len++;
        }

        format++;

      } else if (fmt.specifier == 's') {
        char *src = va_arg(args, char *);

        if (src == S21_NULL) {
          src = "(null)";
        }

        int len = s21_strlen_local(src);

        if (fmt.precision >= 0 && fmt.precision < len) {
          len = fmt.precision;
        }

        while (!fmt.minus && len < fmt.width) {
          *str++ = ' ';
          fmt.width--;
        }

        for (int i = 0; i < len; i++) {
          *str++ = src[i];
        }

        while (fmt.minus && len < fmt.width) {
          *str++ = ' ';
          fmt.width--;
        }

        format++;
      } else if (fmt.specifier == 'd') {
        long value;

        if (fmt.length == 'h') {
          value = (short)va_arg(args, int);
        } else if (fmt.length == 'l') {
          value = va_arg(args, long);
        } else {
          value = va_arg(args, int);
        }

        char buffer[32];
        s21_int_to_str((int)value, buffer);
        if (fmt.precision > 0) {
          s21_add_leading_zeros(buffer, fmt.precision);
        }

        int len = s21_strlen_local(buffer);

        if (fmt.plus && value >= 0) {
          len++;
        } else if (fmt.space && value >= 0) {
          len++;
        }

        while (!fmt.minus && len < fmt.width) {
          *str++ = ' ';
          len++;
        }

        if (fmt.plus && value >= 0) {
          *str++ = '+';
        } else if (fmt.space && value >= 0) {
          *str++ = ' ';
        }

        char *p = buffer;

        while (*p) {
          *str++ = *p++;
        }

        while (fmt.minus && len < fmt.width) {
          *str++ = ' ';
          len++;
        }

        format++;

      } else if (fmt.specifier == 'u') {
        unsigned int value = va_arg(args, unsigned int);

        char buffer[32];
        s21_uint_to_str(value, buffer);
        if (fmt.precision > 0) {
          s21_add_leading_zeros(buffer, fmt.precision);
        }

        char *p = buffer;

        while (*p) {
          *str++ = *p++;
        }

        format++;

      } else if (fmt.specifier == 'f') {
        double value = va_arg(args, double);

        char buffer[128];
        s21_double_to_str(value, buffer, fmt.precision);

        char *p = buffer;

        while (*p) {
          *str++ = *p++;
        }

        format++;
      }

    } else {
      *str++ = *format++;
    }
  }

  *str = '\0';

  va_end(args);

  return (int)(str - start);
}
