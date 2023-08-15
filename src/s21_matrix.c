#include "s21_matrix.h"

void s21_fill_matrix(matrix_t *val, double step);

int s21_incorrect_matrix(matrix_t *value) {
  int res = 0;
  if (value->rows <= 0 || value->columns <= 0 || value->matrix == NULL ||
      value == NULL) {
    res = 1;
  }
  return res;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  int memory_error = 0;
  if (rows <= 0 || columns <= 0) {
    res = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) memory_error = 1;

    for (int i = 0; i < rows && !memory_error; ++i) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) memory_error = 1;
    }
  }
  return res;
}

// если освобождается нулевой указатель, ничего не присходит и ошибки нет
void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) res = FAILURE;
  long double temp_a, temp_b;
  for (int i = 0; i < A->rows && res; ++i) {
    for (int k = 0; k < A->columns && res; ++k) {
      temp_a = A->matrix[i][k] * pow(10, 7);
      temp_b = B->matrix[i][k] * pow(10, 7);
      if (trunc(temp_a) != trunc(temp_b)) res = FAILURE;
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (s21_incorrect_matrix(A) || s21_incorrect_matrix(B)) res = 1;
  if (A->rows != B->rows || A->columns != B->columns) res = 2;

  if (!res) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[i][k] = A->matrix[i][k] + B->matrix[i][k];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (s21_incorrect_matrix(A) || s21_incorrect_matrix(B)) res = 1;
  if (A->rows != B->rows || A->columns != B->columns) res = 2;

  if (!res) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[i][k] = A->matrix[i][k] - B->matrix[i][k];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (s21_incorrect_matrix(A)) res = 1;
  if (!res) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[i][k] = A->matrix[i][k] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (s21_incorrect_matrix(A)) res = 1;
  if (A->columns != B->rows) res = 2;
  if (!res) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int k = 0; k < B->columns; ++k) {
        for (int n = 0; n < A->columns; ++n) {
          result->matrix[i][k] += A->matrix[i][n] * B->matrix[n][k];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;

  if (s21_incorrect_matrix(A))
    res = 1;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[k][i] = A->matrix[i][k];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (s21_incorrect_matrix(A)) res = 1;
  if (A->rows != A->columns) res = 2;

  if (!res) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = s21_find_det(A);
    }
  }

  return res;
}

double s21_find_det(matrix_t *val) {
  double det = 0.0;

  if (val->rows == 1) {
    return val->matrix[0][0];
  } else {
    for (int i = 0; i < val->rows; ++i) {
      matrix_t temp_minor;

      s21_minor(val, &temp_minor, 0, i);
      det += pow(-1, i) * val->matrix[0][i] * s21_find_det(&temp_minor);
      s21_remove_matrix(&temp_minor);
    }
  }
  return det;
}

//если col больше макс индекса все равно отсекается последний столбец, но почему
void s21_minor(matrix_t *matrix, matrix_t *minor, int row, int col) {
  s21_create_matrix(matrix->rows - 1, matrix->rows - 1, minor);

  for (int i = 0, n = 0; i < matrix->rows; ++i, ++n) {
    if (i == row) {
      n--;
      continue;
    }

    for (int k = 0, m = 0; k < matrix->columns; ++k, ++m) {
      if (k == col) {
        m--;
        continue;
      } else
        minor->matrix[n][m] = matrix->matrix[i][k];
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (s21_incorrect_matrix(A)) res = 1;
  if (A->rows != A->columns) res = 2;

  if (!res) {
    s21_create_matrix(A->rows, A->columns, result);
    if (result->rows == 1)
      result->matrix[0][0] = 1;
    else {
      for (int i = 0; i < A->rows; ++i) {
        for (int k = 0; k < A->columns; ++k) {
          matrix_t temp_minor;
          s21_minor(A, &temp_minor, i, k);
          result->matrix[i][k] = pow(-1, i + k) * s21_find_det(&temp_minor);
          s21_remove_matrix(&temp_minor);
        }
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (s21_incorrect_matrix(A)) res = 1;
  if (A->rows != A->columns) res = 2;

  if (!res) {
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det) < 1e-6 || det == 0) {
      res = 2;
    } else {
      if (A->rows == 1) {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        matrix_t compl, transposed;

        s21_calc_complements(A, &compl );
        s21_transpose(&compl, &transposed);
        s21_mult_number(&transposed, 1 / det, result);
        s21_remove_matrix(&compl );
        s21_remove_matrix(&transposed);
      }
    }
  }
  return res;
}