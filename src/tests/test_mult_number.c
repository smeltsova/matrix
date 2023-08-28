#include "s21_tests.h"

START_TEST(random_mult_number) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;
  float number = randd(1e-6, 1e6);
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = randd(-1000, 1000);
      expected.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_4_5) {
  int rows = 4, columns = 5;
  double number = 2.78;
  const double a[] = {5.2,  4.2,  6.2,  5.2, 7.2,  2.3, 4.2, -5.3, -8.1, 4.2,
                      -3.5, 6.32, 65.3, 5.3, 76.1, 76,  1,   0,    2,    0};
  const double exp[] = {14.456, 11.676,  17.236,  14.456,  20.016,
                        6.394,  11.676,  -14.734, -22.518, 11.676,
                        -9.73,  17.5696, 181.534, 14.734,  211.558,
                        211.28, 2.78,    0,       5.56,    0};
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
      expected.matrix[i][j] = exp[i * columns + j];
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, number, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(zero_columns) {
  int rows = 2;
  int columns = 0;

  double number = 3;

  matrix_t A = {0};
  matrix_t got = {0};
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, number, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(zero_rows) {
  int rows = 0;
  int columns = 7;

  double number = 3;

  matrix_t A = {0};
  matrix_t got = {0};
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, number, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_mult_number_matrix() {
  Suite *s = suite_create("suite_mult_number");
  TCase *tc = tcase_create("mult_number_tc");
  tcase_add_loop_test(tc, random_mult_number, 0, 50);
  tcase_add_test(tc, matrix_4_5);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);
  suite_add_tcase(s, tc);
  return s;
}