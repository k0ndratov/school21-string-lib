#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  s21_size_t len = 0;

  while (str[len] != '\0') {
    len++;
  }

  return len;
}

void* s21_memset(void* str, int c, s21_size_t n) {
  unsigned char* ptr = (unsigned char*)str;
  unsigned char value = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = value;
  }

  return str;
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  unsigned char* d = (unsigned char*)dest;
  const unsigned char* s = (const unsigned char*)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  const unsigned char* s1 = (const unsigned char*)str1;
  const unsigned char* s2 = (const unsigned char*)str2;

  int result = 0;

  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if (s1[i] != s2[i]) {
      result = s1[i] - s2[i];
    }
  }

  return result;
}

void* s21_memchr(const void* str, int c, s21_size_t n) {
  const unsigned char* ptr = (const unsigned char*)str;
  void* result = S21_NULL;

  for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
    if (ptr[i] == (unsigned char)c) {
      result = (void*)(ptr + i);
    }
  }

  return result;
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
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

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }

  dest[dest_len + i] = '\0';

  return dest;
}

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;

  while (*str != '\0' && result == S21_NULL) {
    if (*str == (char)c) {
      result = (char*)str;
    }
    str++;
  }

  if (result == S21_NULL && (char)c == '\0') {
    result = (char*)str;
  }

  return result;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
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

s21_size_t s21_strcspn(const char* str1, const char* str2) {
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

char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;

  while (*str1 != '\0' && result == S21_NULL) {
    const char* tmp = str2;

    while (*tmp != '\0' && result == S21_NULL) {
      if (*str1 == *tmp) {
        result = (char*)str1;
      }
      tmp++;
    }

    str1++;
  }

  return result;
}

char* s21_strrchr(const char* str, int c) {
  char* result = S21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      result = (char*)str;
    }
    str++;
  }

  if ((char)c == '\0') {
    result = (char*)str;
  }

  return result;
}

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;

  if (*needle == '\0') {
    result = (char*)haystack;
  } else {
    while (*haystack != '\0' && result == S21_NULL) {
      s21_size_t i = 0;

      while (needle[i] != '\0' && haystack[i] == needle[i]) {
        i++;
      }

      if (needle[i] == '\0') {
        result = (char*)haystack;
      }

      haystack++;
    }
  }

  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* next = S21_NULL;

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

  char* token = next;

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
