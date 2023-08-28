#include "s21_tests.h"

START_TEST(matrix_1_1) {
  int rows = 1, columns = 1;
  const double a[] = {4};
  const double exp[] = {0.25};
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_2_2) {
  int rows = 2, columns = 2;
  const double a[] = {1, 3, 2, 4};
  const double exp[] = {-2, 1.5, 1, -0.5};
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_3_3) {
  int rows = 3, columns = 3;
  const double a[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  const double exp[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_4_4) {
  int rows = 4, columns = 4;
  const double a[] = {2, 3, 5, 1, 2, 4, -4, 4, 1, -5, 3, 2, 3, 4, 1, 0};
  const double exp[] = {-0.233766233766234,
                        -0.036796536796537,
                        0.19047619047619,
                        0.45021645021645,
                        0.12987012987013,
                        0.038961038961039,
                        -0.142857142857143,
                        -0.064935064935065,
                        0.181818181818182,
                        -0.045454545454545,
                        0,
                        -0.090909090909091,
                        0.168831168831169,
                        0.183982683982684,
                        0.047619047619048,
                        -0.251082251082251};
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_inrertible) {
  int rows = 2, columns = 2;
  const double a[] = {4, 2, 2, 1};
  matrix_t A = {0};
  matrix_t got = {0};
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_5_5) {
  int rows = 5, columns = 5;
  const double a[] = {2, 3, 5, 1, 6, 2, 4, -4, 4, 2, 1, -5, 3,
                      2, 3, 3, 4, 1, 0, 1, 2,  4, 0, 0, 4};
  const double exp[] = {
      -0.240601503759398, -0.047619047619048, 0.215538847117794,
      0.365914786967419,  0.131578947368421,  0.135338345864662,
      0.047619047619048,  -0.162907268170426, 0.00250626566416,
      -0.105263157894737, 0.195488721804511,  -0.023809523809524,
      -0.050125313283208, 0.077694235588972,  -0.263157894736842,
      0.18796992481203,   0.214285714285714,  -0.022556390977444,
      -0.015037593984962, -0.368421052631579, -0.015037593984962,
      -0.023809523809524, 0.055137844611529,  -0.18546365914787,
      0.289473684210526};
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_not_square) {
  int rows = 2, columns = 3;
  const double a[] = {4, 2, 2, 1, 0, -3};
  matrix_t A = {0};
  matrix_t got = {0};
  s21_create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = a[i * columns + j];
    }
  }

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), CALC_ERROR);
  s21_remove_matrix(&A);
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), INCORRECT_MATRIX);
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

  ck_assert_int_eq(s21_inverse_matrix(&A, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_inverse_matrix() {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("inverse_matrix_tc");
  tcase_add_test(tc, matrix_1_1);
  tcase_add_test(tc, matrix_2_2);
  tcase_add_test(tc, matrix_3_3);
  tcase_add_test(tc, matrix_4_4);
  tcase_add_test(tc, matrix_5_5);
  tcase_add_test(tc, matrix_inrertible);
  tcase_add_test(tc, matrix_not_square);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);

  suite_add_tcase(s, tc);
  return s;
}