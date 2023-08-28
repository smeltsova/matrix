#include "s21_tests.h"

START_TEST(random_transpose) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);

  s21_create_matrix(columns, rows, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = randd(-1000, 1000);
      expected.matrix[j][i] = A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_3_4) {
  int rows = 3, columns = 4;

  const double a[] = {3,    9.1, 10.001, 9.2,  -4.1, -5.3,
                      9.46, 34,  6.2,    32.1, 7.1,  8.3};
  const double exp[] = {3,      -4.1, 6.2, 9.1, -5.3, 32.1,
                        10.001, 9.46, 7.1, 9.2, 34,   8.3};
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }

  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      expected.matrix[i][j] = exp[i * rows + j];
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_5_4) {
  int rows = 5, columns = 4;

  const double a[] = {5.2,  4.2,  6.2,  5.2, 7.2,  2.3, 4.2, -5.3, -8.1, 4.2,
                      -3.5, 6.32, 65.3, 5.3, 76.1, 76,  1,   0,    2,    0};
  const double exp[] = {5.2, 7.2, -8.1, 65.3, 1, 4.2, 2.3,  4.2,  5.3, 0,
                        6.2, 4.2, -3.5, 76.1, 2, 5.2, -5.3, 6.32, 76,  0};
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }

  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      expected.matrix[i][j] = exp[i * rows + j];
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_1_5) {
  int rows = 1, columns = 5;

  const double a[] = {5.2, 4.2, 6.2, 5.2, 6};
  const double exp[] = {5.2, 4.2, 6.2, 5.2, 6};
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }

  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      expected.matrix[i][j] = exp[i * rows + j];
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_5_1) {
  int rows = 5, columns = 1;

  const double a[] = {5.2, 4.2, 6.2, 5.2, 6};
  const double exp[] = {5.2, 4.2, 6.2, 5.2, 6};
  matrix_t A = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }

  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      expected.matrix[i][j] = exp[i * rows + j];
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(zero_columns) {
  int rows = 2;
  int columns = 0;

  matrix_t A = {0};
  matrix_t got = {0};
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(zero_rows) {
  int rows = 0;
  int columns = 7;

  matrix_t A = {0};
  matrix_t got = {0};
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 10;
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST
Suite *suite_transpose_matrix() {
  Suite *s = suite_create("suite_transpose");
  TCase *tc = tcase_create("transpose_tc");
  tcase_add_loop_test(tc, random_transpose, 0, 50);
  tcase_add_test(tc, matrix_1_5);
  tcase_add_test(tc, matrix_3_4);
  tcase_add_test(tc, matrix_5_1);
  tcase_add_test(tc, matrix_5_4);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);

  suite_add_tcase(s, tc);
  return s;
}