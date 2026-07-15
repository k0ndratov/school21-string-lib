#include <stdlib.h>

#include "s21_string.h"

// Считает, сколько символов в строке.
static s21_size_t local_strlen(const char *str) {
  s21_size_t len = 0;
  while (str[len] != '\0') len++;
  return len;
}

// Проверяет, является ли c заглавной буквой (A-Z).
static int is_upper_ascii(char c) { return c >= 'A' && c <= 'Z'; }

// Проверяет, является ли c строчной буквой (a-z).
static int is_lower_ascii(char c) { return c >= 'a' && c <= 'z'; }

// Проверяет, является ли c одним из символов, которые нужно убрать по
// краям строки. Если trim_chars пустой, использует обычные пробелы/
// табуляции.
static int is_trim_char(char c, const char *trim_chars) {
  int result = 0;
  if (trim_chars == S21_NULL || trim_chars[0] == '\0') {
    result = (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' ||
              c == '\v');
  } else {
    for (s21_size_t i = 0; trim_chars[i] != '\0' && !result; i++) {
      if (trim_chars[i] == c) result = 1;
    }
  }
  return result;
}

// Создаёт новую строку, где все буквы превращены в заглавные.
void *s21_to_upper(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = local_strlen(str);
    result = malloc(len + 1);
    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        result[i] = is_lower_ascii(str[i]) ? str[i] - 'a' + 'A' : str[i];
      }
      result[len] = '\0';
    }
  }
  return result;
}

// Создаёт новую строку, где все буквы превращены в строчные.
void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = local_strlen(str);
    result = malloc(len + 1);
    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        result[i] = is_upper_ascii(str[i]) ? str[i] - 'A' + 'a' : str[i];
      }
      result[len] = '\0';
    }
  }
  return result;
}

// Создаёт новую строку, вставляя str внутрь src, начиная с позиции
// start_index.
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_len = local_strlen(src);
    if (start_index <= src_len) {
      s21_size_t str_len = local_strlen(str);
      result = malloc(src_len + str_len + 1);
      if (result != S21_NULL) {
        s21_size_t pos = 0;
        for (s21_size_t i = 0; i < start_index; i++) result[pos++] = src[i];
        for (s21_size_t i = 0; i < str_len; i++) result[pos++] = str[i];
        for (s21_size_t i = start_index; i < src_len; i++) {
          result[pos++] = src[i];
        }
        result[pos] = '\0';
      }
    }
  }
  return result;
}

// Создаёт новую строку, убирая ненужные символы в начале и конце src
// (по умолчанию пробелы, либо то, что указано в trim_chars).
void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src != S21_NULL) {
    s21_size_t src_len = local_strlen(src);
    s21_size_t start = 0;
    while (start < src_len && is_trim_char(src[start], trim_chars)) start++;
    s21_size_t end = src_len;
    while (end > start && is_trim_char(src[end - 1], trim_chars)) end--;
    s21_size_t trimmed_len = end - start;
    result = malloc(trimmed_len + 1);
    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < trimmed_len; i++) {
        result[i] = src[start + i];
      }
      result[trimmed_len] = '\0';
    }
  }
  return result;
}
