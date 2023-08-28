#include "s21_tests.h"

START_TEST(matrix_3_3) {
  int rows = 3;
  int columns = 3;
  const double a[] = {1, 2, 3.3, 4.25, -5, 6, 5, 3, -7};
  const double b[] = {6.8, 1.5, 8, 34, -8, 1.2, 8.1, 9.4, 100};
  const double exp[] = {101.53, 16.52, 340.4, -92.5, 102.775,
                        628,    79.3,  -82.3, -656.4};
  matrix_t A = {0}, B = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
      B.matrix[i][j] = b[i * columns + j];
      expected.matrix[i][j] = exp[i * columns + j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_3_4_4_5) {
  int rows_a = 3, columns_a = 4;
  int rows_b = 4, columns_b = 5;
  int rows_exp = 3, columns_exp = 5;
  const double a[] = {3,    9.1, 10.001, 9.2,  -4.1, -5.3,
                      9.46, 34,  6.2,    32.1, 7.1,  8.3};
  const double b[] = {5.2,  4.2,  6.2,  5.2, 7.2,  2.3, 4.2, -5.3, -8.1, 4.2,
                      -3.5, 6.32, 65.3, 5.3, 76.1, 76,  1,   0,    2,    0};
  const double exp[] = {700.7265, 123.22632, 623.4353, 13.2953, 820.8961,
                        2517.38,  54.3072,   620.408,  139.748, 668.126,
                        712.02,   214.032,   331.94,   -173.54, 719.77};
  matrix_t A = {0}, B = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows_a, columns_a, &A);
  s21_create_matrix(rows_b, columns_b, &B);
  s21_create_matrix(rows_exp, columns_exp, &expected);

  for (int i = 0; i < rows_a; i++) {
    for (int j = 0; j < columns_a; j++) {
      A.matrix[i][j] = a[i * columns_a + j];
    }
  }

  for (int i = 0; i < rows_b; i++) {
    for (int j = 0; j < columns_b; j++) {
      B.matrix[i][j] = b[i * columns_b + j];
    }
  }
  for (int i = 0; i < rows_exp; i++) {
    for (int j = 0; j < columns_exp; j++) {
      expected.matrix[i][j] = exp[i * columns_exp + j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(zero_columns) {
  int rows_a = 3, columns_a = 0;
  int rows_b = 0, columns_b = 5;

  matrix_t A = {0}, B = {0};
  matrix_t got = {0};

  s21_create_matrix(rows_a, columns_a, &A);
  s21_create_matrix(rows_b, columns_b, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = 10;
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(zero_rows) {
  int rows_a = 0, columns_a = 7;
  int rows_b = 7, columns_b = 0;

  matrix_t A = {0}, B = {0};
  matrix_t got = {0};

  s21_create_matrix(rows_a, columns_a, &A);
  s21_create_matrix(rows_b, columns_b, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = 10;
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mismatched_sizes) {
  int rows_a = 4, columns_a = 2;
  int rows_b = 3, columns_b = 4;

  matrix_t A = {0}, B = {0};
  matrix_t got = {0};

  s21_create_matrix(rows_a, columns_a, &A);
  s21_create_matrix(rows_b, columns_b, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = 10;
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &got), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_mul_matrix() {
  Suite *s = suite_create("suite_mul");
  TCase *tc = tcase_create("mul_tc");
  tcase_add_test(tc, matrix_3_3);
  tcase_add_test(tc, matrix_3_4_4_5);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);
  tcase_add_test(tc, mismatched_sizes);

  suite_add_tcase(s, tc);
  return s;
}