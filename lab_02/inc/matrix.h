#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct {
    size_t row;
    size_t collumn;
    int **data;
} matrix_t;

#endif // MATRIX_H
