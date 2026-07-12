#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

// Part 4 (bonus) tests: compare s21_sscanf vs libc sscanf.
// Covers: width, '*' suppression, %n, float/scientific (e/E/f/g/G),
// int bases (i/o/x), %%, EOF/short-input, and return-count correctness.

START_TEST(test_sscanf_two_ints) {
  int a1, a2, b1, b2;
  int r1 = s21_sscanf("42 -7", "%d %d", &a1, &a2);
  int r2 = sscanf("42 -7", "%d %d", &b1, &b2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(a2, b2);
}
END_TEST

START_TEST(test_sscanf_short_input) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int r1 = s21_sscanf("42", "%d %d", &a1, &a2);
  int r2 = sscanf("42", "%d %d", &b1, &b2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_empty_eof) {
  int a1, b1;
  int r1 = s21_sscanf("", "%d", &a1);
  int r2 = sscanf("", "%d", &b1);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sscanf_match_fail) {
  int a1, b1;
  int r1 = s21_sscanf("abc", "%d", &a1);
  int r2 = sscanf("abc", "%d", &b1);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sscanf_i_hex) {
  int a1, b1;
  int r1 = s21_sscanf("0x1F", "%i", &a1);
  int r2 = sscanf("0x1F", "%i", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_i_octal) {
  int a1, b1;
  int r1 = s21_sscanf("017", "%i", &a1);
  int r2 = sscanf("017", "%i", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_octal) {
  unsigned a1, b1;
  int r1 = s21_sscanf("777", "%o", &a1);
  int r2 = sscanf("777", "%o", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_uint_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_hex) {
  unsigned a1, b1;
  int r1 = s21_sscanf("deadBEEF", "%x", &a1);
  int r2 = sscanf("deadBEEF", "%x", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_uint_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_hex_prefix) {
  unsigned a1, b1;
  int r1 = s21_sscanf("0Xff", "%x", &a1);
  int r2 = sscanf("0Xff", "%x", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_uint_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  unsigned a1, b1;
  int r1 = s21_sscanf("12345", "%u", &a1);
  int r2 = sscanf("12345", "%u", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_uint_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_char_leading_space) {
  char a1, b1;
  int r1 = s21_sscanf(" x", "%c", &a1);
  int r2 = sscanf(" x", "%c", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_string) {
  char a1[32], b1[32];
  int r1 = s21_sscanf("  hello world", "%s", a1);
  int r2 = sscanf("  hello world", "%s", b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_string_width) {
  char a1[32], b1[32];
  int r1 = s21_sscanf("hello", "%3s", a1);
  int r2 = sscanf("hello", "%3s", b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_int_width) {
  int a1, a2, b1, b2;
  int r1 = s21_sscanf("12345", "%2d%3d", &a1, &a2);
  int r2 = sscanf("12345", "%2d%3d", &b1, &b2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(a2, b2);
}
END_TEST

START_TEST(test_sscanf_suppress) {
  int a1, b1;
  int r1 = s21_sscanf("10 20", "%*d %d", &a1);
  int r2 = sscanf("10 20", "%*d %d", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_n) {
  int a1, n1, b1, n2;
  int r1 = s21_sscanf("123abc", "%d%n", &a1, &n1);
  int r2 = sscanf("123abc", "%d%n", &b1, &n2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_percent) {
  int a1, b1;
  int r1 = s21_sscanf("50% done", "%d%%", &a1);
  int r2 = sscanf("50% done", "%d%%", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_float) {
  float a1, b1;
  int r1 = s21_sscanf("3.14", "%f", &a1);
  int r2 = sscanf("3.14", "%f", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_float_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_scientific) {
  float a1, b1;
  int r1 = s21_sscanf("1.5e3", "%e", &a1);
  int r2 = sscanf("1.5e3", "%e", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_float_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_g_negative) {
  float a1, b1;
  int r1 = s21_sscanf("-0.001", "%g", &a1);
  int r2 = sscanf("-0.001", "%g", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_float_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_double) {
  double a1, b1;
  int r1 = s21_sscanf("2.718281828", "%lf", &a1);
  int r2 = sscanf("2.718281828", "%lf", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_double_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_long_double) {
  long double a1, b1;
  int r1 = s21_sscanf("1.23456789", "%Lf", &a1);
  int r2 = sscanf("1.23456789", "%Lf", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_ldouble_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_short) {
  short a1, b1;
  int r1 = s21_sscanf("-32000", "%hd", &a1);
  int r2 = sscanf("-32000", "%hd", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_long) {
  long a1, b1;
  int r1 = s21_sscanf("9999999999", "%ld", &a1);
  int r2 = sscanf("9999999999", "%ld", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1 == b1, 1);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  void *a1, *b1;
  int r1 = s21_sscanf("0x7ffd1234", "%p", &a1);
  int r2 = sscanf("0x7ffd1234", "%p", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_ptr_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_mixed) {
  int a1, b1;
  char a2[16], b2[16];
  float a3, b3;
  int r1 = s21_sscanf("7 word 2.5", "%d %s %f", &a1, a2, &a3);
  int r2 = sscanf("7 word 2.5", "%d %s %f", &b1, b2, &b3);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
  ck_assert_str_eq(a2, b2);
  ck_assert_float_eq(a3, b3);
}
END_TEST

START_TEST(test_sscanf_literal_mismatch) {
  int a1 = 0, b1 = 0;
  int r1 = s21_sscanf("x42", "y%d", &a1);
  int r2 = sscanf("x42", "y%d", &b1);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sscanf_ws_run) {
  int a1, a2, b1, b2;
  int r1 = s21_sscanf("1\t\n  2", "%d %d", &a1, &a2);
  int r2 = sscanf("1\t\n  2", "%d %d", &b1, &b2);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(a2, b2);
}
END_TEST

START_TEST(test_sscanf_suppress_char) {
  char a1, b1;
  int r1 = s21_sscanf("ab", "%*c%c", &a1);
  int r2 = sscanf("ab", "%*c%c", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_hhd) {
  signed char a1, b1;
  int r1 = s21_sscanf("100", "%hhd", &a1);
  int r2 = sscanf("100", "%hhd", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

START_TEST(test_sscanf_char_width) {
  char a1[8] = {0}, b1[8] = {0};
  int r1 = s21_sscanf("hello", "%3c", a1);
  int r2 = sscanf("hello", "%3c", b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(memcmp(a1, b1, 3), 0);
}
END_TEST

START_TEST(test_sscanf_plus_sign) {
  int a1, b1;
  int r1 = s21_sscanf("+55", "%d", &a1);
  int r2 = sscanf("+55", "%d", &b1);
  ck_assert_int_eq(r1, r2);
  ck_assert_int_eq(a1, b1);
}
END_TEST

Suite *sscanf_suite(void) {
  Suite *s = suite_create("sscanf");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sscanf_two_ints);
  tcase_add_test(tc, test_sscanf_short_input);
  tcase_add_test(tc, test_sscanf_empty_eof);
  tcase_add_test(tc, test_sscanf_match_fail);
  tcase_add_test(tc, test_sscanf_i_hex);
  tcase_add_test(tc, test_sscanf_i_octal);
  tcase_add_test(tc, test_sscanf_octal);
  tcase_add_test(tc, test_sscanf_hex);
  tcase_add_test(tc, test_sscanf_hex_prefix);
  tcase_add_test(tc, test_sscanf_unsigned);
  tcase_add_test(tc, test_sscanf_char_leading_space);
  tcase_add_test(tc, test_sscanf_string);
  tcase_add_test(tc, test_sscanf_string_width);
  tcase_add_test(tc, test_sscanf_int_width);
  tcase_add_test(tc, test_sscanf_suppress);
  tcase_add_test(tc, test_sscanf_n);
  tcase_add_test(tc, test_sscanf_percent);
  tcase_add_test(tc, test_sscanf_float);
  tcase_add_test(tc, test_sscanf_scientific);
  tcase_add_test(tc, test_sscanf_g_negative);
  tcase_add_test(tc, test_sscanf_double);
  tcase_add_test(tc, test_sscanf_long_double);
  tcase_add_test(tc, test_sscanf_short);
  tcase_add_test(tc, test_sscanf_long);
  tcase_add_test(tc, test_sscanf_pointer);
  tcase_add_test(tc, test_sscanf_mixed);
  tcase_add_test(tc, test_sscanf_literal_mismatch);
  tcase_add_test(tc, test_sscanf_ws_run);
  tcase_add_test(tc, test_sscanf_suppress_char);
  tcase_add_test(tc, test_sscanf_hhd);
  tcase_add_test(tc, test_sscanf_char_width);
  tcase_add_test(tc, test_sscanf_plus_sign);

  suite_add_tcase(s, tc);
  return s;
}
