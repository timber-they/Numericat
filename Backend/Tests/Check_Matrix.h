#include "../Solver/Matrix/Utility.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

// TODO: Complex tests

START_TEST(test_multiply)
{
    printf("test_multiply \n");
    Matrix input = createMatrix(2,2);
    input.matrix[0][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input.matrix[0][1] = (Complex) {.real = 1.0, .imaginary = 0};
    input.matrix[1][0] = (Complex) {.real = 5.0, .imaginary = 0};
    input.matrix[1][1] = (Complex) {.real = 2.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input);
    printf("-------------------\n");
    Matrix input_2 = createMatrix(2,2);
    input_2.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 2.0, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
    printf("-------------------\n");
    Matrix multiplied = multiply(input, input_2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);
    ck_assert((multiplied.matrix[0][0].real - (6.0)) < 0.0001 && (multiplied.matrix[0][0].real - (6.0)) > -0.0001);
    ck_assert((multiplied.matrix[1][1].real - (18.0)) < 0.0001 && (multiplied.matrix[1][1].real - (18.0)) > -0.0001);
    ck_assert((multiplied.matrix[0][1].real - (10.0)) < 0.0001 && (multiplied.matrix[0][1].real - (10.0)) > -0.0001);
    ck_assert((multiplied.matrix[1][0].real - (11.0)) < 0.0001 && (multiplied.matrix[1][0].real - (11.0)) > -0.0001);
    printf("\n");
    freeMatrix(input);
    freeMatrix(input_2);
    freeMatrix(multiplied);
}
END_TEST

START_TEST(test_multiply_3x3)
{
    double diff;
    printf("test_multiply 3x3:\n");
    Matrix matrix_3 = createMatrix(3, 3);
    matrix_3.matrix[0][0] = (Complex) {.real = 2.6, .imaginary = 0};
    matrix_3.matrix[0][1] = (Complex) {.real = 4.2, .imaginary = 0};
    matrix_3.matrix[0][2] = (Complex) {.real = 1.5, .imaginary = 0};
    matrix_3.matrix[1][0] = (Complex) {.real = 6.4, .imaginary = 0};
    matrix_3.matrix[1][1] = (Complex) {.real = 3.0, .imaginary = 0};
    matrix_3.matrix[1][2] = (Complex) {.real = 4.5, .imaginary = 0};
    matrix_3.matrix[2][0] = (Complex) {.real = 3.4, .imaginary = 0};
    matrix_3.matrix[2][1] = (Complex) {.real = 5.6, .imaginary = 0};
    matrix_3.matrix[2][2] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(matrix_3);
    printf("-------------------\n");
    Matrix matrix_4 = createMatrix(3, 3);
    matrix_4.matrix[0][0] = (Complex) {.real = 4, .imaginary = 0};
    matrix_4.matrix[0][1] = (Complex) {.real = 3, .imaginary = 0};
    matrix_4.matrix[0][2] = (Complex) {.real = 4.5, .imaginary = 0};
    matrix_4.matrix[1][0] = (Complex) {.real = 4.6, .imaginary = 0};
    matrix_4.matrix[1][1] = (Complex) {.real = 5.7, .imaginary = 0};
    matrix_4.matrix[1][2] = (Complex) {.real = 1.1, .imaginary = 0};
    matrix_4.matrix[2][0] = (Complex) {.real = 0.6, .imaginary = 0};
    matrix_4.matrix[2][1] = (Complex) {.real = 4.3, .imaginary = 0};
    matrix_4.matrix[2][2] = (Complex) {.real = 6.7, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(matrix_4);
    printf("-------------------\n");
    Matrix multiplied = multiply(matrix_3, matrix_4);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);
    diff = multiplied.matrix[0][0].real - (30.62);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[0][1].real - (38.19);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[0][2].real - (26.37);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][0].real - (42.1);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][1].real - (55.65);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][2].real - (62.25);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][0].real - (41.76);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][1].real - (59.32);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][2].real - (48.26);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    freeMatrix(matrix_3);
    freeMatrix(matrix_4);
    freeMatrix(multiplied);
}
END_TEST

