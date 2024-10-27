#ifndef MATRIX_READ_H
#define MATRIX_READ_H

#include "matrix.h"
#include "error_t.h"

void matrix_fill(matrix_t *matrix);

error_t matrix_create_random(matrix_t *matrix, size_t n, size_t m);

error_t matrix_read(matrix_t *matrix) ;

error_t matrix_create(matrix_t *matrix);

void matrix_print(matrix_t *matrix);

#endif // MATRIX_READ_H
