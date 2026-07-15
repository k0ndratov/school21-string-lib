CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = --coverage
CHECK_FLAGS = $(shell pkg-config --cflags --libs check)

SRC = s21_string.c s21_strerror.c s21_sprintf.c s21_float_fmt.c s21_sscanf.c s21_special.c
OBJ = s21_string.o s21_strerror.o s21_sprintf.o s21_float_fmt.o s21_sscanf.o s21_special.o

TESTS = \
	tests/test_main.c \
	tests/test_strlen.c \
	tests/test_memset.c \
	tests/test_memcpy.c \
	tests/test_memcmp.c \
	tests/test_memchr.c \
	tests/test_strncpy.c \
	tests/test_strncat.c \
	tests/test_strchr.c \
	tests/test_strncmp.c \
	tests/test_strcspn.c \
	tests/test_strpbrk.c \
	tests/test_strrchr.c \
	tests/test_strstr.c \
	tests/test_strtok.c \
	tests/test_strerror.c \
	tests/test_sprintf.c \
	tests/test_sscanf.c \
	tests/test_special.c \

all: s21_string.a

s21_string.a: $(OBJ)
	ar rcs s21_string.a $(OBJ)
	ranlib s21_string.a

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

test:
	$(CC) $(CFLAGS) $(SRC) $(TESTS) -o test $(CHECK_FLAGS) -lm
	./test

gcov_report:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC) $(TESTS) -o test $(CHECK_FLAGS) -lm
	./test
	lcov -t "s21_string" -o coverage.info -c -d .
	genhtml coverage.info -o report
	-xdg-open report/index.html 2>/dev/null || true

clean:
	rm -f *.o *.a test *.gcda *.gcno coverage.info
	rm -rf report

rebuild: clean all

.PHONY: all clean test gcov_report rebuild