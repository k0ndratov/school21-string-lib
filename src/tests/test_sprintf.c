#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_text_only) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Hello World");
  int r2 = sprintf(s2, "Hello World");

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_percent) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "100%%");
  int r2 = sprintf(s2, "100%%");

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_char) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Char: %c", 'A');
  int r2 = sprintf(s2, "Char: %c", 'A');

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_string) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Hello %s", "World");
  int r2 = sprintf(s2, "Hello %s", "World");

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_int) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Number: %d", 12345);
  int r2 = sprintf(s2, "Number: %d", 12345);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_int_negative) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%d", -54321);
  int r2 = sprintf(s2, "%d", -54321);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_int_zero) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%d", 0);
  int r2 = sprintf(s2, "%d", 0);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_unsigned) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "Number: %u", 12345u);
  int r2 = sprintf(s2, "Number: %u", 12345u);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_unsigned_zero) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%u", 0u);
  int r2 = sprintf(s2, "%u", 0u);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_float_zero) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%f", 123.0);
  int r2 = sprintf(s2, "%f", 123.0);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_float_fraction) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%f", 12.345678);
  int r2 = sprintf(s2, "%f", 12.345678);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_precision_parse) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%.2f", 12.3456);
  int r2 = sprintf(s2, "%.2f", 12.3456);

  (void)r1;
  (void)r2;
}
END_TEST

