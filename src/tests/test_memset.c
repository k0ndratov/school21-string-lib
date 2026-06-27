#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memset_char) {
  char s1[20] = "Hello World";
  char s2[20] = "Hello World";

  s21_memset(s1, '*', 5);
  memset(s2, '*', 5);

  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

START_TEST(test_memset_zero) {
  char s1[10] = "abcdefghi";
  char s2[10] = "abcdefghi";

  s21_memset(s1, 0, 5);
  memset(s2, 0, 5);

  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

START_TEST(test_memset_full) {
  char s1[10];
  char s2[10];

  s21_memset(s1, 'A', sizeof(s1));
  memset(s2, 'A', sizeof(s2));

  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

START_TEST(test_memset_empty) {
  char s1[] = "Hello";
  char s2[] = "Hello";

  s21_size_t n = 0;

  s21_memset(s1, 'X', n);
  memset(s2, 'X', n);

  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

Suite *memset_suite(void) {
  Suite *suite = suite_create("s21_memset");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memset_char);
  tcase_add_test(tc, test_memset_zero);
  tcase_add_test(tc, test_memset_full);
  tcase_add_test(tc, test_memset_empty);

  suite_add_tcase(suite, tc);

  return suite;
}