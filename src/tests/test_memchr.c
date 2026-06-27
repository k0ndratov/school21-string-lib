#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memchr_found) {
  char str[] = "Hello";

  ck_assert_ptr_eq(
      s21_memchr(str, 'l', 5),
      memchr(str, 'l', 5));
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = "Hello";

  ck_assert_ptr_eq(
      s21_memchr(str, 'x', 5),
      memchr(str, 'x', 5));
}
END_TEST

START_TEST(test_memchr_zero_length) {
  char str[] = "Hello";

  ck_assert_ptr_eq(
      s21_memchr(str, 'H', 0),
      memchr(str, 'H', 0));
}
END_TEST

START_TEST(test_memchr_null_char) {
  char str[] = "Hello";

  ck_assert_ptr_eq(
      s21_memchr(str, '\0', 6),
      memchr(str, '\0', 6));
}
END_TEST

Suite *memchr_suite(void) {
  Suite *suite = suite_create("s21_memchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memchr_found);
  tcase_add_test(tc, test_memchr_not_found);
  tcase_add_test(tc, test_memchr_zero_length);
  tcase_add_test(tc, test_memchr_null_char);

  suite_add_tcase(suite, tc);

  return suite;
}