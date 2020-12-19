#include "../Solver/Matrix/Utility.h"
#include "check.h"
#include <stdio.h>

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

START_TEST(test_det)
{
    Matrix tmp = createMatrix(2,2);
    tmp.matrix[0][0] = 2.0;
    tmp.matrix[0][1] = 2.0;
    tmp.matrix[1][0] = 2.0;
    tmp.matrix[1][1] = 2.0;
    int dimension = getDimension(&tmp);
    int det = determinant(&tmp, dimension);
    ck_assert(det == 0);
}
END_TEST

START_TEST(test_multiply)
{
    Matrix Matrix_1 = createMatrix(2,2);
    Matrix_1.matrix[0][0] = 2.0;
    Matrix_1.matrix[0][1] = 2.0;
    Matrix_1.matrix[1][0] = 2.0;
    Matrix_1.matrix[1][1] = 2.0;
    Matrix Matrix_2 = createMatrix(2,2);
    Matrix_2.matrix[0][0] = 2.0;
    Matrix_2.matrix[0][1] = 2.0;
    Matrix_2.matrix[1][0] = 2.0;
    Matrix_2.matrix[1][1] = 2.0;
    Matrix multiplied = multiply(&Matrix_1, &Matrix_2);
    printf("test: %f", multiplied.matrix[0][0]);
    ck_assert(multiplied.matrix[0][0] == 8.0);
    ck_assert(multiplied.matrix[1][0] == 8.0);
    ck_assert(multiplied.matrix[0][1] == 8.0);
    ck_assert(multiplied.matrix[1][1] == 8.0);
}
END_TEST

#endif
