#include <check.h>
#include <stdlib.h>

Suite *strlen_suite(void);
Suite *memset_suite(void);
Suite *memcpy_suite(void);
Suite *memcmp_suite(void);
Suite *memchr_suite(void);
Suite *strncpy_suite(void);
Suite *strncat_suite(void);
Suite *strchr_suite(void);
Suite *strncmp_suite(void);
Suite *strcspn_suite(void);
Suite *strpbrk_suite(void);
Suite *strrchr_suite(void);
Suite *strstr_suite(void);
Suite *strtok_suite(void);
Suite *strerror_suite(void);
Suite *sprintf_suite(void);
Suite *sscanf_suite(void);
Suite *special_suite(void);

int main(void) {
  int failed;

  Suite *suite = strlen_suite();
  Suite *suite2 = memset_suite();

  SRunner *runner = srunner_create(suite);
  srunner_add_suite(runner, suite2);

  Suite *suite3 = memcpy_suite();
  srunner_add_suite(runner, suite3);

  Suite *suite4 = memcmp_suite();
  srunner_add_suite(runner, suite4);

  Suite *suite5 = memchr_suite();
  srunner_add_suite(runner, suite5);

  Suite *suite6 = strncpy_suite();
  srunner_add_suite(runner, suite6);

  Suite *suite7 = strncat_suite();
  srunner_add_suite(runner, suite7);

  Suite *suite8 = strchr_suite();
  srunner_add_suite(runner, suite8);

  Suite *suite9 = strncmp_suite();
  srunner_add_suite(runner, suite9);

  Suite *suite10 = strcspn_suite();
  srunner_add_suite(runner, suite10);

  Suite *suite11 = strpbrk_suite();
  srunner_add_suite(runner, suite11);

  Suite *suite12 = strrchr_suite();
  srunner_add_suite(runner, suite12);

  Suite *suite13 = strstr_suite();
  srunner_add_suite(runner, suite13);

  Suite *suite14 = strtok_suite();
  srunner_add_suite(runner, suite14);

  Suite *suite15 = strerror_suite();
  srunner_add_suite(runner, suite15);

  Suite *suite16 = sprintf_suite();
  srunner_add_suite(runner, suite16);

  Suite *suite17 = sscanf_suite();
  srunner_add_suite(runner, suite17);

  Suite *suite18 = special_suite();
  srunner_add_suite(runner, suite18);

  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);

  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}