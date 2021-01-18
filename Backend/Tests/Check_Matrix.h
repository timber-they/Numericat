#include "../Solver/Matrix/Utility.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

START_TEST(test_multiply)
{
    printf("test_multiply \n");
    Matrix input = createMatrix(2,2);
    input.matrix[0][0] = 2.0;
    input.matrix[0][1] = 2.0;
    input.matrix[1][0] = 2.0;
    input.matrix[1][1] = 2.0;
    printf("Input Matrix 1: \n");
    printMatrix(input);
    printf("-------------------\n");
    Matrix input_2 = createMatrix(2,2);
    input_2.matrix[0][0] = 2.0;
    input_2.matrix[0][1] = 2.0;
    input_2.matrix[1][0] = 2.0;
    input_2.matrix[1][1] = 2.0;
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
    printf("-------------------\n");
    Matrix multiplied = multiply(input, input_2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);
    ck_assert((multiplied.matrix[0][0] - (8.0)) < 0.0001);
    ck_assert((multiplied.matrix[1][1] - (8.0)) < 0.0001);
    ck_assert((multiplied.matrix[0][1] - (8.0)) < 0.0001);
    ck_assert((multiplied.matrix[1][1] - (8.0)) < 0.0001);
    printf("\n");
    freeMatrix(input);
    freeMatrix(input_2);
    freeMatrix(multiplied);
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
    double det = determinant(matrix_6);
    printf("Input Matrix: \n");
    printMatrix(matrix_6);
    printf("Determinant: %f\n", det);
    ck_assert(det == 0.0);
    printf("\n");
    freeMatrix(matrix_6);
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
    printMatrix(temp);
    printf("-------------------\n");
    Matrix Inverse =  inverse(temp);
    printf("Output Matrix: \n");
    printMatrix(Inverse);
    printf("\n");
    diff = Inverse.matrix[0][0] - (0.6);
    ck_assert(diff < 0.0001);
    diff = Inverse.matrix[0][1] - (-0.4);
    ck_assert(diff < 0.0001);
    diff = Inverse.matrix[1][0] - (-0.4);
    ck_assert(diff < 0.0001);
    diff = Inverse.matrix[1][1] - (0.6);
    ck_assert(diff < 0.01);
    freeMatrix(temp);
    freeMatrix(Inverse);
}
END_TEST

START_TEST(test_multiply_3x3)
{
    double diff;
    printf("test_multiply 3x3:\n");
    Matrix matrix_3 = createMatrix(3, 3);
    matrix_3.matrix[0][0] = 2.6;
    matrix_3.matrix[0][1] = 4.2;
    matrix_3.matrix[0][2] = 1.5;
    matrix_3.matrix[1][0] = 6.4;
    matrix_3.matrix[1][1] = 3.0;
    matrix_3.matrix[1][2] = 4.5;
    matrix_3.matrix[2][0] = 3.4;
    matrix_3.matrix[2][1] = 5.6;
    matrix_3.matrix[2][2] = 4.0;
    printf("Input Matrix 1: \n");
    printMatrix(matrix_3);
    printf("-------------------\n");
    Matrix matrix_4 = createMatrix(3, 3);
    matrix_4.matrix[0][0] = 4;
    matrix_4.matrix[0][1] = 3;
    matrix_4.matrix[0][2] = 4.5;
    matrix_4.matrix[1][0] = 4.6;
    matrix_4.matrix[1][1] = 5.7;
    matrix_4.matrix[1][2] = 1.1;
    matrix_4.matrix[2][0] = 0.6;
    matrix_4.matrix[2][1] = 4.3;
    matrix_4.matrix[2][2] = 6.7;
    printf("Input Matrix 2: \n");
    printMatrix(matrix_4);
    printf("-------------------\n");
    Matrix multiplied = multiply(matrix_3, matrix_4);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);
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
    freeMatrix(matrix_3);
    freeMatrix(matrix_4);
    freeMatrix(multiplied);
}
END_TEST

START_TEST(test_det_3x3)
{
    printf("test_det_3x3: \n");
    double diff;
    Matrix matrix_5 = createMatrix(3, 3);
    matrix_5.matrix[0][0] = 2.6;
    matrix_5.matrix[0][1] = 4.2;
    matrix_5.matrix[0][2] = 1.5;
    matrix_5.matrix[1][0] = 6.4;
    matrix_5.matrix[1][1] = 3.0;
    matrix_5.matrix[1][2] = 4.5;
    matrix_5.matrix[2][0] = 3.4;
    matrix_5.matrix[2][1] = 5.6;
    matrix_5.matrix[2][2] = 4.0;
    double det = determinant(matrix_5);
    printf("Input Matrix: \n");
    printMatrix(matrix_5);
    printf("Determinant: %f\n", det);
    diff = det -39.12;
    ck_assert(diff < 0.0001);
    printf("\n");
    freeMatrix(matrix_5);
}
END_TEST

