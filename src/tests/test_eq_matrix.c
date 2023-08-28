#include "s21_tests.h"

START_TEST(random_true) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double value = randd(-1000, 1000);
      A.matrix[i][j] = value;
      B.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(random_true_eps) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double value = randd(-1000, 1000);
      A.matrix[i][j] = value;
      B.matrix[i][j] = value + 0.00000009;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(random_false) {
  int rows = rand() % 5 + 1;
  int columns = rand() % 5 + 1;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double value = randd(-1000, 1000);
      A.matrix[i][j] = value;
      B.matrix[i][j] = value + 0.0000002;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(diff_sizes) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;

  int d_rows = rows, d_columns = columns;

  while (d_rows == rows && d_columns == columns) {
    d_rows = rand() % 50 + 1;
    d_columns = rand() % 50 + 1;
  }

  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(d_rows, d_columns, &B);

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
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(zero_rows) {
  int rows = 0;
  int columns = 5;

  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

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
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(zero_columns) {
  int rows = 2;
  int columns = 0;

  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

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
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(zero_columns_2) {
  int rows = 2;
  int columns = 3;

  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, 0, &A);
  s21_create_matrix(rows, columns, &B);

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
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(diff_rows) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;

  int d_rows = rows;

  while (d_rows == rows) {
    d_rows = rand() % 50 + 1;
  }

  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(d_rows, columns, &B);

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
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null) {
  matrix_t A = {0}, B = {0};
  A.columns = 3;
  A.rows = 3;
  A.matrix = NULL;
  B.columns = 3;
  B.rows = 3;
  B.matrix = NULL;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_eq_matrix() {
  Suite *s = suite_create("suite_eq");
  TCase *tc = tcase_create("eq_tc");
  tcase_add_loop_test(tc, random_true, 0, 10);
  tcase_add_loop_test(tc, random_true_eps, 0, 10);
  tcase_add_loop_test(tc, random_false, 0, 10);
  tcase_add_loop_test(tc, diff_sizes, 0, 10);
  tcase_add_loop_test(tc, diff_rows, 0, 5);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);
  tcase_add_test(tc, zero_columns_2);
  tcase_add_test(tc, null);

  suite_add_tcase(s, tc);
  return s;
}