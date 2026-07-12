#include <check.h>

#include "../s21_string.h"

// Part 5 (bonus) tests. TODO(W-E): behavioral asserts for
// s21_to_upper / s21_to_lower / s21_insert / s21_trim (heap copies,
// S21_NULL on error). Remember to free() returned buffers.

Suite *special_suite(void) {
  Suite *s = suite_create("special");
  TCase *tc = tcase_create("core");
  suite_add_tcase(s, tc);
  return s;
}
