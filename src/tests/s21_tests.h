#ifndef SRC_TESTS_S21_TESTS_H_
#define SRC_TESTS_S21_TESTS_H_

#include <check.h>
#include <limits.h>
#include <time.h>

#include "../s21_matrix.h"

#define PRECISION 1e-6

Suite *suite_create_matrix();
Suite *suite_eq_matrix();
Suite *suite_sum_matrix();
Suite *suite_sub_matrix();
Suite *suite_mul_matrix();
Suite *suite_mult_number_matrix();
Suite *suite_transpose_matrix();
Suite *suite_determinant();
Suite *suite_calc_complements();
Suite *suite_inverse_matrix();

void run_tests();
void run_testcase(Suite *testcase);
double randd(double min, double max);

#endif  // SRC_TESTS_S21_TESTS_H_