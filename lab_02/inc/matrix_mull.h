#ifndef MATRIX_MULL_H
#define MATRIX_MULL_H

#include "matrix.h"
#include "error_t.h"

typedef enum {
    DEFAULT,
    VINOGRAD,
    VINOGRAD_MODIFY,
} mull_mode;

error_t matrix_mul(const matrix_t *matrix_1, const matrix_t *martix_2, matrix_t *result);

error_t vinograd_matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result);

error_t vinograd_modify_matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result);

#endif // MATRIX_MULL_H
