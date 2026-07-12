#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_to_upper_basic) {
  char *result = s21_to_upper("abcXYZ123");

  ck_assert_str_eq(result, "ABCXYZ123");
  free(result);
}
END_TEST

START_TEST(test_to_upper_null) {
  ck_assert_ptr_eq(s21_to_upper(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_to_upper_empty) {
  char *result = s21_to_upper("");

  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_basic) {
  char *result = s21_to_lower("abcXYZ123");

  ck_assert_str_eq(result, "abcxyz123");
  free(result);
}
END_TEST

START_TEST(test_to_lower_null) {
  ck_assert_ptr_eq(s21_to_lower(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_to_lower_empty) {
  char *result = s21_to_lower("");

  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_insert_start) {
  char *result = s21_insert("world", "hello ", 0);

  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_end) {
  char *result = s21_insert("hello", " world", 5);

  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_middle) {
  char *result = s21_insert("helloworld", " ", 5);

  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_index_too_large) {
  ck_assert_ptr_eq(s21_insert("hello", "x", 6), S21_NULL);
}
END_TEST

START_TEST(test_insert_null_src) {
  ck_assert_ptr_eq(s21_insert(S21_NULL, "x", 0), S21_NULL);
}
END_TEST

START_TEST(test_insert_null_str) {
  ck_assert_ptr_eq(s21_insert("hello", S21_NULL, 0), S21_NULL);
}
END_TEST

START_TEST(test_insert_empty_str) {
  char *result = s21_insert("hello", "", 2);

  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_insert_into_empty_src) {
  char *result = s21_insert("", "abc", 0);

  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(test_trim_null_src) {
  ck_assert_ptr_eq(s21_trim(S21_NULL, "x"), S21_NULL);
}
END_TEST

START_TEST(test_trim_custom_chars) {
  char *result = s21_trim("xxHelloxx", "x");

  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_trim_leading_only) {
  char *result = s21_trim("xxHello", "x");

  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_trim_trailing_only) {
  char *result = s21_trim("Helloxx", "x");

  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_trim_removes_all) {
  char *result = s21_trim("aaaa", "a");

  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_removes_none) {
  char *result = s21_trim("Hello", "xyz");

  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_trim_default_whitespace_null) {
  char *result = s21_trim("  Hello World  ", S21_NULL);

  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(test_trim_default_whitespace_empty) {
  char *result = s21_trim("\t\nHello\r\n", "");

  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_src) {
  char *result = s21_trim("", "x");

  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

Suite *special_suite(void) {
  Suite *suite = suite_create("special");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_to_upper_basic);
  tcase_add_test(tc, test_to_upper_null);
  tcase_add_test(tc, test_to_upper_empty);
  tcase_add_test(tc, test_to_lower_basic);
  tcase_add_test(tc, test_to_lower_null);
  tcase_add_test(tc, test_to_lower_empty);
  tcase_add_test(tc, test_insert_start);
  tcase_add_test(tc, test_insert_end);
  tcase_add_test(tc, test_insert_middle);
  tcase_add_test(tc, test_insert_index_too_large);
  tcase_add_test(tc, test_insert_null_src);
  tcase_add_test(tc, test_insert_null_str);
  tcase_add_test(tc, test_insert_empty_str);
  tcase_add_test(tc, test_insert_into_empty_src);
  tcase_add_test(tc, test_trim_null_src);
  tcase_add_test(tc, test_trim_custom_chars);
  tcase_add_test(tc, test_trim_leading_only);
  tcase_add_test(tc, test_trim_trailing_only);
  tcase_add_test(tc, test_trim_removes_all);
  tcase_add_test(tc, test_trim_removes_none);
  tcase_add_test(tc, test_trim_default_whitespace_null);
  tcase_add_test(tc, test_trim_default_whitespace_empty);
  tcase_add_test(tc, test_trim_empty_src);

  suite_add_tcase(suite, tc);

  return suite;
}
