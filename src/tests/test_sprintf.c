#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_text_only) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Hello World");
  int r2 = sprintf(s2, "Hello World");

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_percent) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "100%%");
  int r2 = sprintf(s2, "100%%");

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_char) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Char: %c", 'A');
  int r2 = sprintf(s2, "Char: %c", 'A');

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_string) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Hello %s", "World");
  int r2 = sprintf(s2, "Hello %s", "World");

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_int) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Number: %d", 12345);
  int r2 = sprintf(s2, "Number: %d", 12345);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_int_negative) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%d", -54321);
  int r2 = sprintf(s2, "%d", -54321);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_int_zero) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%d", 0);
  int r2 = sprintf(s2, "%d", 0);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_unsigned) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Number: %u", 12345u);
  int r2 = sprintf(s2, "Number: %u", 12345u);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_unsigned_zero) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%u", 0u);
  int r2 = sprintf(s2, "%u", 0u);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_float_zero) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%f", 123.0);
  int r2 = sprintf(s2, "%f", 123.0);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_float_fraction) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%f", 12.345678);
  int r2 = sprintf(s2, "%f", 12.345678);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_precision_parse) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%.2f", 12.3456);
  int r2 = sprintf(s2, "%.2f", 12.3456);

  (void)r1;
  (void)r2;
}
END_TEST

START_TEST(test_width_d) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%5d", 42);
  int r2 = sprintf(s2, "%5d", 42);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST


Suite *sprintf_suite(void) {
  Suite *suite = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_text_only);
  tcase_add_test(tc, test_percent);
  tcase_add_test(tc, test_char);
  tcase_add_test(tc, test_string);
  tcase_add_test(tc, test_int);
  tcase_add_test(tc, test_int_negative);
  tcase_add_test(tc, test_int_zero);
  tcase_add_test(tc, test_unsigned);
  tcase_add_test(tc, test_unsigned_zero);
  tcase_add_test(tc, test_float_zero);
  tcase_add_test(tc, test_float_fraction);
  tcase_add_test(tc, test_precision_parse);
  tcase_add_test(tc, test_width_d);

  suite_add_tcase(suite, tc);

  return suite;
}

