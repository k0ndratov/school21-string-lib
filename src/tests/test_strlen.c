#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strlen_empty) { ck_assert_uint_eq(s21_strlen(""), strlen("")); }
END_TEST

START_TEST(test_strlen_word) {
  ck_assert_uint_eq(s21_strlen("Hello"), strlen("Hello"));
}
END_TEST

START_TEST(test_strlen_sentence) {
  ck_assert_uint_eq(s21_strlen("Hello, School 21!"),
                    strlen("Hello, School 21!"));
}
END_TEST

START_TEST(test_strlen_spaces) {
  ck_assert_uint_eq(s21_strlen("     "), strlen("     "));
}
END_TEST

START_TEST(test_strlen_numbers) {
  ck_assert_uint_eq(s21_strlen("1234567890"), strlen("1234567890"));
}
END_TEST

Suite *strlen_suite(void) {
  Suite *suite = suite_create("s21_strlen");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_word);
  tcase_add_test(tc, test_strlen_sentence);
  tcase_add_test(tc, test_strlen_spaces);
  tcase_add_test(tc, test_strlen_numbers);

  suite_add_tcase(suite, tc);

  return suite;
}