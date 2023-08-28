#include "s21_tests.h"

START_TEST(matrix_1_1) {
  int rows = 1;
  int columns = 1;
  const double a[] = {265.76};
  matrix_t A = {0};
  double got = 0, expected = 265.76;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_2_2) {
  int rows = 2;
  int columns = 2;
  const double a[] = {4, 2, 9, 15};
  matrix_t A = {0};
  double got = 0, expected = 42;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_3_3) {
  int rows = 3;
  int columns = 3;
  const double a[] = {3, 9.1, 10.001, -4.1, -5.3, 9.46, 6.2, 32.1, 7.1};
  matrix_t A = {0};
  double got = 0, expected = -1212.85255;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_4_4) {
  int rows = 4;
  int columns = 4;
  const double a[] = {4, 8,  4, 0, -4, -5,  9.5, -17,
                      6, 32, 7, 0, 0,  100, 999, -7342};
  matrix_t A = {0};
  double got = 0, expected = 6489416;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_4_4_2) {
  int rows = 4;
  int columns = 4;
  const double a[] = {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1};
  matrix_t A = {0};
  double got = 0, expected = 3;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }
  ck_assert_int_eq(s21_determinant(&A, &got), OK);
  ck_assert_double_eq_tol(got, expected, PRECISION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(zero_columns) {
  int rows = 2;
  int columns = 0;

  matrix_t A = {0};
  double got = 0;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  ck_assert_int_eq(s21_determinant(&A, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(zero_rows) {
  int rows = 0;
  int columns = 7;

  matrix_t A = {0};
  double got = 0;
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  ck_assert_int_eq(s21_determinant(&A, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_determinant() {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("determinant_tc");
  tcase_add_test(tc, matrix_1_1);
  tcase_add_test(tc, matrix_2_2);
  tcase_add_test(tc, matrix_3_3);
  tcase_add_test(tc, matrix_4_4);
  tcase_add_test(tc, matrix_4_4_2);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);

  suite_add_tcase(s, tc);
  return s;
}