#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strerror_zero) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
END_TEST

START_TEST(test_strerror_one) {
  ck_assert_str_eq(s21_strerror(1), strerror(1));
}
END_TEST

START_TEST(test_strerror_two) {
  ck_assert_str_eq(s21_strerror(2), strerror(2));
}
END_TEST

START_TEST(test_strerror_middle) {
  ck_assert_str_eq(s21_strerror(22), strerror(22));
}
END_TEST

START_TEST(test_strerror_known) {
  ck_assert_str_eq(s21_strerror(95), strerror(95));
}
END_TEST

START_TEST(test_strerror_negative) {
  ck_assert_str_eq(s21_strerror(-1), strerror(-1));
}
END_TEST

START_TEST(test_strerror_big) {
  ck_assert_str_eq(s21_strerror(999), strerror(999));
}
END_TEST

Suite *strerror_suite(void) {
  Suite *suite = suite_create("s21_strerror");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strerror_zero);
  tcase_add_test(tc, test_strerror_one);
  tcase_add_test(tc, test_strerror_two);
  tcase_add_test(tc, test_strerror_middle);
  tcase_add_test(tc, test_strerror_known);
  tcase_add_test(tc, test_strerror_negative);
  tcase_add_test(tc, test_strerror_big);

  suite_add_tcase(suite, tc);

  return suite;
}