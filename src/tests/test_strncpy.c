#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strncpy_equal) {
  char d1[20] = {0};
  char d2[20] = {0};

  s21_strncpy(d1, "Hello", 6);
  strncpy(d2, "Hello", 6);

  ck_assert_mem_eq(d1, d2, sizeof(d1));
}
END_TEST

START_TEST(test_strncpy_short) {
  char d1[20] = {0};
  char d2[20] = {0};

  s21_strncpy(d1, "Hi", 10);
  strncpy(d2, "Hi", 10);

  ck_assert_mem_eq(d1, d2, sizeof(d1));
}
END_TEST

START_TEST(test_strncpy_full_buffer) {
  char d1[20] = {0};
  char d2[20] = {0};

  char src[] = "abcdef";
  s21_size_t n = 7;  // "abcdef" + '\0'

  s21_strncpy(d1, src, n);
  strncpy(d2, src, n);

  ck_assert_mem_eq(d1, d2, sizeof(d1));
}
END_TEST

START_TEST(test_strncpy_zero) {
  char d1[20] = "Hello";
  char d2[20] = "Hello";

  char src[] = "World";
  s21_size_t n = 0;

  s21_strncpy(d1, src, n);
  strncpy(d2, src, n);

  ck_assert_mem_eq(d1, d2, sizeof(d1));
}
END_TEST

Suite *strncpy_suite(void) {
  Suite *suite = suite_create("s21_strncpy");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncpy_equal);
  tcase_add_test(tc, test_strncpy_short);
  tcase_add_test(tc, test_strncpy_full_buffer);
  tcase_add_test(tc, test_strncpy_zero);

  suite_add_tcase(tc ? suite : suite, tc);

  return suite;
}