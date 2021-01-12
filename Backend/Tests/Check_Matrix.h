#include "../Solver/Matrix/Utility.h"
#include "check.h"
#include <stdio.h>

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

START_TEST(test_multiply)
{

    printf("test_multiply \n");
    Matrix Matrix_1 = createMatrix(2,2);
    Matrix_1.matrix[0][0] = 2.0;
    Matrix_1.matrix[0][1] = 2.0;
    Matrix_1.matrix[1][0] = 2.0;
    Matrix_1.matrix[1][1] = 2.0;
    printf("Input Matrix 1: \n");
    printMatrix(&Matrix_1);
    printf("-------------------\n");
    Matrix Matrix_2 = createMatrix(2,2);
    Matrix_2.matrix[0][0] = 2.0;
    Matrix_2.matrix[0][1] = 2.0;
    Matrix_2.matrix[1][0] = 2.0;
    Matrix_2.matrix[1][1] = 2.0;
    printf("Input Matrix 2: \n");
    printMatrix(&Matrix_1);
    printf("-------------------\n");
    Matrix multiplied = multiply(&Matrix_1, &Matrix_2);
    printf("multiplied Matrix: \n");
    printMatrix(&multiplied);
    ck_assert(multiplied.matrix[0][0] == 8.0);
    ck_assert(multiplied.matrix[1][0] == 8.0);
    ck_assert(multiplied.matrix[0][1] == 8.0);
    ck_assert(multiplied.matrix[1][1] == 8.0);
    printf("\n");
}
END_TEST

START_TEST(test_det)
{
    printf("test_det \n");
    Matrix tmp = createMatrix(2,2);
    tmp.matrix[0][1] = 2.0;
    tmp.matrix[1][0] = 2.0;
    tmp.matrix[1][1] = 2.0;
    tmp.matrix[0][0] = 2.0;
    double det = determinant(tmp.matrix, tmp.columnSize);
    printf("Input Matrix: \n");
    printMatrix(&tmp);
    printf("Determinant: %f\n", det);
    ck_assert(det == 0.0);
    printf("\n");
}
END_TEST

START_TEST(test_Inverse)
{
    double diff;
    printf("test_Inverse \n");
    Matrix temp = createMatrix(2,2);
    temp.matrix[0][0] = 3.0;
    temp.matrix[0][1] = 2.0;
    temp.matrix[1][0] = 2.0;
    temp.matrix[1][1] = 3.0;
    printf("Input Matrix: \n");
    printMatrix(&temp);
    printf("-------------------\n");
    Matrix Inverse =  inverse(&temp);
    printf("Output Matrix: \n");
    printMatrix(&Inverse);
    printf("\n");
    diff = Inverse.matrix[0][0] - (0.6);
    ck_assert(diff < 0.01);
    diff = Inverse.matrix[0][1] - (-0.4);
    ck_assert(diff < 0.01);
    diff = Inverse.matrix[1][0] - (-0.4);
    ck_assert(diff < 0.01);
    diff = Inverse.matrix[1][1] - (0.6);
    ck_assert(diff < 0.01);
}
END_TEST

START_TEST(test_identity)
{
    double diff;
    printf("test_identity \n");
    Matrix result = identity(2);
    printf("Output Matrix: \n");
    printMatrix(&result);
    diff = Inverse.matrix[0][0] - (1);
    ck_assert(diff < 0.01);
    diff = Inverse.matrix[0][1] - (0);
    ck_assert(diff < 0.01);
    diff = Inverse.matrix[1][0] - (0);
    ck_assert(diff < 0.01);
    diff = Inverse.matrix[1][1] - (1);
    ck_assert(diff < 0.01);
}
END_TEST

START_TEST(test_ones)
{
    double diff;
    printf("test_identity \n");
    Matrix result = ones(2,2);
    printf("Output Matrix: \n");
    printMatrix(&result);
}
END_TEST

#endif
