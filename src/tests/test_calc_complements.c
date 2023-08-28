#include "s21_tests.h"

START_TEST(matrix_2_2) {
  int rows = 2, columns = 2;
  const double a[] = {1, 3, 2, 4};
  const double exp[] = {4, -2, -3, 1};
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_3_3) {
  int rows = 3, columns = 3;
  const double a[] = {1.1, 2.3, 3, 3, 4, 5.9, 7.1, 2, 8};
  const double exp[] = {20.2,  17.89, -22.4, -12.4, -12.5,
                        14.13, 1.57,  2.51,  -2.5};
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_4_4) {
  int rows = 4, columns = 4;
  const double a[] = {1, 3, 4, 5, 7, 8, 6, 4, 3, 5, 2, 3, 1, 2, 9, 4};
  const double exp[] = {-72, 87,   30,  -93, -92, 70,  8,   -30,
                        168, -177, -18, 87,  56,  -46, -32, 42};
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_4_4_2) {
  int rows = 4, columns = 4;
  const double a[] = {2.4, 3.1, 9, 2.5, 2,  4, -1,   14,
                      5,   6,   1, 1,   45, 6, 87.1, 23};
  const double exp[] = {7108,   -5408.8,  -3376,    288.8,    95.21,  192.41,
                        500.2,  -2130.71, -3037.44, -2822.24, 1409.6, 1340.96,
                        -698.5, 593.5,    1.2,      -69.7};
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), OK);
  ck_assert_int_eq(s21_eq_matrix(&got, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(matrix_5_5) {
  int rows = 5, columns = 5;
  const double a[] = {5, 3, 4, 1, -2, -5, 8, 2, 4,  1, 7, 5, -2,
                      4, 1, 8, 5, 2,  9,  1, 3, -5, 2, 8, 4};
  const double exp[] = {-746,  -516,  -1851, 1630, -2420, 166,  -568,
                        -629,  470,   -1460, -940, -900,  -592, 1904,
                        -3932, 754,   788,   1671, -2730, 5044, -368,
                        -88,   -1038, 904,   -2676};
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), OK);
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), INCORRECT_MATRIX);
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
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

  ck_assert_int_eq(s21_calc_complements(&A, &got), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

Suite *suite_calc_complements() {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("calc_complements_tc");
  tcase_add_test(tc, matrix_2_2);
  tcase_add_test(tc, matrix_3_3);
  tcase_add_test(tc, matrix_4_4);
  tcase_add_test(tc, matrix_4_4_2);
  tcase_add_test(tc, matrix_5_5);
  tcase_add_test(tc, zero_columns);
  tcase_add_test(tc, zero_rows);
  tcase_add_test(tc, matrix_not_square);

  suite_add_tcase(s, tc);
  return s;
}