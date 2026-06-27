#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strrchr_found) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strrchr(str, 'l'),
                   strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strrchr_first) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strrchr(str, 'H'),
                   strrchr(str, 'H'));
}
END_TEST

START_TEST(test_strrchr_not_found) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strrchr(str, 'x'),
                   strrchr(str, 'x'));
}
END_TEST

START_TEST(test_strrchr_null) {
  char str[] = "Hello";

  ck_assert_ptr_eq(s21_strrchr(str, '\0'),
                   strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strrchr_last_occurrence) {
  char str[] = "abacada";

  ck_assert_ptr_eq(s21_strrchr(str, 'a'),
                   strrchr(str, 'a'));
}
END_TEST

Suite *strrchr_suite(void) {
  Suite *suite = suite_create("s21_strrchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strrchr_found);
  tcase_add_test(tc, test_strrchr_first);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_null);
  tcase_add_test(tc, test_strrchr_last_occurrence);

  suite_add_tcase(suite, tc);

  return suite;
}