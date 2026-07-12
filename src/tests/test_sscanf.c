#include <check.h>

#include "../s21_string.h"

// Part 4 (bonus) tests. TODO(W-D): compare s21_sscanf vs libc sscanf.
// Must cover: width, '*' suppression, %n, float/scientific (e/E/f/g/G),
// int bases (i/o/x), %%, EOF/short-input, and return-count correctness.

Suite *sscanf_suite(void) {
  Suite *s = suite_create("sscanf");
  TCase *tc = tcase_create("core");
  suite_add_tcase(s, tc);
  return s;
}
