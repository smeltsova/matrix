#include "s21_tests.h"

START_TEST(correct_random) {
  int rows = rand() % 50 + 1;
  int columns = rand() % 50 + 1;
  matrix_t A;
  int return_value = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(return_value, OK);
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, columns);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j * j;
      ck_assert_double_eq_tol(i + j * j, A.matrix[i][j], PRECISION);
    }
  }
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(no_rows) {
  const int rows = 0;
  const int columns = 3;
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &A), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(no_columns) {
  const int rows = 5;
  const int columns = 0;

  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &A), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null) {
  const int rows = 5;
  const int columns = 7;

  ck_assert_int_eq(s21_create_matrix(rows, columns, NULL), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_create_matrix() {
  Suite *s = suite_create("suite_create");
  TCase *tc = tcase_create("create_tc");
  tcase_add_loop_test(tc, correct_random, 0, 10);
  tcase_add_test(tc, no_columns);
  tcase_add_test(tc, no_rows);
  tcase_add_test(tc, null);
  suite_add_tcase(s, tc);
  return s;
}