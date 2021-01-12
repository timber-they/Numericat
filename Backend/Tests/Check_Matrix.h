#include "../Solver/Matrix/Utility.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

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
    ck_assert((multiplied.matrix[0][0] - (8.0)) < 0.0001);
    ck_assert((multiplied.matrix[1][1] - (8.0)) < 0.0001);
    ck_assert((multiplied.matrix[0][1] - (8.0)) < 0.0001);
    ck_assert((multiplied.matrix[1][1] - (8.0)) < 0.0001);
    printf("\n");
    freeMatrix(&Matrix_1);
    freeMatrix(&Matrix_2);
    freeMatrix(&multiplied);
}
END_TEST

START_TEST(test_det)
{
    printf("test_det \n");
    Matrix matrix_6 = createMatrix(2,2);
    matrix_6.matrix[0][1] = 2.0;
    matrix_6.matrix[1][0] = 2.0;
    matrix_6.matrix[1][1] = 2.0;
    matrix_6.matrix[0][0] = 2.0;
    double det = determinant(&matrix_6);
    printf("Input Matrix: \n");
    printMatrix(&matrix_6);
    printf("Determinant: %f\n", det);
    ck_assert(det == 0.0);
    printf("\n");
    freeMatrix(&matrix_6);
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
    ck_assert(diff < 0.0001);
    diff = Inverse.matrix[0][1] - (-0.4);
    ck_assert(diff < 0.0001);
    diff = Inverse.matrix[1][0] - (-0.4);
    ck_assert(diff < 0.0001);
    diff = Inverse.matrix[1][1] - (0.6);
    ck_assert(diff < 0.01);
    freeMatrix(&temp);
    freeMatrix(&Inverse);
}
END_TEST

START_TEST(test_multiply_3x3)
{
    double diff;
    printf("test_multiply 3x3:\n");
    Matrix Matrix_3 = createMatrix(3,3);
    Matrix_3.matrix[0][0] = 2.6;
    Matrix_3.matrix[0][1] = 4.2;
    Matrix_3.matrix[0][2] = 1.5;
    Matrix_3.matrix[1][0] = 6.4;
    Matrix_3.matrix[1][1] = 3.0;
    Matrix_3.matrix[1][2] = 4.5;
    Matrix_3.matrix[2][0] = 3.4;
    Matrix_3.matrix[2][1] = 5.6;
    Matrix_3.matrix[2][2] = 4.0;
    printf("Input Matrix 1: \n");
    printMatrix(&Matrix_3);
    printf("-------------------\n");
    Matrix Matrix_4 = createMatrix(3,3);
    Matrix_4.matrix[0][0] = 4;
    Matrix_4.matrix[0][1] = 3;
    Matrix_4.matrix[0][2] = 4.5;
    Matrix_4.matrix[1][0] = 4.6;
    Matrix_4.matrix[1][1] = 5.7;
    Matrix_4.matrix[1][2] = 1.1;
    Matrix_4.matrix[2][0] = 0.6;
    Matrix_4.matrix[2][1] = 4.3;
    Matrix_4.matrix[2][2] = 6.7;
    printf("Input Matrix 2: \n");
    printMatrix(&Matrix_4);
    printf("-------------------\n");
    Matrix multiplied = multiply(&Matrix_3, &Matrix_4);
    printf("multiplied Matrix: \n");
    printMatrix(&multiplied);
    diff = multiplied.matrix[0][0] - (30.62);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[0][1] - (38.19);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[0][2] - (26.37);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][0] - (42.1);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][1] - (55.65);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][2] - (62.25);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][0] - (41.76),
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][1] - (59.32);
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][2] - (48.26);
    ck_assert(diff < 0.0001);
    freeMatrix(&Matrix_3);
    freeMatrix(&Matrix_4);
    freeMatrix(&multiplied);
}
END_TEST

START_TEST(test_det_3x3)
{
    printf("test_det_3x3: \n");
    double diff;
    Matrix Matrix_5 = createMatrix(3,3);
    Matrix_5.matrix[0][0] = 2.6;
    Matrix_5.matrix[0][1] = 4.2;
    Matrix_5.matrix[0][2] = 1.5;
    Matrix_5.matrix[1][0] = 6.4;
    Matrix_5.matrix[1][1] = 3.0;
    Matrix_5.matrix[1][2] = 4.5;
    Matrix_5.matrix[2][0] = 3.4;
    Matrix_5.matrix[2][1] = 5.6;
    Matrix_5.matrix[2][2] = 4.0;
    double det = determinant(&Matrix_5);
    printf("Input Matrix: \n");
    printMatrix(&Matrix_5);
    printf("Determinant: %f\n", det);
    diff = det -39.12;
    ck_assert(diff < 0.0001);
    printf("\n");
    freeMatrix(&Matrix_5);
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
