#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strncmp_equal) {
  char s1[] = "Hello";
  char s2[] = "Hello";

  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));
}
END_TEST

START_TEST(test_strncmp_less) {
  char s1[] = "Hello";
  char s2[] = "World";

  ck_assert_int_eq((s21_strncmp(s1, s2, 5) < 0), (strncmp(s1, s2, 5) < 0));
}
END_TEST

START_TEST(test_strncmp_greater) {
  char s1[] = "World";
  char s2[] = "Hello";

  ck_assert_int_eq((s21_strncmp(s1, s2, 5) > 0), (strncmp(s1, s2, 5) > 0));
}
END_TEST

START_TEST(test_strncmp_zero) {
  char s1[] = "Hello";
  char s2[] = "World";

  ck_assert_int_eq(s21_strncmp(s1, s2, 0), strncmp(s1, s2, 0));
}
END_TEST

START_TEST(test_strncmp_prefix) {
  char s1[] = "Hello";
  char s2[] = "Help";

  ck_assert_int_eq((s21_strncmp(s1, s2, 3) == 0), (strncmp(s1, s2, 3) == 0));
}
END_TEST

Suite *strncmp_suite(void) {
  Suite *suite = suite_create("s21_strncmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncmp_equal);
  tcase_add_test(tc, test_strncmp_less);
  tcase_add_test(tc, test_strncmp_greater);
  tcase_add_test(tc, test_strncmp_zero);
  tcase_add_test(tc, test_strncmp_prefix);

  suite_add_tcase(suite, tc);

  return suite;
}