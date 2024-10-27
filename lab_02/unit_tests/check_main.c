#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "check_matrix_mull.h"


typedef Suite *(*test_case_t)(void);

int test_main(void) {
    SRunner *runner;
    test_case_t unit_tests[] = {matrix_mult_tests, vinograd_matrix_mul_tests, vinograd_modify_matrix_mul_tests};
    size_t tests_cnt = sizeof(unit_tests) / sizeof(*unit_tests);

    int number_failed = 0;

    runner = srunner_create(unit_tests[0]());
    for (size_t i = 1; i < tests_cnt; ++i) {
        srunner_add_suite(runner, unit_tests[i]());
    }

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