START_TEST(test_width_d) {
  char s1[100];
  char s2[100];

  int r1 = s21_sprintf(s1, "%5d", 42);
  int r2 = sprintf(s2, "%5d", 42);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_short_d) {
  char s1[128];
  char s2[128];

  short value = -123;

  int r1 = sprintf(s1, "%hd", value);
  int r2 = s21_sprintf(s2, "%hd", value);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_long_d) {
  char s1[128];
  char s2[128];

  long value = 123456789L;

  int r1 = sprintf(s1, "%ld", value);
  int r2 = s21_sprintf(s2, "%ld", value);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_precision_d) {
  char s1[128];
  char s2[128];

  int value = 42;

  int r1 = sprintf(s1, "%.5d", value);
  int r2 = s21_sprintf(s2, "%.5d", value);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_precision_u) {
  char s1[128];
  char s2[128];

  unsigned int value = 42;

  int r1 = sprintf(s1, "%.5u", value);
  int r2 = s21_sprintf(s2, "%.5u", value);

  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

#define CK_CMP(fmt, ...)                        \
  do {                                          \
    char s1[512];                               \
    char s2[512];                               \
    int r1 = s21_sprintf(s1, fmt, __VA_ARGS__); \
    int r2 = sprintf(s2, fmt, __VA_ARGS__);     \
    ck_assert_int_eq(r1, r2);                   \
    ck_assert_str_eq(s1, s2);                   \
  } while (0)

START_TEST(test_octal) {
  CK_CMP("%o", 255);
  CK_CMP("%o", 0);
  CK_CMP("%#o", 255);
  CK_CMP("%.5o", 8);
  CK_CMP("%#08o", 255);
  CK_CMP("%lo", 123456789UL);
}
END_TEST

START_TEST(test_hex) {
  CK_CMP("%x", 255);
  CK_CMP("%X", 255);
  CK_CMP("%#x", 255);
  CK_CMP("%#X", 255);
  CK_CMP("%#x", 0);
  CK_CMP("%.5x", 255);
  CK_CMP("%#010x", 255);
  CK_CMP("%lx", 4294967296UL);
}
END_TEST

START_TEST(test_pointer) {
  int v = 5;
  char s1[64];
  char s2[64];
  int r1 = s21_sprintf(s1, "%p", (void *)&v);
  int r2 = sprintf(s2, "%p", (void *)&v);
  ck_assert_int_eq(r1, r2);
  ck_assert_str_eq(s1, s2);
  CK_CMP("%p", (void *)0);
}
END_TEST

START_TEST(test_scientific) {
  CK_CMP("%e", 12345.678);
  CK_CMP("%E", 12345.678);
  CK_CMP("%.2e", 12345.678);
  CK_CMP("%.0e", 12345.678);
  CK_CMP("%e", 0.0);
  CK_CMP("%15.3e", 1234.5);
  CK_CMP("%-15.3e", 1234.5);
  CK_CMP("%+e", 1234.5);
  CK_CMP("%e", 1e300);
}
END_TEST

START_TEST(test_general) {
  CK_CMP("%g", 100000.0);
  CK_CMP("%g", 1000000.0);
  CK_CMP("%g", 0.0001);
  CK_CMP("%g", 0.00001);
  CK_CMP("%g", 123.456);
  CK_CMP("%G", 0.00001234);
  CK_CMP("%.10g", 3.14159265358979);
  CK_CMP("%#g", 1.5);
}
END_TEST

START_TEST(test_star) {
  CK_CMP("%*d", 8, 42);
  CK_CMP("%-*d", 8, 42);
  CK_CMP("%.*f", 3, 3.14159);
  CK_CMP("%*.*f", 10, 2, 3.14159);
  CK_CMP("%*d", -8, 42);
}
END_TEST

START_TEST(test_long_double) {
  CK_CMP("%Lf", (long double)3.14159265358979L);
  CK_CMP("%.2Le", (long double)12345.678L);
  CK_CMP("%Lg", (long double)0.0001L);
}
END_TEST

START_TEST(test_harden_width) {
  CK_CMP("%10u", 42u);
  CK_CMP("%-10u", 42u);
  CK_CMP("%010u", 42u);
  CK_CMP("%10f", 3.14);
  CK_CMP("%-10f", 3.14);
  CK_CMP("%010f", 3.14);
  CK_CMP("%+10.2f", 3.14);
}
END_TEST

START_TEST(test_harden_long) {
  CK_CMP("%ld", 9999999999L);
  CK_CMP("%ld", -9999999999L);
  CK_CMP("%lu", 9999999999UL);
}
END_TEST

START_TEST(test_harden_big_double) {
  CK_CMP("%.2f", 3000000000.5);
  CK_CMP("%.0f", 12345678901.0);
}
END_TEST

START_TEST(test_harden_edge) {
  CK_CMP("%.0d", 0);
  CK_CMP("%.0u", 0);
  CK_CMP("%5.0d", 0);
  CK_CMP("%f", -0.0);
  CK_CMP("%.1f", -0.0);
}
END_TEST

Suite *sprintf_suite(void) {
  Suite *suite = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_text_only);
  tcase_add_test(tc, test_percent);
  tcase_add_test(tc, test_char);
  tcase_add_test(tc, test_string);
  tcase_add_test(tc, test_int);
  tcase_add_test(tc, test_int_negative);
  tcase_add_test(tc, test_int_zero);
  tcase_add_test(tc, test_unsigned);
  tcase_add_test(tc, test_unsigned_zero);
  tcase_add_test(tc, test_float_zero);
  tcase_add_test(tc, test_float_fraction);
  tcase_add_test(tc, test_precision_parse);
  tcase_add_test(tc, test_width_d);
  tcase_add_test(tc, test_short_d);
  tcase_add_test(tc, test_long_d);
  tcase_add_test(tc, test_precision_d);
  tcase_add_test(tc, test_precision_u);
  tcase_add_test(tc, test_octal);
  tcase_add_test(tc, test_hex);
  tcase_add_test(tc, test_pointer);
  tcase_add_test(tc, test_scientific);
  tcase_add_test(tc, test_general);
  tcase_add_test(tc, test_star);
  tcase_add_test(tc, test_long_double);
  tcase_add_test(tc, test_harden_width);
  tcase_add_test(tc, test_harden_long);
  tcase_add_test(tc, test_harden_big_double);
  tcase_add_test(tc, test_harden_edge);

  suite_add_tcase(suite, tc);

  return suite;
}