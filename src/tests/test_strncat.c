#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strncat_basic) {
  char d1[30] = "Hello ";
  char d2[30] = "Hello ";

  char src[] = "World";
  s21_size_t n = strlen(src);

  s21_strncat(d1, src, n);
  strncat(d2, src, n);

  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_strncat_partial) {
  char d1[30] = "Hello ";
  char d2[30] = "Hello ";

  char src[] = "World";

  s21_strncat(d1, src, 3);
  strncat(d2, src, 3);

  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_strncat_zero) {
  char d1[30] = "Hello";
  char d2[30] = "Hello";

  char src[] = "World";
  s21_size_t n = 0;

  s21_strncat(d1, src, n);
  strncat(d2, src, n);

  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char d1[30] = "Hello";
  char d2[30] = "Hello";

  s21_strncat(d1, "", 5);
  strncat(d2, "", 5);

  ck_assert_str_eq(d1, d2);
}
END_TEST

Suite *strncat_suite(void) {
  Suite *suite = suite_create("s21_strncat");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_partial);
  tcase_add_test(tc, test_strncat_zero);
  tcase_add_test(tc, test_strncat_empty_src);

  suite_add_tcase(suite, tc);

  return suite;
}