START_TEST(test_identity)
{
    double diff;
    printf("test_identity \n");
    Matrix result = identity(2);
    printf("Output Matrix: \n");
    printMatrix(result);
    diff = result.matrix[0][0] - (1);
    ck_assert(diff < 0.01);
    diff = result.matrix[0][1] - (0);
    ck_assert(diff < 0.01);
    diff = result.matrix[1][0] - (0);
    ck_assert(diff < 0.01);
    diff = result.matrix[1][1] - (1);
    ck_assert(diff < 0.01);
    freeMatrix(result);
}
END_TEST

START_TEST(test_ones)
{
    double diff;
    printf("test_identity \n");
    Matrix result = ones(2,2);
    printf("Output Matrix: \n");
    printMatrix(result);
    diff = result.matrix[0][0] - (1);
    ck_assert(diff < 0.01);
    diff = result.matrix[0][1] - (1);
    ck_assert(diff < 0.01);
    diff = result.matrix[1][0] - (1);
    ck_assert(diff < 0.01);
    diff = result.matrix[1][1] - (1);
    ck_assert(diff < 0.01);
    freeMatrix(result);
}
END_TEST

START_TEST(test_factor)
{
    printf("\n");
    printf("test_factor \n");
    Matrix input = createMatrix(2, 2);
    input.matrix[0][0] = 2.0;
    input.matrix[0][1] = 2.0;
    input.matrix[1][0] = 2.0;
    input.matrix[1][1] = 2.0;
    printf("Input Matrix 1: \n");
    printMatrix(input);
    double f = 5;
    Matrix result = factor(input, f);
    ck_assert((result.matrix[0][0] - (10.0)) < 0.0001);
    ck_assert((result.matrix[1][1] - (10.0)) < 0.0001);
    ck_assert((result.matrix[0][1] - (10.0)) < 0.0001);
    ck_assert((result.matrix[1][1] - (10.0)) < 0.0001);
    freeMatrix(result);
    freeMatrix(input);
}
END_TEST

START_TEST(test_sum)
{
    printf("\n");
    printf("test_sum \n");
    Matrix input_1 = createMatrix(2, 2);
    input_1.matrix[0][0] = 4.0;
    input_1.matrix[0][1] = 4.0;
    input_1.matrix[1][0] = 4.0;
    input_1.matrix[1][1] = 4.0;
    printf("Input Matrix 1: \n");
    printMatrix(input_1);
    printf("-------------------\n");
    Matrix input_2 = createMatrix(2, 2);
    input_2.matrix[0][0] = 2.0;
    input_2.matrix[0][1] = 2.0;
    input_2.matrix[1][0] = 2.0;
    input_2.matrix[1][1] = 2.0;
    printf("Input Matrix 2: \n");
    printMatrix(input_1);
    Matrix result = sum(input_1, input_2);
    printMatrix(result);
    ck_assert((result.matrix[0][0] - (6.0)) < 0.0001);
    ck_assert((result.matrix[1][1] - (6.0)) < 0.0001);
    ck_assert((result.matrix[0][1] - (6.0)) < 0.0001);
    ck_assert((result.matrix[1][1] - (6.0)) < 0.0001);
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
}
END_TEST

START_TEST(test_arrayToMatrix)
{
    double *arr = malloc(sizeof(double *) * 3);
    arr[0] = 1.0;
    arr[1] = 2.0;
    arr[2] = 3.0;
    Matrix result = arrayToMatrix(arr, 3);
    ck_assert((result.matrix[0][0] - (1.0)) < 0.0001);
    ck_assert((result.matrix[1][0] - (2.0)) < 0.0001);
    ck_assert((result.matrix[2][0] - (3.0)) < 0.0001);
    freeMatrix(result);
    free(arr);
}
END_TEST

START_TEST(test_MatrixToArray)
{
    Matrix result = createMatrix(3,1);
    result.matrix[0][0] = 1.0;
    result.matrix[1][0] = 2.0;
    result.matrix[2][0] = 3.0;
    double *arr = matrixToArray(result);
    ck_assert((arr[0] - (1.0)) < 0.0001);
    ck_assert((arr[1] - (2.0)) < 0.0001);
    ck_assert((arr[2] - (3.0)) < 0.0001);
    free(arr);
    freeMatrix(result);
}
END_TEST

START_TEST(test_thomas)
{
    printf("\n");
    printf("test_thomas \n");
    Matrix input_1 = createMatrix(5,5);
    for(int i = 0; i < 5; i++)
    {
        input_1.matrix[i][i] = -2;
    }
    for(int i = 0; i < 4; i++)
    {
        input_1.matrix[i][i+1] = -2;
    }
    for(int i = 0; i < 4; i++)
    {
        input_1.matrix[i+1][i] = -2;
    }
    Matrix input_2 = createMatrix(5,1);
    for(int i = 0; i < 5; i++)
    {
        input_1.matrix[i][0] = -1;
    }
    Matrix thomasMatrix = thomasSolve(input_1, input_2);
    printMatrix(thomasMatrix);
    printf("results should: \n");
    printf("x_1 = 5/2 \n");
    printf("x_2 = 4 \n");
    printf("x_3 = 9/2 \n");
    printf("x_4 = 4 \n");
    printf("x_5 = 5/2 \n");
    freeMatrix(thomasMatrix);
    freeMatrix(input_1);
}
END_TEST

#endif
