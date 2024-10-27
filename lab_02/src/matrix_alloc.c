#include "matrix.h"
#include "matrix_alloc.h"
#include "error_t.h"
#include <stdlib.h>

error_t alloc_matrix_t(matrix_t *matrix, size_t n, size_t m) {
    int **data = alloc_matrix(n, m);
    if (data == NULL)
        return ERR_MEM;
    matrix->data = data;
    matrix->row = n;
    matrix->collumn = m;
    return ERR_OK;
}

void free_matrix_t(matrix_t *matrix) {
    free_martrix(&matrix->data, matrix->row);
    matrix->collumn = 0;
    matrix->row = 0;
}

int **alloc_matrix(size_t n, size_t m) {
    int **data = calloc(n, sizeof(int *));
    if (data == NULL)
        return NULL;
    for (size_t i = 0; i < n; ++i) {
        data[i] = malloc(sizeof(int) * m);
        if (data[i] == NULL) {
            free_martrix(&data, i);
            return NULL;
        }
    }
    return data;
}

double **alloc_matrix_double(size_t n, size_t m) {
    double **data = calloc(n, sizeof(double *));
    if (data == NULL)
        return NULL;
    for (size_t i = 0; i < n; ++i) {
        data[i] = malloc(sizeof(double) * m);
        if (data[i] == NULL) {
            free_martrix_double(&data, i);
            return NULL;
        }
    }
    return data;
}

void free_martrix(int ***data, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        free((*data)[i]);
    }
    free(*data);
    *data = NULL;
}

void free_martrix_double(double ***data, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        free((*data)[i]);
    }
    free(*data);
    *data = NULL;
}