START_TEST(test_identity)
{
    double diff;
    printf("test_identity \n");
    Matrix result = identity(2);
    printf("Output Matrix: \n");
    printMatrix(result);
    diff = result.matrix[0][0].real - (1);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    diff = result.matrix[0][1].real - (0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    diff = result.matrix[1][0].real - (0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    diff = result.matrix[1][1].real - (1);
    if (diff < 0) diff = -diff;
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
    diff = result.matrix[0][0].real - (1);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    diff = result.matrix[0][1].real - (1);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    diff = result.matrix[1][0].real - (1);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    diff = result.matrix[1][1].real - (1);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01);
    freeMatrix(result);
}
END_TEST

START_TEST(test_factor)
{
    printf("\n");
    printf("test_factor \n");
    Matrix input = createMatrix(2, 2);
    input.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    input.matrix[0][1] = (Complex) {.real = 2.0, .imaginary = 0};
    input.matrix[1][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input.matrix[1][1] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input);
    Complex f = {.real = 5, .imaginary = 0};
    Matrix result = factor(input, f);
    printf("result: \n");
    printMatrix(result);
    ck_assert((result.matrix[0][0].real - (5.0)) < 0.0001 && (result.matrix[0][0].real - (5.0)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (20.0)) < 0.0001 && (result.matrix[1][1].real - (20.0)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (10.0)) < 0.0001 && (result.matrix[0][1].real - (10.0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (15.0)) < 0.0001 && (result.matrix[1][0].real - (15.0)) > -0.0001);
    freeMatrix(result);
    freeMatrix(input);
}
END_TEST

START_TEST(test_sum)
{
    printf("\n");
    printf("test_sum \n");
    Matrix input_1 = createMatrix(2, 2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input_1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 0};
    input_1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 0};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input_1);
    printf("-------------------\n");
    Matrix input_2 = createMatrix(2, 2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_1);
    Matrix result = sum(input_1, input_2);
    printMatrix(result);
    ck_assert((result.matrix[0][0].real - (5.5)) < 0.0001 && (result.matrix[0][0].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) < 0.0001 && (result.matrix[1][1].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (5.5)) < 0.0001 && (result.matrix[0][1].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) < 0.0001 && (result.matrix[1][1].real - (5.5)) > -0.0001);
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
}
END_TEST

START_TEST(test_arrayToMatrix)
{
    Complex *arr = malloc(3 * sizeof(* arr));
    arr[0] = (Complex) {.real= 1.0, .imaginary = 0};
    arr[1] = (Complex) {.real= 2.0, .imaginary = 0};
    arr[2] = (Complex) {.real= 3.0, .imaginary = 0};
    Matrix result = arrayToMatrix(arr, 3);
    ck_assert((result.matrix[0][0].real - (1.0)) < 0.0001 && (result.matrix[0][0].real - (1.0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (2.0)) < 0.0001 && (result.matrix[1][0].real - (2.0)) > -0.0001);
    ck_assert((result.matrix[2][0].real - (3.0)) < 0.0001 && (result.matrix[2][0].real - (3.0)) > -0.0001);
    freeMatrix(result);
    free(arr);
}
END_TEST

START_TEST(test_MatrixToArray)
{
    Matrix result = createMatrix(3,1);
    result.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    result.matrix[1][0] = (Complex) {.real = 2.0, .imaginary = 0};
    result.matrix[2][0] = (Complex) {.real = 3.0, .imaginary = 0};
    Complex *arr = matrixToArray(result);
    ck_assert((arr[0].real - (1.0)) < 0.0001 && (arr[0].real - (1.0)) > -0.0001);
    ck_assert((arr[1].real - (2.0)) < 0.0001 && (arr[1].real - (2.0)) > -0.0001);
    ck_assert((arr[2].real - (3.0)) < 0.0001 && (arr[2].real - (3.0)) > -0.0001);
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
        input_1.matrix[i][i] = (Complex) {.real = -2, .imaginary = 0};
    }
    for(int i = 0; i < 4; i++)
    {
        input_1.matrix[i][i+1] = (Complex) {.real = -1, .imaginary = 0};
    }
    for(int i = 0; i < 4; i++)
    {
        input_1.matrix[i+1][i] = (Complex) {.real = -1, .imaginary = 0};
    }
    printf("Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(5,1);
    for(int i = 0; i < 5; i++)
    {
        input_2.matrix[i][0] = (Complex) {.real = -1, .imaginary = 0};
    }
    printf("Matrix 2: \n");
    printMatrix(input_2);
    Matrix thomasMatrix = thomasSolve(input_1, input_2);
    printf("results: \n");
    printMatrix(thomasMatrix);
    printf("results should: \n");
    ck_assert((thomasMatrix.matrix[0][0].real - (0.5)) < 0.0001 && (thomasMatrix.matrix[0][0].real - (0.5)) > -0.0001);
    ck_assert((thomasMatrix.matrix[1][0].real - (0.0)) < 0.0001 && (thomasMatrix.matrix[1][0].real - (0.0)) > -0.0001);
    ck_assert((thomasMatrix.matrix[2][0].real - (0.5)) < 0.0001 && (thomasMatrix.matrix[2][0].real - (0.5)) > -0.0001);
    ck_assert((thomasMatrix.matrix[3][0].real - (0.0)) < 0.0001 && (thomasMatrix.matrix[3][0].real - (0.0)) > -0.0001);
    ck_assert((thomasMatrix.matrix[4][0].real - (0.5)) < 0.0001 && (thomasMatrix.matrix[4][0].real - (0.5)) > -0.0001);
    freeMatrix(thomasMatrix);
    freeMatrix(input_1);
    freeMatrix(input_2);
}
END_TEST

#endif
