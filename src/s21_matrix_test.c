#include "s21_matrix.h"

#include <check.h>
#include <stdio.h>

void s21_fill_matrix(matrix_t *val, double step) {
  double n = 0.0;
  for (int i = 0; i < val->rows; ++i) {
    for (int k = 0; k < val->columns; ++k) {
      val->matrix[i][k] = n;
      n += step;
    }
  }
}

// create matrix test
START_TEST(s21_create_test_1) {
  matrix_t res;
  ck_assert_int_eq(s21_create_matrix(5, 5, &res), 0);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_create_test_2) {
  matrix_t res;
  ck_assert_int_eq(s21_create_matrix(10, 15, &res), 0);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_create_test_3) {
  matrix_t res;
  ck_assert_int_eq(s21_create_matrix(0, 5, &res), 1);
}
END_TEST

START_TEST(s21_create_test_4) {
  matrix_t res;
  ck_assert_int_eq(s21_create_matrix(1, 0, &res), 1);
}
END_TEST

// equal tests
START_TEST(s21_eq_test_1) {
  matrix_t res1, res2;
  s21_create_matrix(5, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  s21_fill_matrix(&res1, 1.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&res1, &res2), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

START_TEST(s21_eq_test_2) {
  matrix_t res1, res2;
  s21_create_matrix(7, 9, &res1);
  s21_create_matrix(7, 9, &res2);

  s21_fill_matrix(&res1, 1.5);
  s21_fill_matrix(&res2, 1.5);

  ck_assert_int_eq(s21_eq_matrix(&res1, &res2), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

START_TEST(s21_eq_test_3) {
  matrix_t res1, res2;
  s21_create_matrix(5, 5, &res1);
  s21_create_matrix(2, 5, &res2);

  s21_fill_matrix(&res1, 1.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&res1, &res2), FAILURE);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

START_TEST(s21_eq_test_4) {
  matrix_t res1, res2;
  s21_create_matrix(5, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  s21_fill_matrix(&res1, 2.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&res1, &res2), FAILURE);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

// sum tests
START_TEST(s21_sum_test_1) {
  matrix_t res1, res2, res3;
  int compare = 1;

  s21_create_matrix(5, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  s21_fill_matrix(&res1, 2.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_sum_matrix(&res1, &res2, &res3), 0);

  for (int i = 0; i < res1.rows; ++i) {
    for (int k = 0; k < res1.columns; ++k) {
      if (res3.matrix[i][k] != res1.matrix[i][k] + res2.matrix[i][k]) {
        compare = 0;
      }
    }
  }

  ck_assert_int_eq(compare, 1);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_sum_test_2) {
  matrix_t res1, res2, res3;

  s21_create_matrix(3, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  ck_assert_int_eq(s21_sum_matrix(&res1, &res2, &res3), 2);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

START_TEST(s21_sum_test_3) {
  matrix_t res1, res2, res3;
  int compare = 1;

  s21_create_matrix(5, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  s21_fill_matrix(&res1, 15.0);
  s21_fill_matrix(&res2, 7.0);

  ck_assert_int_eq(s21_sum_matrix(&res1, &res2, &res3), 0);

  for (int i = 0; i < res1.rows; ++i) {
    for (int k = 0; k < res1.columns; ++k) {
      if (res3.matrix[i][k] != res1.matrix[i][k] + res2.matrix[i][k]) {
        compare = 0;
      }
    }
  }

  ck_assert_int_eq(compare, 1);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_sub_test_1) {
  matrix_t res1, res2, res3;
  int compare = 1;

  s21_create_matrix(5, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  s21_fill_matrix(&res1, 15.0);
  s21_fill_matrix(&res2, 7.0);

  ck_assert_int_eq(s21_sub_matrix(&res1, &res2, &res3), 0);

  for (int i = 0; i < res1.rows; ++i) {
    for (int k = 0; k < res1.columns; ++k) {
      if (res3.matrix[i][k] != res1.matrix[i][k] - res2.matrix[i][k]) {
        compare = 0;
      }
    }
  }

  ck_assert_int_eq(compare, 1);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_sub_test_2) {
  matrix_t res1, res2, res3;
  int compare = 1;

  s21_create_matrix(3, 5, &res1);
  s21_create_matrix(3, 5, &res2);

  s21_fill_matrix(&res1, 2.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_sub_matrix(&res1, &res2, &res3), 0);

  for (int i = 0; i < res1.rows; ++i) {
    for (int k = 0; k < res1.columns; ++k) {
      if (res3.matrix[i][k] != res1.matrix[i][k] - res2.matrix[i][k]) {
        compare = 0;
      }
    }
  }

  ck_assert_int_eq(compare, 1);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_sub_test_3) {
  matrix_t res1, res2, res3;

  s21_create_matrix(3, 5, &res1);
  s21_create_matrix(5, 5, &res2);

  ck_assert_int_eq(s21_sub_matrix(&res1, &res2, &res3), 2);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

// mult num tests
START_TEST(s21_mult_num_test_1) {
  matrix_t res1, res2, res3;
  double mult = 10.0;

  s21_create_matrix(3, 5, &res1);
  s21_fill_matrix(&res1, 2.0);
  ck_assert_int_eq(s21_mult_number(&res1, mult, &res2), 0);

  s21_create_matrix(3, 5, &res3);
  s21_fill_matrix(&res3, 2.0 * mult);

  ck_assert_int_eq(s21_eq_matrix(&res2, &res3), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_mult_num_test_2) {
  matrix_t res1, res2, res3;
  double mult = 2.5;

  s21_create_matrix(7, 5, &res1);
  s21_fill_matrix(&res1, 2.0);
  ck_assert_int_eq(s21_mult_number(&res1, mult, &res2), 0);

  s21_create_matrix(7, 5, &res3);
  s21_fill_matrix(&res3, 2.0 * mult);

  ck_assert_int_eq(s21_eq_matrix(&res2, &res3), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_mult_num_test_3) {
  matrix_t res1, res2, res3;
  double mult = 0.0;

  s21_create_matrix(3, 5, &res1);
  s21_fill_matrix(&res1, 2.0);
  ck_assert_int_eq(s21_mult_number(&res1, mult, &res2), 0);

  s21_create_matrix(3, 5, &res3);
  s21_fill_matrix(&res3, 2.0 * mult);

  ck_assert_int_eq(s21_eq_matrix(&res2, &res3), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
}
END_TEST

START_TEST(s21_mult_test_1) {
  matrix_t res1, res2, res3, orig;

  s21_create_matrix(3, 3, &res1);
  s21_create_matrix(3, 3, &res2);
  s21_fill_matrix(&res1, 2.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_mult_matrix(&res1, &res2, &res3), 0);

  double m[3][3] = {{30, 36, 42}, {84, 108, 132}, {138, 180, 222}};
  s21_create_matrix(3, 3, &orig);

  for (int i = 0; i < res1.rows; ++i) {
    for (int k = 0; k < res1.columns; ++k) {
      orig.matrix[i][k] = m[i][k];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&orig, &res3), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
  s21_remove_matrix(&orig);
}
END_TEST

START_TEST(s21_mult_test_2) {
  matrix_t res1, res2, res3, orig;

  s21_create_matrix(2, 3, &res1);
  s21_create_matrix(3, 2, &res2);
  s21_fill_matrix(&res1, 2.0);
  s21_fill_matrix(&res2, 1.0);

  ck_assert_int_eq(s21_mult_matrix(&res1, &res2, &res3), 0);

  double m[3][3] = {{20, 26}, {56, 80}};
  s21_create_matrix(2, 2, &orig);

  for (int i = 0; i < res1.rows; ++i) {
    for (int k = 0; k < res1.columns; ++k) {
      orig.matrix[i][k] = m[i][k];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&orig, &res3), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&res3);
  s21_remove_matrix(&orig);
}
END_TEST

START_TEST(s21_mult_test_3) {
  matrix_t res1, res2, res3;

  s21_create_matrix(3, 2, &res1);
  s21_create_matrix(3, 3, &res2);
  s21_fill_matrix(&res1, 2.0);
  s21_fill_matrix(&res1, 1.0);

  ck_assert_int_eq(s21_mult_matrix(&res1, &res2, &res3), 2);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
}
END_TEST

// transpose matrix test
START_TEST(s21_transpose_test_1) {
  matrix_t res1, res2, orig;

  s21_create_matrix(3, 2, &res1);
  s21_fill_matrix(&res1, 1.0);
  ck_assert_int_eq(s21_transpose(&res1, &res2), 0);

  double m[3][3] = {{0, 2, 4}, {1, 3, 5}};
  s21_create_matrix(2, 3, &orig);

  for (int i = 0; i < orig.rows; ++i) {
    for (int k = 0; k < orig.columns; ++k) {
      orig.matrix[i][k] = m[i][k];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&orig, &res2), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&orig);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t res1, res2, orig;

  s21_create_matrix(3, 3, &res1);
  s21_fill_matrix(&res1, 1.0);
  ck_assert_int_eq(s21_transpose(&res1, &res2), 0);

  double m[3][3] = {{0, 3, 6}, {1, 4, 7}, {2, 5, 8}};
  s21_create_matrix(3, 3, &orig);

  for (int i = 0; i < orig.rows; ++i) {
    for (int k = 0; k < orig.columns; ++k) {
      orig.matrix[i][k] = m[i][k];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&orig, &res2), SUCCESS);

  s21_remove_matrix(&res1);
  s21_remove_matrix(&res2);
  s21_remove_matrix(&orig);
}
END_TEST

// determ tests
START_TEST(s21_det_test_1) {
  matrix_t val;
  double d;

  double m[3][3] = {{0, 10, -2}, {-4, 4, 56}, {6, 8, 8}};
  s21_create_matrix(3, 3, &val);

  for (int i = 0; i < val.rows; ++i) {
    for (int k = 0; k < val.columns; ++k) {
      val.matrix[i][k] = m[i][k];
    }
  }

  ck_assert_int_eq(s21_determinant(&val, &d), 0);
  ck_assert_int_eq(d, 3792.0);

  s21_remove_matrix(&val);
}
END_TEST

START_TEST(s21_det_test_2) {
  matrix_t val;
  double d;

  s21_create_matrix(5, 3, &val);
  ck_assert_int_eq(s21_determinant(&val, &d), 2);
  s21_remove_matrix(&val);
}
END_TEST

START_TEST(s21_det_test_3) {
  matrix_t val;
  double d;

  double m[3][3] = {{6, 10}, {-4, 47}};
  s21_create_matrix(2, 2, &val);

  for (int i = 0; i < val.rows; ++i) {
    for (int k = 0; k < val.columns; ++k) {
      val.matrix[i][k] = m[i][k];
    }
  }

  ck_assert_int_eq(s21_determinant(&val, &d), 0);
  ck_assert_int_eq(d, 322.0);

  s21_remove_matrix(&val);
}
END_TEST

// inverse tests
START_TEST(s21_inverse_test_1) {
  matrix_t val, res, orig;

  s21_create_matrix(3, 3, &val);
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  for (int i = 0; i < val.rows; ++i) {
    for (int k = 0; k < val.columns; ++k) {
      val.matrix[i][k] = m[i][k];
    }
  }

  ck_assert_int_eq(s21_inverse_matrix(&val, &res), 0);

  s21_create_matrix(3, 3, &orig);
  double n[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  for (int i = 0; i < orig.rows; ++i) {
    for (int k = 0; k < orig.columns; ++k) {
      orig.matrix[i][k] = n[i][k];
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&orig, &res), SUCCESS);

  s21_remove_matrix(&res);
  s21_remove_matrix(&val);
  s21_remove_matrix(&orig);
}
END_TEST

START_TEST(s21_inverse_test_2) {
  matrix_t val, res;

  s21_create_matrix(3, 3, &val);
  s21_fill_matrix(&val, 2.0);

  ck_assert_int_eq(s21_inverse_matrix(&val, &res), 2);

  s21_remove_matrix(&val);
}
END_TEST

START_TEST(s21_inverse_test_3) {
  matrix_t val, res;

  s21_create_matrix(1, 1, &val);
  val.matrix[0][0] = 2.0;

  ck_assert_int_eq(s21_inverse_matrix(&val, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 0.5);

  s21_remove_matrix(&val);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_inverse_suite(void) {
  TCase *tc = tcase_create("s21_inverse_core");
  Suite *s = suite_create("s21_inverse_tests");

  tcase_add_test(tc, s21_inverse_test_1);
  tcase_add_test(tc, s21_inverse_test_2);
  tcase_add_test(tc, s21_inverse_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_det_suite(void) {
  TCase *tc = tcase_create("s21_det_core");
  Suite *s = suite_create("s21_det_tests");

  tcase_add_test(tc, s21_det_test_1);
  tcase_add_test(tc, s21_det_test_2);
  tcase_add_test(tc, s21_det_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_transpose_suite(void) {
  TCase *tc = tcase_create("s21_transpose_core");
  Suite *s = suite_create("s21_transpose_tests");

  tcase_add_test(tc, s21_transpose_test_1);
  tcase_add_test(tc, s21_transpose_test_2);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_mult_suite(void) {
  TCase *tc = tcase_create("s21_mult_core");
  Suite *s = suite_create("s21_mult_tests");

  tcase_add_test(tc, s21_mult_test_1);
  tcase_add_test(tc, s21_mult_test_2);
  tcase_add_test(tc, s21_mult_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_mult_num_suite(void) {
  TCase *tc = tcase_create("s21_mult_num_core");
  Suite *s = suite_create("s21_mult_num_tests");

  tcase_add_test(tc, s21_mult_num_test_1);
  tcase_add_test(tc, s21_mult_num_test_2);
  tcase_add_test(tc, s21_mult_num_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sub_suite(void) {
  TCase *tc = tcase_create("s21_sub_core");
  Suite *s = suite_create("s21_sub_tests");

  tcase_add_test(tc, s21_sub_test_1);
  tcase_add_test(tc, s21_sub_test_2);
  tcase_add_test(tc, s21_sub_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_sum_suite(void) {
  TCase *tc = tcase_create("s21_sum_core");
  Suite *s = suite_create("s21_sum_tests");

  tcase_add_test(tc, s21_sum_test_1);
  tcase_add_test(tc, s21_sum_test_2);
  tcase_add_test(tc, s21_sum_test_3);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_eq_suite(void) {
  TCase *tc = tcase_create("s21_eq_core");
  Suite *s = suite_create("s21_eq_tests");

  tcase_add_test(tc, s21_eq_test_1);
  tcase_add_test(tc, s21_eq_test_2);
  tcase_add_test(tc, s21_eq_test_3);
  tcase_add_test(tc, s21_eq_test_4);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_create_suite(void) {
  TCase *tc = tcase_create("s21_create_core");
  Suite *s = suite_create("s21_create_tests");

  tcase_add_test(tc, s21_create_test_1);
  tcase_add_test(tc, s21_create_test_2);
  tcase_add_test(tc, s21_create_test_3);
  tcase_add_test(tc, s21_create_test_4);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  SRunner *sr;

  sr = srunner_create(s21_create_suite());
  srunner_add_suite(sr, s21_eq_suite());
  srunner_add_suite(sr, s21_sum_suite());
  srunner_add_suite(sr, s21_sub_suite());
  srunner_add_suite(sr, s21_mult_num_suite());
  srunner_add_suite(sr, s21_mult_suite());
  srunner_add_suite(sr, s21_transpose_suite());
  srunner_add_suite(sr, s21_det_suite());
  srunner_add_suite(sr, s21_inverse_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 1 : 0;
}
