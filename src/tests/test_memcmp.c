#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memcmp_equal) {
  char s1[] = "Hello";
  char s2[] = "Hello";

  ck_assert_int_eq(
      s21_memcmp(s1, s2, 5),
      memcmp(s1, s2, 5));
}
END_TEST

START_TEST(test_memcmp_less) {
  char s1[] = "Hello";
  char s2[] = "World";

  ck_assert_int_eq(
      (s21_memcmp(s1, s2, 5) < 0),
      (memcmp(s1, s2, 5) < 0));
}
END_TEST

START_TEST(test_memcmp_greater) {
  char s1[] = "World";
  char s2[] = "Hello";

  ck_assert_int_eq(
      (s21_memcmp(s1, s2, 5) > 0),
      (memcmp(s1, s2, 5) > 0));
}
END_TEST

START_TEST(test_memcmp_zero) {
  char s1[] = "Hello";
  char s2[] = "World";

  ck_assert_int_eq(
      s21_memcmp(s1, s2, 0),
      memcmp(s1, s2, 0));
}
END_TEST

Suite *memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcmp_equal);
  tcase_add_test(tc, test_memcmp_less);
  tcase_add_test(tc, test_memcmp_greater);
  tcase_add_test(tc, test_memcmp_zero);

  suite_add_tcase(suite, tc);

  return suite;
}