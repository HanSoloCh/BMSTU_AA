#include "matrix_mull.h"
#include "matrix.h"
#include "matrix_alloc.h"
#include "error_t.h"

#include <stdlib.h>


error_t matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result) {
    if (matrix_1->collumn != matrix_2->row)
        return ERR_RANGE;
    error_t rc = alloc_matrix_t(result, matrix_1->row, matrix_2->collumn);
    if (rc)
        return rc;
    for (size_t i = 0; i < result->row; ++i)
    {
        for (size_t j = 0; j != result->collumn; ++j)
        {
            result->data[i][j] = 0;
            for (size_t k = 0; k < matrix_1->collumn; ++k)
                result->data[i][j] += matrix_1->data[i][k] * matrix_2->data[k][j];
        }
    }
    return ERR_OK;
}


error_t vinograd_matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result) {
    if (matrix_1->collumn != matrix_2->row)
        return ERR_RANGE;

    error_t rc = alloc_matrix_t(result, matrix_1->row, matrix_2->collumn);
    if (rc)
        return rc;

    size_t row_1 = matrix_1->row;
    size_t collumn_1 = matrix_1->collumn;
    size_t collumn_2 = matrix_2->collumn;

    int *row_factor = malloc(row_1 * sizeof(int));
    int *col_factor;
    if (row_factor != NULL) {
        col_factor = malloc(collumn_2 * sizeof(int));
        if (col_factor == NULL) {
            free(row_factor);
            return ERR_MEM;
        }
    } else
        return ERR_MEM;

    for (size_t i = 0; i < row_1; ++i) {
        row_factor[i] = 0;
        for (size_t j = 0; j < collumn_1 / 2; ++j) {
            row_factor[i] = row_factor[i] +
                            matrix_1->data[i][2 * j] * matrix_1->data[i][2 * j + 1];
        }
    }

    for (size_t j = 0; j < collumn_2; ++j) {
        col_factor[j] = 0;
        for (size_t i = 0; i < collumn_1 / 2; ++i) {
            col_factor[j] = col_factor[j] +
                            matrix_2->data[2 * i][j] * matrix_2->data[2 * i + 1][j];
        }
    }

    for (size_t i = 0; i < row_1; ++i) {
        for (size_t j = 0; j < collumn_2; ++j) {
            result->data[i][j] = -row_factor[i] - col_factor[j];
            for (size_t k = 0; k < collumn_1 / 2; ++k) {
                result->data[i][j] = result->data[i][j] + (matrix_1->data[i][2 * k] + matrix_2->data[2 * k + 1][j]) *
                                                          (matrix_1->data[i][2 * k + 1] + matrix_2->data[2 * k][j]);
            }
        }
    }

    if (collumn_1 % 2 == 1) {
        for (size_t i = 0; i < row_1; ++i) {
            for (size_t j = 0; j < collumn_2; ++j) {
                result->data[i][j] = result->data[i][j]+
                                     matrix_1->data[i][collumn_1 - 1] * matrix_2->data[collumn_1 - 1][j];
            }
        }
    }

    free(col_factor);
    free(row_factor);

    return ERR_OK;
}


error_t vinograd_modify_matrix_mul(const matrix_t *matrix_1, const matrix_t *matrix_2, matrix_t *result) {
    if (matrix_1->collumn != matrix_2->row)
        return ERR_RANGE;

    error_t rc = alloc_matrix_t(result, matrix_1->row, matrix_2->collumn);
    if (rc)
        return rc;

    size_t row_1 = matrix_1->row;
    size_t collumn_1 = matrix_1->collumn;
    size_t collumn_2 = matrix_2->collumn;

    int *row_factor = malloc(row_1 * sizeof(int));
    int *col_factor;
    if (row_factor != NULL) {
        col_factor = malloc(collumn_2 * sizeof(int));
        if (col_factor == NULL) {
            free(row_factor);
            return ERR_MEM;
        }
    } else
        return ERR_MEM;

    for (size_t i = 0; i < row_1; ++i) {
        row_factor[i] = 0;
        for (size_t j = 0; j < collumn_1 / 2; ++j) {
            row_factor[i] += matrix_1->data[i][j << 1] * matrix_1->data[i][(j << 1) + 1];
        }
    }

    for (size_t j = 0; j < collumn_2; ++j) {
        col_factor[j] = 0;
        for (size_t i = 0; i < collumn_1 / 2; ++i) {
            col_factor[j] += matrix_2->data[i << 1][j] * matrix_2->data[(i << 1) + 1][j];
        }
    }

    for (size_t i = 0; i < row_1; ++i) {
        for (size_t j = 0; j < collumn_2; ++j) {
            result->data[i][j] = -row_factor[i] - col_factor[j] +
                                 (matrix_1->data[i][0] + matrix_2->data[1][j]) * (matrix_1->data[i][1] + matrix_2->data[0][j]);
            for (size_t k = 1; k < collumn_1 / 2; ++k) {
                result->data[i][j] += (matrix_1->data[i][k << 1] + matrix_2->data[(k << 1) + 1][j]) *
                                      (matrix_1->data[i][(k << 1) + 1] + matrix_2->data[k << 1][j]);
            }
        }
    }

    if (collumn_1 % 2 == 1) {
        for (size_t i = 0; i < row_1; ++i) {
            for (size_t j = 0; j < collumn_2; ++j) {
                result->data[i][j] += matrix_1->data[i][collumn_1 - 1] * matrix_2->data[collumn_1 - 1][j];
            }
        }
    }

    free(col_factor);
    free(row_factor);

    return ERR_OK;
}

