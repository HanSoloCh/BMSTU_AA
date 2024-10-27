#include "matrix_read.h"

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_alloc.h"
#include "error_t.h"


void matrix_fill(matrix_t *matrix) {
    for (size_t i = 0; i < matrix->row; ++i)
        for (size_t j = 0; j < matrix->collumn; ++j)
            matrix->data[i][j] = rand();
}


error_t matrix_create_random(matrix_t *matrix, size_t n, size_t m) {
    matrix_t tmp_matrix;
    error_t rc = alloc_matrix_t(&tmp_matrix, n, m);
    if (rc == ERR_OK) {
        matrix_fill(&tmp_matrix);
    }
    if (rc == ERR_OK)
        *matrix = tmp_matrix;
    return rc;
}

error_t matrix_read(matrix_t *matrix) {
    error_t rc = ERR_OK;
    for (size_t i = 0; i < matrix->row && rc == ERR_OK; ++i)
        for (size_t j = 0; j < matrix->collumn && rc == ERR_OK; ++j)
            if (scanf("%d", &matrix->data[i][j]) != 1)
                rc = ERR_IO;
    return rc;
}

error_t matrix_create(matrix_t *matrix) {
    error_t rc = ERR_OK;
    size_t n, m;
    printf("Input sizes: ");
    if (scanf("%zu %zu", &n, &m) != 2)
        rc = ERR_IO;
    else {
        matrix_t tmp_matrix;
        rc = alloc_matrix_t(&tmp_matrix, n, m);
        if (rc == ERR_OK) {
            printf("Input matrix:\n");
            rc = matrix_read(&tmp_matrix);
            if (rc)
                free_matrix_t(&tmp_matrix);
        }
        if (rc == ERR_OK)
            *matrix = tmp_matrix;
    }
    return rc;
}

void matrix_print(matrix_t *matrix) {
    for (size_t i = 0; i < matrix->row; ++i) {
        for (size_t j = 0; j < matrix->collumn; ++j)
            printf("%d ", matrix->data[i][j]);

        printf("\n");
    }
}
