#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memcpy_string) {
  char s1[20] = {0};
  char s2[20] = {0};

  s21_memcpy(s1, "Hello", 6);
  memcpy(s2, "Hello", 6);

  ck_assert_mem_eq(s1, s2, sizeof(s2));
}
END_TEST

START_TEST(test_memcpy_partial) {
  char src[] = "abcdef";
  char d1[10] = {0};
  char d2[10] = {0};

  s21_memcpy(d1, src, 3);
  memcpy(d2, src, 3);

  ck_assert_mem_eq(d1, d2, sizeof(d1));
}
END_TEST

START_TEST(test_memcpy_zero) {
  char src[] = "Hello";
  char d1[10] = "12345";
  char d2[10] = "12345";

  s21_memcpy(d1, src, 0);
  memcpy(d2, src, 0);

  ck_assert_mem_eq(d1, d2, sizeof(d1));
}
END_TEST

START_TEST(test_memcpy_bytes) {
  unsigned char src[] = {1, 2, 3, 4, 5};
  unsigned char d1[5] = {0};
  unsigned char d2[5] = {0};

  s21_memcpy(d1, src, sizeof(src));
  memcpy(d2, src, sizeof(src));

  ck_assert_mem_eq(d1, d2, sizeof(src));
}
END_TEST

Suite *memcpy_suite(void) {
  Suite *suite = suite_create("s21_memcpy");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcpy_string);
  tcase_add_test(tc, test_memcpy_partial);
  tcase_add_test(tc, test_memcpy_zero);
  tcase_add_test(tc, test_memcpy_bytes);

  suite_add_tcase(suite, tc);

  return suite;
}