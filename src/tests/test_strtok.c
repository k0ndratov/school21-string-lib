#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strtok_basic) {
  char s1[] = "one,two,three";
  char s2[] = "one,two,three";

  ck_assert_str_eq(s21_strtok(s1, ","), strtok(s2, ","));
  ck_assert_str_eq(s21_strtok(NULL, ","), strtok(NULL, ","));
  ck_assert_str_eq(s21_strtok(NULL, ","), strtok(NULL, ","));
  ck_assert_ptr_eq(s21_strtok(NULL, ","), strtok(NULL, ","));
}
END_TEST

START_TEST(test_strtok_multi_delim) {
  char s1[] = "one,two;three";
  char s2[] = "one,two;three";

  ck_assert_str_eq(s21_strtok(s1, ",;"), strtok(s2, ",;"));
  ck_assert_str_eq(s21_strtok(NULL, ",;"), strtok(NULL, ",;"));
  ck_assert_str_eq(s21_strtok(NULL, ",;"), strtok(NULL, ",;"));
  ck_assert_ptr_eq(s21_strtok(NULL, ",;"), strtok(NULL, ",;"));
}
END_TEST

START_TEST(test_strtok_leading_delim) {
  char s1[] = ",,,abc";
  char s2[] = ",,,abc";

  ck_assert_str_eq(s21_strtok(s1, ","), strtok(s2, ","));
  ck_assert_ptr_eq(s21_strtok(NULL, ","), strtok(NULL, ","));
}
END_TEST

START_TEST(test_strtok_trailing_delim) {
  char s1[] = "abc,,,";
  char s2[] = "abc,,,";

  ck_assert_str_eq(s21_strtok(s1, ","), strtok(s2, ","));
  ck_assert_ptr_eq(s21_strtok(NULL, ","), strtok(NULL, ","));
}
END_TEST

START_TEST(test_strtok_only_delim) {
  char s1[] = ",,,,";
  char s2[] = ",,,,";

  ck_assert_ptr_eq(s21_strtok(s1, ","), strtok(s2, ","));
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char s1[] = "";
  char s2[] = "";

  ck_assert_ptr_eq(s21_strtok(s1, ","), strtok(s2, ","));
}
END_TEST

START_TEST(test_strtok_no_delim) {
  char s1[] = "abcdef";
  char s2[] = "abcdef";

  ck_assert_str_eq(s21_strtok(s1, ","), strtok(s2, ","));
  ck_assert_ptr_eq(s21_strtok(NULL, ","), strtok(NULL, ","));
}
END_TEST

START_TEST(test_strtok_space) {
  char s1[] = "one two three";
  char s2[] = "one two three";

  ck_assert_str_eq(s21_strtok(s1, " "), strtok(s2, " "));
  ck_assert_str_eq(s21_strtok(NULL, " "), strtok(NULL, " "));
  ck_assert_str_eq(s21_strtok(NULL, " "), strtok(NULL, " "));
}
END_TEST

Suite *strtok_suite(void) {
  Suite *suite = suite_create("s21_strtok");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_multi_delim);
  tcase_add_test(tc, test_strtok_leading_delim);
  tcase_add_test(tc, test_strtok_trailing_delim);
  tcase_add_test(tc, test_strtok_only_delim);
  tcase_add_test(tc, test_strtok_empty_string);
  tcase_add_test(tc, test_strtok_no_delim);
  tcase_add_test(tc, test_strtok_space);

  suite_add_tcase(suite, tc);

  return suite;
}