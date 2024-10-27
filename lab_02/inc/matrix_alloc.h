#ifndef MATRIX_ALLOC_H
#define MATRIX_ALLOC_H

#include "matrix.h"
#include "error_t.h"

error_t alloc_matrix_t(matrix_t *matrix, size_t n, size_t m);

void free_matrix_t(matrix_t *matrix);

int **alloc_matrix(size_t n, size_t m);

double **alloc_matrix_double(size_t n, size_t m);

void free_martrix(int ***data, size_t n);

void free_martrix_double(double ***data, size_t n);


#endif // MATRIX_ALLOC_H
