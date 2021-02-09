#include "../Solver/Matrix/Utility.h"
#include "../Solver/Matrix/Complex.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

START_TEST(test_multiply)
{
    printf("----------------------------------------\n");
    printf("test_multiply \n");
    Matrix input = createMatrix(2,2);
    input.matrix[0][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input.matrix[0][1] = (Complex) {.real = 1.0, .imaginary = 0};
    input.matrix[1][0] = (Complex) {.real = 5.0, .imaginary = 0};
    input.matrix[1][1] = (Complex) {.real = 2.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input);
    Matrix input_2 = createMatrix(2,2);
    input_2.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 2.0, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
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
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_multiply_3x3)
{
    double diff;
    printf("test_multiply 3x3:\n");
    Matrix matrix_1 = createMatrix(3, 3);
    matrix_1.matrix[0][0] = (Complex) {.real = 2.6, .imaginary = 0};
    matrix_1.matrix[0][1] = (Complex) {.real = 4.2, .imaginary = 0};
    matrix_1.matrix[0][2] = (Complex) {.real = 1.5, .imaginary = 0};
    matrix_1.matrix[1][0] = (Complex) {.real = 6.4, .imaginary = 0};
    matrix_1.matrix[1][1] = (Complex) {.real = 3.0, .imaginary = 0};
    matrix_1.matrix[1][2] = (Complex) {.real = 4.5, .imaginary = 0};
    matrix_1.matrix[2][0] = (Complex) {.real = 3.4, .imaginary = 0};
    matrix_1.matrix[2][1] = (Complex) {.real = 5.6, .imaginary = 0};
    matrix_1.matrix[2][2] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(matrix_1);
    Matrix matrix_2 = createMatrix(3, 3);
    matrix_2.matrix[0][0] = (Complex) {.real = 4, .imaginary = 0};
    matrix_2.matrix[0][1] = (Complex) {.real = 3, .imaginary = 0};
    matrix_2.matrix[0][2] = (Complex) {.real = 4.5, .imaginary = 0};
    matrix_2.matrix[1][0] = (Complex) {.real = 4.6, .imaginary = 0};
    matrix_2.matrix[1][1] = (Complex) {.real = 5.7, .imaginary = 0};
    matrix_2.matrix[1][2] = (Complex) {.real = 1.1, .imaginary = 0};
    matrix_2.matrix[2][0] = (Complex) {.real = 0.6, .imaginary = 0};
    matrix_2.matrix[2][1] = (Complex) {.real = 4.3, .imaginary = 0};
    matrix_2.matrix[2][2] = (Complex) {.real = 6.7, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(matrix_2);
    Matrix multiplied = multiply(matrix_1, matrix_2);
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
    freeMatrix(matrix_1);
    freeMatrix(matrix_2);
    freeMatrix(multiplied);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_multiply_tri)
{
    double diff;
    printf("test_multiply tri:\n");
    Matrix matrix_3 = createMatrix(3, 3);
    matrix_3.matrix[0][0] = (Complex) {.real = 2.6, .imaginary = 0};
    matrix_3.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    matrix_3.matrix[0][2] = (Complex) {.real = 0, .imaginary = 0};
    matrix_3.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    matrix_3.matrix[1][1] = (Complex) {.real = 3.0, .imaginary = 0};
    matrix_3.matrix[1][2] = (Complex) {.real = 0, .imaginary = 0};
    matrix_3.matrix[2][0] = (Complex) {.real = 0, .imaginary = 0};
    matrix_3.matrix[2][1] = (Complex) {.real = 0, .imaginary = 0};
    matrix_3.matrix[2][2] = (Complex) {.real = 4.0, .imaginary = 0};
    /*
     * 2.6  0   0
     *  0  3.0  0
     *  0   0  4.0
     */
    printf("Input Matrix 1: \n");
    printMatrix(matrix_3);
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
    /*
     *  4    3  4.5
     *  4.6 5.7 1.1
     *  0.6 4.3 6.7
     */
    printf("Input Matrix 2: \n");
    printMatrix(matrix_4);
    Matrix multiplied = multiplyTri(matrix_3, matrix_4);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);
    diff = multiplied.matrix[0][0].real - (4*2.6);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[0][1].real - (3*2.6);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[0][2].real - (4.5*2.6);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][0].real - (4.6*3.0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][1].real - (5.7*3.0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[1][2].real - (1.1*3.0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][0].real - (0.6*4.0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][1].real - (4.3*4.0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    diff = multiplied.matrix[2][2].real - (6.7*4.0);
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001);
    freeMatrix(matrix_3);
    freeMatrix(matrix_4);
    freeMatrix(multiplied);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_identity)
{
    printf("\n");
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
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_ones)
{
    printf("\n");
    double diff;
    printf("test_ones \n");
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
    printf("----------------------------------------\n");
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
    ck_assert((result.matrix[0][0].real - (5.0)) > -0.0001 && (result.matrix[0][0].real - (5.0)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (20.0)) < 0.0001 && (result.matrix[1][1].real - (20.0)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (20.0)) > -0.0001 && (result.matrix[1][1].real - (20.0)) < 0.0001);
    ck_assert((result.matrix[0][1].real - (10.0)) < 0.0001 && (result.matrix[0][1].real - (10.0)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (10.0)) > -0.0001 && (result.matrix[0][1].real - (10.0)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (15.0)) < 0.0001 && (result.matrix[1][0].real - (15.0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (15.0)) > -0.0001 && (result.matrix[1][0].real - (15.0)) < 0.0001);
    freeMatrix(result);
    freeMatrix(input);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_factorIpTri)
{
    printf("\n");
    printf("test_factorIpTri \n");
    Matrix input = createMatrix(2, 2);
    input.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    input.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input.matrix[1][1] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input);
    Complex f = {.real = 5, .imaginary = 0};
    Matrix result = factorIpTri(input, f);
    printf("result: \n");
    printMatrix(result);
    ck_assert((result.matrix[0][0].real - (5.0)) < 0.0001 && (result.matrix[0][0].real - (5.0)) > -0.0001);
    ck_assert((result.matrix[0][0].real - (5.0)) > -0.0001 && (result.matrix[0][0].real - (5.0)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (20.0)) < 0.0001 && (result.matrix[1][1].real - (20.0)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (20.0)) > -0.0001 && (result.matrix[1][1].real - (20.0)) < 0.0001);
    ck_assert((result.matrix[0][1].real - (0)) < 0.0001 && (result.matrix[0][1].real - (0)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (0)) > -0.0001 && (result.matrix[0][1].real - (0)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (0)) < 0.0001 && (result.matrix[1][0].real - (0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (0)) > -0.0001 && (result.matrix[1][0].real - (0)) < 0.0001);
    freeMatrix(result);
    printf("----------------------------------------\n");
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
    Matrix input_2 = createMatrix(2, 2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
    printf("result:\n");
    Matrix result = sum(input_1, input_2);
    printMatrix(result);
    ck_assert((result.matrix[0][0].real - (5.5)) < 0.0001 && (result.matrix[0][0].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[0][0].real - (5.5)) > -0.0001 && (result.matrix[0][0].real - (5.5)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) < 0.0001 && (result.matrix[1][1].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) > -0.0001 && (result.matrix[1][1].real - (5.5)) < 0.0001);
    ck_assert((result.matrix[0][1].real - (5.5)) < 0.0001 && (result.matrix[0][1].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (5.5)) > -0.0001 && (result.matrix[0][1].real - (5.5)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (5.5)) < 0.0001 && (result.matrix[1][0].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (5.5)) > -0.0001 && (result.matrix[1][0].real - (5.5)) < 0.0001);
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_sumIpTri)
{
    printf("\n");
    printf("test_sumIpTri \n");
    Matrix input_1 = createMatrix(2, 2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input_1.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input_1.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(2, 2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
    printf("result:\n");
    Matrix result = sumIpTri(input_1, input_2);
    printMatrix(result);
    ck_assert((result.matrix[0][0].real - (5.5)) < 0.0001 && (result.matrix[0][0].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[0][0].real - (5.5)) > -0.0001 && (result.matrix[0][0].real - (5.5)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) < 0.0001 && (result.matrix[1][1].real - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) > -0.0001 && (result.matrix[1][1].real - (5.5)) < 0.0001);
    ck_assert((result.matrix[0][1].real - (0)) < 0.0001 && (result.matrix[0][1].real - (0)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (0)) > -0.0001 && (result.matrix[0][1].real - (0)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (0)) < 0.0001 && (result.matrix[1][0].real - (0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (0)) > -0.0001 && (result.matrix[1][0].real - (0)) < 0.0001);
    freeMatrix(input_2);
    freeMatrix(result);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_Matrixsubtract)
{
    printf("\n");
    printf("test_Matrixsubtract \n");
    Matrix input_1 = createMatrix(2, 2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input_1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 0};
    input_1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 0};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(2, 2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
    Matrix result = subtract(input_1, input_2);
    printf("result:\n");
    printMatrix(result);
    ck_assert((result.matrix[0][0].real + (3.30)) < 0.0001 && (result.matrix[0][0].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[0][0].real + (3.30)) > -0.0001 && (result.matrix[0][0].imaginary - (0.0)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (3.30)) < 0.0001 && (result.matrix[1][1].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (3.30)) > -0.0001 && (result.matrix[1][1].imaginary - (0.0)) > -0.0001);
    ck_assert((result.matrix[0][1].real + (1.10)) < 0.0001 && (result.matrix[0][1].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[0][1].real + (1.10)) > -0.0001 && (result.matrix[0][1].imaginary - (0.0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (1.10)) < 0.0001 && (result.matrix[1][0].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (1.10)) > -0.0001 && (result.matrix[1][0].imaginary - (0.0)) > -0.0001);
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_MatrixsubtractTri)
{
    printf("\n");
    printf("test_Matrixsubtract \n");
    Matrix input_1 = createMatrix(2, 2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input_1.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input_1.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(2, 2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input_2.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input_2.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input_2);
    Matrix result = subtractTri(input_1, input_2);
    printf("result:\n");
    printMatrix(result);
    ck_assert((result.matrix[0][0].real + (3.30)) < 0.0001 && (result.matrix[0][0].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[0][0].real + (3.30)) > -0.0001 && (result.matrix[0][0].imaginary - (0.0)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (3.30)) < 0.0001 && (result.matrix[1][1].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (3.30)) > -0.0001 && (result.matrix[1][1].imaginary - (0.0)) > -0.0001);
    ck_assert((result.matrix[0][1].real + (0)) < 0.0001 && (result.matrix[0][1].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[0][1].real + (0)) > -0.0001 && (result.matrix[0][1].imaginary - (0.0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (0)) < 0.0001 && (result.matrix[1][0].imaginary - (0.0)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (0)) > -0.0001 && (result.matrix[1][0].imaginary - (0.0)) > -0.0001);
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_arrayToMatrix)
{
    printf("\n");
    Complex *arr = malloc(3 * sizeof(* arr));
    arr[0] = (Complex) {.real= 1.0, .imaginary = 0};
    arr[1] = (Complex) {.real= 2.0, .imaginary = 0};
    arr[2] = (Complex) {.real= 3.0, .imaginary = 0};
    Matrix result = arrayToMatrix(arr, 3);
    ck_assert((result.matrix[0][0].real - (1.0)) < 0.0001 && (result.matrix[0][0].real - (1.0)) > -0.0001);
    ck_assert((result.matrix[0][0].real - (1.0)) > -0.0001 && (result.matrix[0][0].real - (1.0)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (2.0)) < 0.0001 && (result.matrix[1][0].real - (2.0)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (2.0)) > -0.0001 && (result.matrix[1][0].real - (2.0)) < 0.0001);
    ck_assert((result.matrix[2][0].real - (3.0)) < 0.0001 && (result.matrix[2][0].real - (3.0)) > -0.0001);
    ck_assert((result.matrix[2][0].real - (3.0)) > -0.0001 && (result.matrix[2][0].real - (3.0)) < 0.0001);
    printf("Conversion from Array to Matrix was successful\n");
    freeMatrix(result);
    free(arr);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_MatrixToArray)
{
    printf("\n");
    Matrix result = createMatrix(3,1);
    result.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    result.matrix[1][0] = (Complex) {.real = 2.0, .imaginary = 0};
    result.matrix[2][0] = (Complex) {.real = 3.0, .imaginary = 0};
    Complex *arr = matrixToArray(result);
    ck_assert((arr[0].real - (1.0)) < 0.0001 && (arr[0].real - (1.0)) > -0.0001);
    ck_assert((arr[0].real - (1.0)) > -0.0001 && (arr[0].real - (1.0)) < 0.0001);
    ck_assert((arr[1].real - (2.0)) < 0.0001 && (arr[1].real - (2.0)) > -0.0001);
    ck_assert((arr[1].real - (2.0)) > -0.0001 && (arr[1].real - (2.0)) < 0.0001);
    ck_assert((arr[2].real - (3.0)) < 0.0001 && (arr[2].real - (3.0)) > -0.0001);
    ck_assert((arr[2].real - (3.0)) > -0.0001 && (arr[2].real - (3.0)) < 0.0001);
    printf("Conversion from Matrix to Array was successful\n");
    free(arr);
    freeMatrix(result);
    printf("----------------------------------------\n");
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
    ck_assert((thomasMatrix.matrix[0][0].real - (0.5)) < 0.0001 && (thomasMatrix.matrix[0][0].real - (0.5)) > -0.0001);
    ck_assert((thomasMatrix.matrix[0][0].real - (0.5)) > -0.0001 && (thomasMatrix.matrix[0][0].real - (0.5)) < 0.0001);
    ck_assert((thomasMatrix.matrix[1][0].real - (0.0)) < 0.0001 && (thomasMatrix.matrix[1][0].real - (0.0)) > -0.0001);
    ck_assert((thomasMatrix.matrix[1][0].real - (0.0)) > -0.0001 && (thomasMatrix.matrix[1][0].real - (0.0)) < 0.0001);
    ck_assert((thomasMatrix.matrix[2][0].real - (0.5)) < 0.0001 && (thomasMatrix.matrix[2][0].real - (0.5)) > -0.0001);
    ck_assert((thomasMatrix.matrix[2][0].real - (0.5)) > -0.0001 && (thomasMatrix.matrix[2][0].real - (0.5)) < 0.0001);
    ck_assert((thomasMatrix.matrix[3][0].real - (0.0)) < 0.0001 && (thomasMatrix.matrix[3][0].real - (0.0)) > -0.0001);
    ck_assert((thomasMatrix.matrix[3][0].real - (0.0)) > -0.0001 && (thomasMatrix.matrix[3][0].real - (0.0)) < 0.0001);
    ck_assert((thomasMatrix.matrix[4][0].real - (0.5)) < 0.0001 && (thomasMatrix.matrix[4][0].real - (0.5)) > -0.0001);
    ck_assert((thomasMatrix.matrix[4][0].real - (0.5)) > -0.0001 && (thomasMatrix.matrix[4][0].real - (0.5)) < 0.0001);
    freeMatrix(thomasMatrix);
    freeMatrix(input_1);
    freeMatrix(input_2);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_sumComplexMatrix)
{
    printf("\n");
    printf("test_sumComplex: \n");
    Matrix input_1 = createMatrix(2,2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input_1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input_1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Complexe Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(2,2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 1.1};
    input_2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input_2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 4.4};
    printf("Complexe Matrix 2: \n");
    printMatrix(input_2);
    Matrix result = sum(input_1, input_2);
    printf("result: \n");
    printMatrix(result);
    printf("%f, %f",result.matrix[0][0].real, result.matrix[0][0].imaginary);
    ck_assert((result.matrix[0][0].real - (5.5)) < 0.0001 && (result.matrix[0][0].imaginary - (5.5)) > -0.0001);
    ck_assert((result.matrix[0][0].real - (5.5)) > -0.0001 && (result.matrix[0][0].imaginary - (5.5)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) < 0.0001 && (result.matrix[1][1].imaginary - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (5.5)) > -0.0001 && (result.matrix[1][1].imaginary - (5.5)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (5.5)) < 0.0001 && (result.matrix[1][0].imaginary - (5.5)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (5.5)) > -0.0001 && (result.matrix[1][0].imaginary - (5.5)) < 0.0001);
    ck_assert((result.matrix[0][1].real - (5.5)) < 0.0001 && (result.matrix[0][1].imaginary - (5.5)) > -0.0001);
    ck_assert((result.matrix[0][1].real - (5.5)) > -0.0001 && (result.matrix[0][1].imaginary - (5.5)) < 0.0001);
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_ComplexmultiplyMatrix)
{
    printf("\n");
    printf("test_Complexmultiply \n");
    Matrix input_1 = createMatrix(2,2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input_1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input_1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Complexe Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(2,2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 1.1};
    input_2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input_2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 4.4};
    printf("Complexe Matrix 2: \n");
    printMatrix(input_2);
    Matrix multiplied = multiply(input_1, input_2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);
    ck_assert((multiplied.matrix[0][0].real + (5.05)) < 0.0001 && (multiplied.matrix[0][0].imaginary - (35.09)) > -0.0001);
    ck_assert((multiplied.matrix[0][0].real + (5.05))  - 0.0001 && (multiplied.matrix[0][0].imaginary - (35.09)) < 0.0001);
    ck_assert((multiplied.matrix[1][1].real - (6.05)) < 0.0001 && (multiplied.matrix[1][1].imaginary - (35.09)) > -0.0001);
    ck_assert((multiplied.matrix[1][1].real - (6.05)) > -0.0001 && (multiplied.matrix[1][1].imaginary - (35.09)) < 0.0001);
    ck_assert((multiplied.matrix[0][1].real + (18.15)) < 0.0001 && (multiplied.matrix[0][1].imaginary - (30.25)) > -0.0001);
    ck_assert((multiplied.matrix[0][1].real + (18.15)) > -0.0001 && (multiplied.matrix[0][1].imaginary - (30.25)) < 0.0001);
    ck_assert((multiplied.matrix[1][0].real - (18.15)) < 0.0001 && (multiplied.matrix[1][0].imaginary - (30.25)) > -0.0001);
    ck_assert((multiplied.matrix[1][0].real - (18.15)) > -0.0001 && (multiplied.matrix[1][0].imaginary - (30.25)) < 0.0001);
    printf("----------------------------------------\n");
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(multiplied);
}
END_TEST

START_TEST(test_ComplexMatrixsubtract)
{
    printf("\n");
    printf("test_Complexsubtract \n");
    Matrix input_1 = createMatrix(2,2);
    input_1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input_1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input_1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input_1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Complexe Matrix 1: \n");
    printMatrix(input_1);
    Matrix input_2 = createMatrix(2,2);
    input_2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 1.1};
    input_2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input_2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input_2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 4.4};
    printf("Complexe Matrix 2: \n");
    printMatrix(input_2);
    Matrix result = subtract(input_1, input_2);
    printf("result Matrix: \n");
    printMatrix(result);
    ck_assert((result.matrix[0][0].real + (3.30)) < 0.0001 && (result.matrix[0][0].imaginary - (3.30)) > -0.0001);
    ck_assert((result.matrix[0][0].real + (3.30)) > -0.0001 && (result.matrix[0][0].imaginary - (3.30)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (3.30)) < 0.0001 && (result.matrix[1][1].imaginary + (3.30)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (3.30)) > -0.0001 && (result.matrix[1][1].imaginary + (3.30)) > -0.0001);
    ck_assert((result.matrix[0][1].real + (1.10)) < 0.0001 && (result.matrix[0][1].imaginary - (1.10)) < 0.0001);
    ck_assert((result.matrix[0][1].real + (1.10)) > -0.0001 && (result.matrix[0][1].imaginary - (1.10)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (1.10)) < 0.0001 && (result.matrix[1][0].imaginary + (1.10)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (1.10)) > -0.0001 && (result.matrix[1][0].imaginary + (1.10)) > -0.0001);
    printf("----------------------------------------\n");
    freeMatrix(input_1);
    freeMatrix(input_2);
    freeMatrix(result);
}
END_TEST

START_TEST(test_ComplexFactor)
{
    printf("\n");
    printf("test_ComplexFactor \n");
    Matrix input = createMatrix(2, 2);
    input.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Input Matrix 1: \n");
    printMatrix(input);
    printf("Factor is: \n");
    Complex f = {.real = 5.5, .imaginary = 5.5};
    printComplex(f);
printf("\n");
    Matrix result = factor(input, f);
    printf("result: \n");
    printMatrix(result);
    ck_assert((result.matrix[0][0].real + (18.15)) < 0.0001&& (result.matrix[0][0].imaginary - (30.25)) > -0.0001);
    ck_assert((result.matrix[0][0].real + (18.15)) > -0.0001&& (result.matrix[0][0].imaginary - (30.25)) < 0.0001);
    ck_assert((result.matrix[1][1].real - (18.15)) < 0.0001 && (result.matrix[1][1].imaginary - (30.25)) > -0.0001);
    ck_assert((result.matrix[1][1].real - (18.15)) > -0.0001 && (result.matrix[1][1].imaginary - (30.25)) < 0.0001);
    ck_assert((result.matrix[0][1].real + (6.05)) < 0.0001 && (result.matrix[0][1].imaginary - (30.25)) > -0.0001);
    ck_assert((result.matrix[0][1].real + (6.05)) > -0.0001 && (result.matrix[0][1].imaginary - (30.25)) < 0.0001);
    ck_assert((result.matrix[1][0].real - (6.05)) < 0.0001 && (result.matrix[1][0].imaginary - (30.25)) > -0.0001);
    ck_assert((result.matrix[1][0].real - (6.05)) > -0.0001 && (result.matrix[1][0].imaginary - (30.25)) < 0.0001);
    freeMatrix(result);
    freeMatrix(input);
    printf("----------------------------------------\n");
}
END_TEST

#endif
