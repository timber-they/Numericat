#include "../Solver/Types/Matrix.h"
#include "../Solver/Types/Complex.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

START_TEST(test_multiply)
{
    printf("----------------------------------------\n");
    printf("test_multiply \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 1.0, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 5.0, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 2.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 2.0, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 3.0, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix multiplied = multiply(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 6.0, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 10.0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 11.0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 18.0, .imaginary = 0};

    assertMatrixEq(expected, multiplied);
    printf("\n");
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(multiplied);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_multiply_3x3)
{
    printf("test_multiply 3x3:\n");
    Matrix input1 = createMatrix(3, 3);
    input1.matrix[0][0] = (Complex) {.real = 2.6, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 4.2, .imaginary = 0};
    input1.matrix[0][2] = (Complex) {.real = 1.5, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 6.4, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 3.0, .imaginary = 0};
    input1.matrix[1][2] = (Complex) {.real = 4.5, .imaginary = 0};
    input1.matrix[2][0] = (Complex) {.real = 3.4, .imaginary = 0};
    input1.matrix[2][1] = (Complex) {.real = 5.6, .imaginary = 0};
    input1.matrix[2][2] = (Complex) {.real = 4.0, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(3, 3);
    input2.matrix[0][0] = (Complex) {.real = 4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 3, .imaginary = 0};
    input2.matrix[0][2] = (Complex) {.real = 4.5, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 4.6, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 5.7, .imaginary = 0};
    input2.matrix[1][2] = (Complex) {.real = 1.1, .imaginary = 0};
    input2.matrix[2][0] = (Complex) {.real = 0.6, .imaginary = 0};
    input2.matrix[2][1] = (Complex) {.real = 4.3, .imaginary = 0};
    input2.matrix[2][2] = (Complex) {.real = 6.7, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix multiplied = multiply(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);

    Matrix expected = createMatrix(3, 3);
    expected.matrix[0][0] = (Complex) {.real = 30.62, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 38.19, .imaginary = 0};
    expected.matrix[0][2] = (Complex) {.real = 26.37, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 42.1, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 55.65, .imaginary = 0};
    expected.matrix[1][2] = (Complex) {.real = 62.25, .imaginary = 0};
    expected.matrix[2][0] = (Complex) {.real = 41.76, .imaginary = 0};
    expected.matrix[2][1] = (Complex) {.real = 59.32, .imaginary = 0};
    expected.matrix[2][2] = (Complex) {.real = 48.26, .imaginary = 0};

    assertMatrixEq(expected, multiplied);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(multiplied);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_multiply_tri)
{
    printf("test_multiply tri:\n");
    Matrix input1 = createMatrix(3, 3);
    input1.matrix[0][0] = (Complex) {.real = 2.6, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[0][2] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 3.0, .imaginary = 0};
    input1.matrix[1][2] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[2][0] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[2][1] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[2][2] = (Complex) {.real = 4.0, .imaginary = 0};
    /*
     * 2.6  0   0
     *  0  3.0  0
     *  0   0  4.0
     */
    printf("Input Matrix 1: \n");
    printMatrix(input1);
    Matrix input2 = createMatrix(3, 3);
    input2.matrix[0][0] = (Complex) {.real = 4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 3, .imaginary = 0};
    input2.matrix[0][2] = (Complex) {.real = 4.5, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 4.6, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 5.7, .imaginary = 0};
    input2.matrix[1][2] = (Complex) {.real = 1.1, .imaginary = 0};
    input2.matrix[2][0] = (Complex) {.real = 0.6, .imaginary = 0};
    input2.matrix[2][1] = (Complex) {.real = 4.3, .imaginary = 0};
    input2.matrix[2][2] = (Complex) {.real = 6.7, .imaginary = 0};
    /*
     *  4    3  4.5
     *  4.6 5.7 1.1
     *  0.6 4.3 6.7
     */
    printf("Input Matrix 2: \n");
    printMatrix(input2);
    Matrix multiplied = multiplyTri(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);

    Matrix expected = createMatrix(3, 3);
    expected.matrix[0][0] = (Complex) {.real = 4*2.6, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 3*2.6, .imaginary = 0};
    expected.matrix[0][2] = (Complex) {.real = 4.5*2.6, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 4.6*3.0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 5.7*3.0, .imaginary = 0};
    expected.matrix[1][2] = (Complex) {.real = 1.1*3.0, .imaginary = 0};
    expected.matrix[2][0] = (Complex) {.real = 0.6*4.0, .imaginary = 0};
    expected.matrix[2][1] = (Complex) {.real = 4.3*4.0, .imaginary = 0};
    expected.matrix[2][2] = (Complex) {.real = 6.7*4.0, .imaginary = 0};

    assertMatrixEq(expected, multiplied);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(multiplied);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_identity)
{
    printf("\n");
    printf("test_identity \n");
    Matrix result = identity(2);
    printf("Output Matrix: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 1, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 1, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_ones)
{
    printf("\n");
    printf("test_ones \n");
    Matrix result = ones(2,2);
    printf("Output Matrix: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 1, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 1, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 1, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 1, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(expected);
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
    printf("Input Matrix: \n");
    printMatrix(input);

    Complex f = {.real = 5, .imaginary = 0};
    Matrix result = factor(input, f);
    printf("result: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 5.0, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 10.0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 15.0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 20.0, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(input);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_factorIpTri)
{
    printf("\n");
    printf("test_factor IpTri \n");
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

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 5.0, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 0.0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 0.0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 20.0, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_sum)
{
    printf("\n");
    printf("test_sum \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    printf("result:\n");
    Matrix result = sum(input1, input2);
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 5.5, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 5.5, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 5.5, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 5.5, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_sumIpTri)
{
    printf("\n");
    printf("test_sum IpTri \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    printf("result:\n");
    Matrix result = sumIpTri(input1, input2);
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 5.5, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 5.5, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_sumTri)
{
    printf("\n");
    printf("test_sum Tri \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    printf("result:\n");
    Matrix result = sumTri(input1, input2);
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 5.5, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 5.5, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_Matrixsubtract)
{
    printf("\n");
    printf("test_Matrixsubtract \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix result = subtract(input1, input2);
    printf("result:\n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = -3.3, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = -1.1, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 1.1, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 3.3, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_MatrixsubtractTri)
{
    printf("\n");
    printf("test_Matrixsubtract Tri \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 0};
    input1.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 0};
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 0};
    input2.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    input2.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 0};
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix result = subtractTri(input1, input2);
    printf("result:\n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = -3.3, .imaginary = 0};
    expected.matrix[0][1] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[1][1] = (Complex) {.real = 3.3, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_arrayToMatrix)
{
    printf("\n");
    Complex *input = malloc(3 * sizeof(* input));
    input[0] = (Complex) {.real= 1.0, .imaginary = 0};
    input[1] = (Complex) {.real= 2.0, .imaginary = 0};
    input[2] = (Complex) {.real= 3.0, .imaginary = 0};
    Matrix result = arrayToMatrix(input, 3);

    Matrix expected = createMatrix(3, 1);
    expected.matrix[0][0] = (Complex) {.real = 1, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 2, .imaginary = 0};
    expected.matrix[2][0] = (Complex) {.real = 3, .imaginary = 0};

    assertMatrixEq(expected, result);
    printf("Conversion from Array to Matrix was successful\n");
    freeMatrix(result);
    freeMatrix(expected);
    free(input);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_MatrixToArray)
{
    printf("\n");
    Matrix input = createMatrix(3, 1);
    input.matrix[0][0] = (Complex) {.real = 1.0, .imaginary = 0};
    input.matrix[1][0] = (Complex) {.real = 2.0, .imaginary = 0};
    input.matrix[2][0] = (Complex) {.real = 3.0, .imaginary = 0};
    Complex *result = matrixToArray(input);

    assertComplexEq((Complex) {.real = 1.0, .imaginary = 0}, result[0]);
    assertComplexEq((Complex) {.real = 2.0, .imaginary = 0}, result[1]);
    assertComplexEq((Complex) {.real = 3.0, .imaginary = 0}, result[2]);

    printf("Conversion from Matrix to Array was successful\n");
    free(result);
    freeMatrix(input);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_thomas)
{
    printf("\n");
    printf("test_thomas \n");
    Matrix input1 = createMatrix(5, 5);
    for(int i = 0; i < 5; i++)
    {
        input1.matrix[i][i] = (Complex) {.real = -2, .imaginary = 0};
    }
    for(int i = 0; i < 4; i++)
    {
        input1.matrix[i][i + 1] = (Complex) {.real = -1, .imaginary = 0};
    }
    for(int i = 0; i < 4; i++)
    {
        input1.matrix[i + 1][i] = (Complex) {.real = -1, .imaginary = 0};
    }
    printf("Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(5, 1);
    for(int i = 0; i < 5; i++)
    {
        input2.matrix[i][0] = (Complex) {.real = -1, .imaginary = 0};
    }
    printf("Matrix 2: \n");
    printMatrix(input2);

    Matrix result = thomasSolve(input1, input2);
    printf("results: \n");
    printMatrix(result);

    Matrix expected = createMatrix(5, 1);
    expected.matrix[0][0] = (Complex) {.real = 0.5, .imaginary = 0};
    expected.matrix[1][0] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[2][0] = (Complex) {.real = 0.5, .imaginary = 0};
    expected.matrix[3][0] = (Complex) {.real = 0, .imaginary = 0};
    expected.matrix[4][0] = (Complex) {.real = 0.5, .imaginary = 0};

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_sumComplexMatrix)
{
    printf("\n");
    printf("test_sumComplex: \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Complexe Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 1.1};
    input2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 4.4};
    printf("Complexe Matrix 2: \n");
    printMatrix(input2);

    Matrix result = sum(input1, input2);
    printf("result: \n");
    printMatrix(result);
    printf("%f, %f", result.matrix[0][0].real, result.matrix[0][0].imaginary);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = 5.5, .imaginary = 5.5};
    expected.matrix[0][1] = (Complex) {.real = 5.5, .imaginary = 5.5};
    expected.matrix[1][0] = (Complex) {.real = 5.5, .imaginary = 5.5};
    expected.matrix[1][1] = (Complex) {.real = 5.5, .imaginary = 5.5};

    assertMatrixEq(expected, result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_ComplexmultiplyMatrix)
{
    printf("\n");
    printf("test_Complexmultiply \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Complexe Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 1.1};
    input2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 4.4};
    printf("Complexe Matrix 2: \n");
    printMatrix(input2);

    Matrix result = multiply(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = -6.05, .imaginary = 35.09};
    expected.matrix[0][1] = (Complex) {.real = -18.15, .imaginary = 30.25};
    expected.matrix[1][0] = (Complex) {.real = 18.15, .imaginary = 30.25};
    expected.matrix[1][1] = (Complex) {.real = 6.05, .imaginary = 35.09};

    assertMatrixEq(expected, result);
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
}
END_TEST

START_TEST(test_ComplexMatrixsubtract)
{
    printf("\n");
    printf("test_Complexsubtract \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = (Complex) {.real = 1.1, .imaginary = 4.4};
    input1.matrix[0][1] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input1.matrix[1][0] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input1.matrix[1][1] = (Complex) {.real = 4.4, .imaginary = 1.1};
    printf("Complexe Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = (Complex) {.real = 4.4, .imaginary = 1.1};
    input2.matrix[0][1] = (Complex) {.real = 3.3, .imaginary = 2.2};
    input2.matrix[1][0] = (Complex) {.real = 2.2, .imaginary = 3.3};
    input2.matrix[1][1] = (Complex) {.real = 1.1, .imaginary = 4.4};
    printf("Complexe Matrix 2: \n");
    printMatrix(input2);

    Matrix result = subtract(input1, input2);
    printf("result Matrix: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = -3.3, .imaginary = 3.3};
    expected.matrix[0][1] = (Complex) {.real = -1.1, .imaginary = 1.1};
    expected.matrix[1][0] = (Complex) {.real = 1.1, .imaginary = -1.1};
    expected.matrix[1][1] = (Complex) {.real = 3.3, .imaginary = -3.3};

    assertMatrixEq(expected, result);
    printf("----------------------------------------\n");
    freeMatrix(input1);
    freeMatrix(input2);
    freeMatrix(result);
    freeMatrix(expected);
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
    printf("Input Matrix: \n");
    printMatrix(input);

    printf("Factor is: \n");
    Complex f = {.real = 5.5, .imaginary = 5.5};
    printComplex(f);
    printf("\n");

    Matrix result = factor(input, f);
    printf("result: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = (Complex) {.real = -18.15, .imaginary = 30.25};
    expected.matrix[0][1] = (Complex) {.real = -6.05, .imaginary = 30.25};
    expected.matrix[1][0] = (Complex) {.real = 6.05, .imaginary = 30.25};
    expected.matrix[1][1] = (Complex) {.real = 18.15, .imaginary = 30.25};

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(input);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

#endif
