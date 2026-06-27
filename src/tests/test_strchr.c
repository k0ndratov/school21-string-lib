#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strchr_found) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
}
END_TEST

START_TEST(test_strchr_not_found) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strchr(str, 'x'), strchr(str, 'x'));
}
END_TEST

START_TEST(test_strchr_first) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strchr(str, 'H'), strchr(str, 'H'));
}
END_TEST

START_TEST(test_strchr_null) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

Suite *strchr_suite(void) {
  Suite *suite = suite_create("s21_strchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strchr_found);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_first);
  tcase_add_test(tc, test_strchr_null);

  suite_add_tcase(suite, tc);

  return suite;
}