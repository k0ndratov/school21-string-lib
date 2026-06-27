#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strstr_found) {
  char s1[] = "Hello World";
  char s2[] = "World";

  ck_assert_ptr_eq(s21_strstr(s1, s2), strstr(s1, s2));
}
END_TEST

START_TEST(test_strstr_not_found) {
  char s1[] = "Hello World";
  char s2[] = "School";

  ck_assert_ptr_eq(s21_strstr(s1, s2), strstr(s1, s2));
}
END_TEST

START_TEST(test_strstr_begin) {
  char s1[] = "Hello World";
  char s2[] = "Hello";

  ck_assert_ptr_eq(s21_strstr(s1, s2), strstr(s1, s2));
}
END_TEST

START_TEST(test_strstr_empty) {
  char s1[] = "Hello";
  char s2[] = "";

  ck_assert_ptr_eq(s21_strstr(s1, s2), strstr(s1, s2));
}
END_TEST

START_TEST(test_strstr_equal) {
  char s1[] = "abcdef";
  char s2[] = "abcdef";

  ck_assert_ptr_eq(s21_strstr(s1, s2), strstr(s1, s2));
}
END_TEST

Suite *strstr_suite(void) {
  Suite *suite = suite_create("s21_strstr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strstr_found);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_begin);
  tcase_add_test(tc, test_strstr_empty);
  tcase_add_test(tc, test_strstr_equal);

  suite_add_tcase(suite, tc);

  return suite;
}