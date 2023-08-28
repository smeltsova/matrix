#include "s21_tests.h"

START_TEST(random_sum) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;
  matrix_t A = {0}, B = {0};
  matrix_t got = {0}, expected = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &expected);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = randd(-1000, 1000);
      B.matrix[i][j] = randd(-1000, 1000);
      expected.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(zero_columns) {
  int rows = 2;
  int columns = 0;

  matrix_t A = {0}, B = {0};
  matrix_t got = {0};
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
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(zero_rows) {
  int rows = 0;
  int columns = 7;

  matrix_t A = {0}, B = {0};
  matrix_t got = {0};
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
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(different_sizes_1) {
  int rows_a = 2, rows_b = 4;
  int columns_a = 4, columns_b = 2;

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
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &got), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(different_sizes_2) {
  int rows_a = 2, rows_b = 4;
  int columns_a = 2, columns_b = 2;

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
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &got), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(different_sizes_3) {
  int rows_a = 2, rows_b = 4;
  int columns_a = 4, columns_b = 4;

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
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &got), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_sum_matrix() {
  Suite *s = suite_create("suite_sum");
  TCase *tc = tcase_create("sum_tc");
  tcase_add_loop_test(tc, random_sum, 0, 50);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);
  tcase_add_test(tc, different_sizes_1);
  tcase_add_test(tc, different_sizes_2);
  tcase_add_test(tc, different_sizes_3);
  return s;
}