#ifndef S21_STRING_INTERNAL_H
#define S21_STRING_INTERNAL_H

#include <float.h>

#include "s21_string.h"

#define S21_MAX_INT_DIGITS (LDBL_MAX_10_EXP + 8)

int s21_strlen_local(const char* str);
void s21_shift_right(char* buffer, int count, char fill);

void s21_build_fixed(long double v, int precision, int hash, char* out);
void s21_build_sci(long double v, int precision, char expchar, int hash,
                   char* out);
void s21_build_g(long double v, int precision, int upper, int hash, char* out);

#endif
