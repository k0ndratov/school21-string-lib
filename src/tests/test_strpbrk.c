#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strpbrk_found) {
  char s1[] = "abcdef";
  char s2[] = "de";

  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(test_strpbrk_first) {
  char s1[] = "abcdef";
  char s2[] = "a";

  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  char s1[] = "abcdef";
  char s2[] = "xyz";

  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(test_strpbrk_empty) {
  char s1[] = "";
  char s2[] = "abc";

  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

Suite *strpbrk_suite(void) {
  Suite *suite = suite_create("s21_strpbrk");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strpbrk_found);
  tcase_add_test(tc, test_strpbrk_first);
  tcase_add_test(tc, test_strpbrk_not_found);
  tcase_add_test(tc, test_strpbrk_empty);

  suite_add_tcase(suite, tc);

  return suite;
}