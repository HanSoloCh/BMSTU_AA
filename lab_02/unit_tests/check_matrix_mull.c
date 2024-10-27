#include "check_matrix_mull.h"

#include <check.h>

#include "matrix.h"
#include "matrix_alloc.h"
#include "matrix_mull.h"
#include "error_t.h"

test_status_t check_matrix(const matrix_t *matrix, const matrix_t *res) {
    if (matrix->collumn != res->collumn || matrix->row != res->row)
        return ASSERT_SIZES;

    for (size_t i = 0; i < matrix->row; ++i) {
        for (size_t j = 0; j < matrix->collumn; ++j) {
            if (matrix->data[i][j] != res->data[i][j])
                return ASSERT_ELEMENTS;
        }
    }
    return PASSED;
}

// __Стандартное умножение__

// Обычный тест
START_TEST(first_matrix_mull_test) {
    error_t rc;
    int data_a[][3] = {{2, -3, 1}, {5, 4, -2}};
    int *data_1[2] = {data_a[0], data_a[1]};
    matrix_t mtr_1 = {2, 3, data_1};

    int data_b[][2] = {{-7, 5}, {2, -1}, {4, 3}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 2, data_2};

    int data_c[][2] = {{-16, 16}, {-35, 15}};
    int *data_3[2] = {data_c[0], data_c[1]};
    matrix_t need_res = {2, 2, data_3};

    matrix_t cur_res;
    rc = matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(second_matrix_mull_test) {
    error_t rc;
    int data_a[][2] = {{-7, 5}, {2, -1}, {4, 3}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 2, data_1};

    int data_b[][3] = {{2, -3, 1}, {5, 4, -2}};
    int *data_2[2] = {data_b[0], data_b[1]};
    matrix_t mtr_2 = {2, 3, data_2};

    int data_c[][3] = {{11, 41, -17}, {-1, -10, 4}, {23, 0, -2}};
    int *data_3[3] = {data_c[0], data_c[1], data_c[2]};
    matrix_t need_res = {3, 3, data_3};

    matrix_t cur_res;
    rc = matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(third_matrix_mull_test) {
    error_t rc;
    int data_a[][2] = {{1, 2}, {3, 4}};
    int *data_1[2] = {data_a[0], data_a[1]};
    matrix_t mtr_1 = {2, 2, data_1};

    int data_b[][2] = {{1, 2}, {3, 4}};
    int *data_2[2] = {data_b[0], data_b[1]};
    matrix_t mtr_2 = {2, 2, data_2};

    int data_c[][2] = {{7, 10}, {15, 22}};
    int *data_3[2] = {data_c[0], data_c[1]};
    matrix_t need_res = {2, 2, data_3};

    matrix_t cur_res;
    rc = matrix_mul(&mtr_2, &mtr_1, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST


START_TEST(fourth_matrix_mull_test) {
    error_t rc;
    int data_a[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 3, data_1};

    int data_b[][1] = {{1}, {2}, {3}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 1, data_2};

    int data_c[][1] = {{14}, {32}, {50}};
    int *data_3[3] = {data_c[0], data_c[1], data_c[2]};
    matrix_t need_res = {3, 1, data_3};

    matrix_t cur_res;
    rc = matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(fifth_matrix_mull_test) {
    error_t rc;
    int data_a[][3] = {{1, 2, 3}};
    int *data_1[1] = {data_a[0]};
    matrix_t mtr_1 = {1, 3, data_1};

    int data_b[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 3, data_2};

    int data_c[][3] = {{30, 36, 42}};
    int *data_3[1] = {data_c[0]};
    matrix_t need_res = {1, 3, data_3};

    matrix_t cur_res;
    rc = matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(sixth_matrix_mull_test) {
    error_t rc;
    int data_a[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 2, data_1};

    int data_b[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 3, data_2};

    matrix_t cur_res;
    rc = matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST


Suite *matrix_mult_tests(void) {
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_test, *sixth_test;

    Suite *s = suite_create("\nMtr_mult_test");

    first_test = tcase_create("First_test");
    tcase_add_test(first_test, first_matrix_mull_test);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_matrix_mull_test);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_matrix_mull_test);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_matrix_mull_test);

    fifth_test = tcase_create("Fifth test");
    tcase_add_test(fifth_test, fifth_matrix_mull_test);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_matrix_mull_test);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_test);
    suite_add_tcase(s, sixth_test);

    return s;
}

// __Умножение Винограда__

// Обычный тест
START_TEST(first_vinograd_matrix_mul_test) {
    error_t rc;
    int data_a[][3] = {{2, -3, 1}, {5, 4, -2}};
    int *data_1[2] = {data_a[0], data_a[1]};
    matrix_t mtr_1 = {2, 3, data_1};

    int data_b[][2] = {{-7, 5}, {2, -1}, {4, 3}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 2, data_2};

    int data_c[][2] = {{-16, 16}, {-35, 15}};
    int *data_3[2] = {data_c[0], data_c[1]};
    matrix_t need_res = {2, 2, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(second_vinograd_matrix_mul_test) {
    error_t rc;
    int data_a[][2] = {{-7, 5}, {2, -1}, {4, 3}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 2, data_1};

    int data_b[][3] = {{2, -3, 1}, {5, 4, -2}};
    int *data_2[2] = {data_b[0], data_b[1]};
    matrix_t mtr_2 = {2, 3, data_2};

    int data_c[][3] = {{11, 41, -17}, {-1, -10, 4}, {23, 0, -2}};
    int *data_3[3] = {data_c[0], data_c[1], data_c[2]};
    matrix_t need_res = {3, 3, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(third_vinograd_matrix_mul_test) {
    error_t rc;
    int data_a[][2] = {{1, 2}, {3, 4}};
    int *data_1[2] = {data_a[0], data_a[1]};
    matrix_t mtr_1 = {2, 2, data_1};

    int data_b[][2] = {{1, 2}, {3, 4}};
    int *data_2[2] = {data_b[0], data_b[1]};
    matrix_t mtr_2 = {2, 2, data_2};

    int data_c[][2] = {{7, 10}, {15, 22}};
    int *data_3[2] = {data_c[0], data_c[1]};
    matrix_t need_res = {2, 2, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_2, &mtr_1, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST


START_TEST(fourth_vinograd_matrix_mul_test) {
    error_t rc;
    int data_a[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 3, data_1};

    int data_b[][1] = {{1}, {2}, {3}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 1, data_2};

    int data_c[][1] = {{14}, {32}, {50}};
    int *data_3[3] = {data_c[0], data_c[1], data_c[2]};
    matrix_t need_res = {3, 1, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(fifth_vinograd_matrix_mul_test) {
    error_t rc;
    int data_a[][3] = {{1, 2, 3}};
    int *data_1[1] = {data_a[0]};
    matrix_t mtr_1 = {1, 3, data_1};

    int data_b[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 3, data_2};

    int data_c[][3] = {{30, 36, 42}};
    int *data_3[1] = {data_c[0]};
    matrix_t need_res = {1, 3, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(sixth_vinograd_matrix_mul_test) {
    error_t rc;
    int data_a[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 2, data_1};

    int data_b[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 3, data_2};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST


Suite *vinograd_matrix_mul_tests(void) {
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_test, *sixth_test;

    Suite *s = suite_create("\nMtr_mult_test");

    first_test = tcase_create("First_test");
    tcase_add_test(first_test, first_vinograd_matrix_mul_test);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_vinograd_matrix_mul_test);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_vinograd_matrix_mul_test);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_vinograd_matrix_mul_test);

    fifth_test = tcase_create("Fifth test");
    tcase_add_test(fifth_test, fifth_vinograd_matrix_mul_test);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_vinograd_matrix_mul_test);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_test);
    suite_add_tcase(s, sixth_test);

    return s;
}


// __Умножение Винограда модифицированное__

// Обычный тест
START_TEST(first_vinograd_modify_matrix_mul_test) {
    error_t rc;
    int data_a[][3] = {{2, -3, 1}, {5, 4, -2}};
    int *data_1[2] = {data_a[0], data_a[1]};
    matrix_t mtr_1 = {2, 3, data_1};

    int data_b[][2] = {{-7, 5}, {2, -1}, {4, 3}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 2, data_2};

    int data_c[][2] = {{-16, 16}, {-35, 15}};
    int *data_3[2] = {data_c[0], data_c[1]};
    matrix_t need_res = {2, 2, data_3};

    matrix_t cur_res;
    rc = vinograd_modify_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(second_vinograd_modify_matrix_mul_test) {
    error_t rc;
    int data_a[][2] = {{-7, 5}, {2, -1}, {4, 3}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 2, data_1};

    int data_b[][3] = {{2, -3, 1}, {5, 4, -2}};
    int *data_2[2] = {data_b[0], data_b[1]};
    matrix_t mtr_2 = {2, 3, data_2};

    int data_c[][3] = {{11, 41, -17}, {-1, -10, 4}, {23, 0, -2}};
    int *data_3[3] = {data_c[0], data_c[1], data_c[2]};
    matrix_t need_res = {3, 3, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(third_vinograd_modify_matrix_mul_test) {
    error_t rc;
    int data_a[][2] = {{1, 2}, {3, 4}};
    int *data_1[2] = {data_a[0], data_a[1]};
    matrix_t mtr_1 = {2, 2, data_1};

    int data_b[][2] = {{1, 2}, {3, 4}};
    int *data_2[2] = {data_b[0], data_b[1]};
    matrix_t mtr_2 = {2, 2, data_2};

    int data_c[][2] = {{7, 10}, {15, 22}};
    int *data_3[2] = {data_c[0], data_c[1]};
    matrix_t need_res = {2, 2, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_2, &mtr_1, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST


START_TEST(fourth_vinograd_modify_matrix_mul_test) {
    error_t rc;
    int data_a[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 3, data_1};

    int data_b[][1] = {{1}, {2}, {3}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 1, data_2};

    int data_c[][1] = {{14}, {32}, {50}};
    int *data_3[3] = {data_c[0], data_c[1], data_c[2]};
    matrix_t need_res = {3, 1, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(fifth_vinograd_modify_matrix_mul_test) {
    error_t rc;
    int data_a[][3] = {{1, 2, 3}};
    int *data_1[1] = {data_a[0]};
    matrix_t mtr_1 = {1, 3, data_1};

    int data_b[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 3, data_2};

    int data_c[][3] = {{30, 36, 42}};
    int *data_3[1] = {data_c[0]};
    matrix_t need_res = {1, 3, data_3};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(check_matrix(&cur_res, &need_res), PASSED);

    free_matrix_t(&cur_res);
}
END_TEST

START_TEST(sixth_vinograd_modify_matrix_mul_test) {
    error_t rc;
    int data_a[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int *data_1[3] = {data_a[0], data_a[1], data_a[2]};
    matrix_t mtr_1 = {3, 2, data_1};

    int data_b[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int *data_2[3] = {data_b[0], data_b[1], data_b[2]};
    matrix_t mtr_2 = {3, 3, data_2};

    matrix_t cur_res;
    rc = vinograd_matrix_mul(&mtr_1, &mtr_2, &cur_res);
    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST


Suite *vinograd_modify_matrix_mul_tests(void) {
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_test, *sixth_test;

    Suite *s = suite_create("\nMtr_mult_test");

    first_test = tcase_create("First_test");
    tcase_add_test(first_test, first_vinograd_modify_matrix_mul_test);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_vinograd_modify_matrix_mul_test);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_vinograd_modify_matrix_mul_test);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_vinograd_modify_matrix_mul_test);

    fifth_test = tcase_create("Fifth test");
    tcase_add_test(fifth_test, fifth_vinograd_modify_matrix_mul_test);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_vinograd_modify_matrix_mul_test);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_test);
    suite_add_tcase(s, sixth_test);

    return s;
}

