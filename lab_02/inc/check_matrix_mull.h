#ifndef CHECK_MATRIX_MULL_H
#define CHECK_MATRIX_MULL_H

#include <check.h>

typedef enum {
    PASSED,
    ASSERT_ELEMENTS,
    ASSERT_SIZES,
} test_status_t;


Suite *matrix_mult_tests(void);

Suite *vinograd_matrix_mul_tests(void);

Suite *vinograd_modify_matrix_mul_tests(void);

#endif // CHECK_MATRIX_MULL_H
