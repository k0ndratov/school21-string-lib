#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strcspn_basic) {
  char s1[] = "abcdef";
  char s2[] = "de";

  ck_assert_uint_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_not_found) {
  char s1[] = "abcdef";
  char s2[] = "xyz";

  ck_assert_uint_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_empty_second) {
  char s1[] = "abcdef";
  char s2[] = "";

  ck_assert_uint_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_first_match) {
  char s1[] = "abcdef";
  char s2[] = "a";

  ck_assert_uint_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

Suite *strcspn_suite(void) {
  Suite *suite = suite_create("s21_strcspn");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strcspn_basic);
  tcase_add_test(tc, test_strcspn_not_found);
  tcase_add_test(tc, test_strcspn_empty_second);
  tcase_add_test(tc, test_strcspn_first_match);

  suite_add_tcase(suite, tc);

  return suite;
}