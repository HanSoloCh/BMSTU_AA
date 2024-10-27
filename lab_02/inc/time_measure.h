#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <time.h>

#include "error_t.h"
#include "matrix.h"
#include "matrix_mull.h"

typedef error_t(*mult_alg_t)(const matrix_t *, const matrix_t *, matrix_t *);

clock_t get_one_measure(mult_alg_t mult_func, const matrix_t *mtr_1, const matrix_t *mtr_2, matrix_t *res);

double get_measure_for_one_size(mult_alg_t func, size_t size, size_t count);

void make_all_measure(size_t max_size, size_t count);

void print_data(const double **data, size_t max_size);

#endif // TIME_MEASURE_H
