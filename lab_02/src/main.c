#include "matrix.h"
#include "matrix_read.h"
#include "matrix_alloc.h"
#include "matrix_mull.h"

#ifdef MEASURE
#include "time_measure.h"
#elif TEST
#include "check_main.h"
#endif


#include <stdio.h>


void matrix_mull_and_print(matrix_t *mtr_1, matrix_t *mtr_2, mull_mode mode);


int main(void) {
#ifdef MEASURE
    make_all_measure(50, 1000);
    return ERR_OK;
#elif TEST
    test_main();
#else
    matrix_t mtr_1;
    matrix_t mtr_2;
    printf("First matrix:\n");
    error_t rc = matrix_create(&mtr_1);
    if (rc == ERR_OK) {
        printf("Seond matrix\n");
        rc = matrix_create(&mtr_2);
    }

    if (rc == ERR_OK) {
        matrix_mull_and_print(&mtr_1, &mtr_2, DEFAULT);
        matrix_mull_and_print(&mtr_1, &mtr_2, VINOGRAD);
        matrix_mull_and_print(&mtr_1, &mtr_2, VINOGRAD_MODIFY);
        free_matrix_t(&mtr_1);
        free_matrix_t(&mtr_2);
    }


    return rc;
#endif
}

void matrix_mull_and_print(matrix_t *mtr_1, matrix_t *mtr_2, mull_mode mode) {
    error_t rc;
    matrix_t res;
    switch (mode) {
    case DEFAULT:
        printf("Default mult:\n");
        rc = matrix_mul(mtr_1, mtr_2, &res);
        break;
    case VINOGRAD:
        printf("Vinograd mult:\n");
        rc = vinograd_matrix_mul(mtr_1, mtr_2, &res);
        break;
    case VINOGRAD_MODIFY:
        printf("Vinograd modify mul:\n");
        rc = vinograd_modify_matrix_mul(mtr_1, mtr_2, &res);
        break;
    }

    if (rc == ERR_OK) {
        matrix_print(&res);
        free_matrix_t(&res);
    }
    else
        printf("ERROR");
}
