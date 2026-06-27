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

Suite *sprintf_suite(void) {
  Suite *suite = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_text_only);
  tcase_add_test(tc, test_percent);

  suite_add_tcase(suite, tc);

  return suite;
}