CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = --coverage
CHECK_FLAGS = $(shell pkg-config --cflags --libs check)

SRC = s21_string.c
OBJ = s21_string.o

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

all: s21_string.a

s21_string.a: $(OBJ)
	ar rcs s21_string.a $(OBJ)
	ranlib s21_string.a

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

test:
	$(CC) $(CFLAGS) $(SRC) $(TESTS) -o test $(CHECK_FLAGS)
	./test

gcov_report:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC) $(TESTS) -o test $(CHECK_FLAGS)
	./test
	lcov -t "s21_string" -o coverage.info -c -d .
	genhtml coverage.info -o report
	xdg-open report/index.html

clean:
	rm -f *.o *.a test *.gcda *.gcno coverage.info
	rm -rf report

rebuild: clean all

.PHONY: all clean test gcov_report rebuild