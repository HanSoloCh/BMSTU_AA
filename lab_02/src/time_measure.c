#include "time_measure.h"

#include <time.h>
#include <stdio.h>

#include "matrix.h"
#include "matrix_alloc.h"
#include "matrix_read.h"
#include "error_t.h"


static mult_alg_t func[] =
{
    matrix_mul,
    vinograd_matrix_mul,
    vinograd_modify_matrix_mul
};

static char *func_names[] =
{
    "deafault",
    "vinograd",
    "vinograd_modify"
};


clock_t get_one_measure(mult_alg_t mult_func, const matrix_t *mtr_1, const matrix_t *mtr_2, matrix_t *res) {
    clock_t start = clock();
    (*mult_func)(mtr_1, mtr_2, res);
    clock_t end = clock();
    return end - start;
}

double get_measure_for_one_size(mult_alg_t func, size_t size, size_t count) {
    matrix_t mtr_1, mtr_2, res;
    error_t rc = matrix_create_random(&mtr_1, size, size);
    if (rc == ERR_OK) {
        rc = matrix_create_random(&mtr_2, size, size);
        if (rc)
            free_matrix_t(&mtr_1);
    }

    clock_t time = 0;
    for (size_t i = 0; i < count; ++i) {
        time += get_one_measure(func, &mtr_1, &mtr_2, &res);
    }
    free_matrix_t(&mtr_1);
    free_matrix_t(&mtr_2);
    free_matrix_t(&res);
    return time * 1E+9 / CLOCKS_PER_SEC / count;
}

void make_all_measure(size_t max_size, size_t count) {
    double **data = alloc_matrix_double(sizeof(func) / sizeof(*func), max_size + 1);
    if (data == NULL)
        return;

    for (size_t i = 0; i < sizeof(func) / sizeof(mult_alg_t); ++i) {
        for (size_t j = 2; j <= max_size; ++j)
            data[i][j] = get_measure_for_one_size(func[i], j, count);
    }
    print_data((const double **)data, max_size);
    free_martrix_double(&data, sizeof(func) / sizeof(*func));
}

void print_data(const double **data, size_t max_size) {
    printf("%s|%s|%s|%s\n", "size", func_names[0], func_names[1], func_names[2]);
    for (size_t i = 2; i <= max_size; ++i)
        printf("%zu|%lf|%lf|%lf\n", i, data[0][i], data[1][i], data[2][i]);
}
