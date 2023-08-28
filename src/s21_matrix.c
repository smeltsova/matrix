#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (rows <= 0 || columns <= 0 || !result) {  //! result ?
    error = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (!(result->matrix)) {
      error = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows && error == OK; i++) {
        (result->matrix)[i] = (double *)calloc(columns, sizeof(double));
        if (!(result->matrix[i])) {
          error = INCORRECT_MATRIX;
          s21_remove_matrix(result);
        }
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    int rows = A->rows;
    if (A->matrix) {
      for (int i = 0; i < rows; i++) {
        if ((A->matrix)[i]) free((A->matrix)[i]);
      }
      free(A->matrix);
    }
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!is_correct(A) || !is_correct(B)) {
    result = FAILURE;
  } else {
    if ((A->rows != B->rows) || (A->columns != B->columns)) {
      result = FAILURE;
    }
    int rows = A->rows, columns = A->columns;
    for (int i = 0; result == SUCCESS && i < rows; i++) {
      for (int j = 0; result == SUCCESS && j < columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!is_correct(A) || !is_correct(B)) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = A->rows, columns = A->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!is_correct(A) || !is_correct(B)) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = A->rows, columns = A->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (!is_correct(A)) {
    error = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = A->rows, columns = A->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!is_correct(A) || !is_correct(B)) {
    error = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    error = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = A->rows, columns = B->columns, adds = A->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < adds; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (!is_correct(A)) {
    error = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = result->rows, columns = result->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (!is_correct(A)) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int n = A->rows;
    if (n == 1) {
      result->matrix[0][0] = 1;
    } else {
      double determinant = 0;
      for (int i = 0; error == OK && i < n; i++) {
        for (int j = 0; error == OK && j < n; j++) {
          matrix_t minor;
          if ((error = get_minor(A, i, j, &minor)) == OK) {
            if ((error = s21_determinant(&minor, &determinant)) == OK) {
              int sign = ((i + j) % 2 ? -1 : 1);
              result->matrix[i][j] = determinant * sign;
            }
          }
          s21_remove_matrix(&minor);
        }
      }
    }
  }

  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  if (!is_correct(A)) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else {
    int n = A->rows;
    if (n == 1) {
      *result = A->matrix[0][0];
    } else {
      matrix_t calc_complement;
      *result = 0;
      if ((error = s21_calc_complements(A, &calc_complement)) == OK) {
        int i = 0;
        for (int j = 0; j < n; j++) {
          *result += A->matrix[i][j] * calc_complement.matrix[i][j];
        }
      }
      s21_remove_matrix(&calc_complement);
    }
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  double determinant;
  matrix_t comp = {0}, transp = {0};
  if (!is_correct(A)) {
    error = INCORRECT_MATRIX;
  } else if ((error = s21_determinant(A, &determinant)) != OK) {
  } else if (determinant == 0) {
    error = CALC_ERROR;
  } else if (s21_calc_complements(A, &comp) != OK) {
    error = INCORRECT_MATRIX;
  } else if (s21_transpose(&comp, &transp) != OK) {
    error = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = result->rows, columns = result->columns;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = transp.matrix[i][j] / determinant;
      }
    }
  }
  s21_remove_matrix(&comp);
  s21_remove_matrix(&transp);
  return error;
}

int is_correct(matrix_t *A) {
  int result = SUCCESS;
  if (!A || A->rows <= 0 || A->columns <= 0 || !A->matrix) {
    result = FAILURE;
  }
  for (int i = 0; result == SUCCESS && i < A->rows; i++) {
    if (!A->matrix[i]) result = FAILURE;
  }
  return result;
}

int get_minor(matrix_t *A, int row, int column, matrix_t *result) {
  int error = OK;
  if (!is_correct(A)) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else if (!(0 <= row && row <= A->rows - 1) ||
             !(0 <= column && column <= A->columns - 1)) {
    error = CALC_ERROR;
  } else if (s21_create_matrix(A->rows - 1, A->columns - 1, result) != OK) {
    error = INCORRECT_MATRIX;
  } else {
    int rows = result->rows, columns = result->columns;
    int past_row = 0;
    for (int i = 0; i < rows; i++) {
      int past_column = 0;
      if (i == row) past_row = 1;
      for (int j = 0; j < columns; j++) {
        if (j == column) past_column = 1;
        result->matrix[i][j] = A->matrix[i + past_row][j + past_column];
      }
    }
  }
  return error;
}