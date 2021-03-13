#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solver/Types/Matrix.h"
#include "../Solver/Types/Complex.h"

#ifndef BACKEND_UTILITY_CHECK_H
#define BACKEND_UTILITY_CHECK_H

START_TEST(test_multiply)
{
    printf("----------------------------------------\n");
    printf("test_multiply \n");
    Matrix input1 = createMatrix(2, 2);
    input1.matrix[0][0] = COMPLEX(3.0,0);
    input1.matrix[0][1] = COMPLEX(1.0,0);
    input1.matrix[1][0] = COMPLEX(5.0,0);
    input1.matrix[1][1] = COMPLEX(2.0,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(1.0,0);
    input2.matrix[0][1] = COMPLEX(2.0,0);
    input2.matrix[1][0] = COMPLEX(3.0,0);
    input2.matrix[1][1] = COMPLEX(4.0,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix multiplied = multiply(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(6.0,0);
    expected.matrix[0][1] = COMPLEX(10.0,0);
    expected.matrix[1][0] = COMPLEX(11.0,0);
    expected.matrix[1][1] = COMPLEX(18.0,0);

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
    input1.matrix[0][0] = COMPLEX(2.6,0);
    input1.matrix[0][1] = COMPLEX(4.2,0);
    input1.matrix[0][2] = COMPLEX(1.5,0);
    input1.matrix[1][0] = COMPLEX(6.4,0);
    input1.matrix[1][1] = COMPLEX(3.0,0);
    input1.matrix[1][2] = COMPLEX(4.5,0);
    input1.matrix[2][0] = COMPLEX(3.4,0);
    input1.matrix[2][1] = COMPLEX(5.6,0);
    input1.matrix[2][2] = COMPLEX(4.0,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(3, 3);
    input2.matrix[0][0] = COMPLEX(4,0);
    input2.matrix[0][1] = COMPLEX(3,0);
    input2.matrix[0][2] = COMPLEX(4.5,0);
    input2.matrix[1][0] = COMPLEX(4.6,0);
    input2.matrix[1][1] = COMPLEX(5.7,0);
    input2.matrix[1][2] = COMPLEX(1.1,0);
    input2.matrix[2][0] = COMPLEX(0.6,0);
    input2.matrix[2][1] = COMPLEX(4.3,0);
    input2.matrix[2][2] = COMPLEX(6.7,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix multiplied = multiply(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(multiplied);

    Matrix expected = createMatrix(3, 3);
    expected.matrix[0][0] = COMPLEX(30.62,0);
    expected.matrix[0][1] = COMPLEX(38.19,0);
    expected.matrix[0][2] = COMPLEX(26.37,0);
    expected.matrix[1][0] = COMPLEX(42.1,0);
    expected.matrix[1][1] = COMPLEX(55.65,0);
    expected.matrix[1][2] = COMPLEX(62.25,0);
    expected.matrix[2][0] = COMPLEX(41.76,0);
    expected.matrix[2][1] = COMPLEX(59.32,0);
    expected.matrix[2][2] = COMPLEX(48.26,0);

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
    input1.matrix[0][0] = COMPLEX(2.6,0);
    input1.matrix[0][1] = COMPLEX(0,0);
    input1.matrix[0][2] = COMPLEX(0,0);
    input1.matrix[1][0] = COMPLEX(0,0);
    input1.matrix[1][1] = COMPLEX(3.0,0);
    input1.matrix[1][2] = COMPLEX(0,0);
    input1.matrix[2][0] = COMPLEX(0,0);
    input1.matrix[2][1] = COMPLEX(0,0);
    input1.matrix[2][2] = COMPLEX(4.0,0);
    /*
     * 2.6  0   0
     *  0  3.0  0
     *  0   0  4.0
     */
    printf("Input Matrix 1: \n");
    printMatrix(input1);
    Matrix input2 = createMatrix(3, 3);
    input2.matrix[0][0] = COMPLEX(4,0);
    input2.matrix[0][1] = COMPLEX(3,0);
    input2.matrix[0][2] = COMPLEX(4.5,0);
    input2.matrix[1][0] = COMPLEX(4.6,0);
    input2.matrix[1][1] = COMPLEX(5.7,0);
    input2.matrix[1][2] = COMPLEX(1.1,0);
    input2.matrix[2][0] = COMPLEX(0.6,0);
    input2.matrix[2][1] = COMPLEX(4.3,0);
    input2.matrix[2][2] = COMPLEX(6.7,0);
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
    expected.matrix[0][0] = COMPLEX(4*2.6,0);
    expected.matrix[0][1] = COMPLEX(3*2.6,0);
    expected.matrix[0][2] = COMPLEX(4.5*2.6,0);
    expected.matrix[1][0] = COMPLEX(4.6*3.0,0);
    expected.matrix[1][1] = COMPLEX(5.7*3.0,0);
    expected.matrix[1][2] = COMPLEX(1.1*3.0,0);
    expected.matrix[2][0] = COMPLEX(0.6*4.0,0);
    expected.matrix[2][1] = COMPLEX(4.3*4.0,0);
    expected.matrix[2][2] = COMPLEX(6.7*4.0,0);

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
    expected.matrix[0][0] = COMPLEX(1,0);
    expected.matrix[0][1] = COMPLEX(0,0);
    expected.matrix[1][0] = COMPLEX(0,0);
    expected.matrix[1][1] = COMPLEX(1,0);

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
    expected.matrix[0][0] = COMPLEX(1,0);
    expected.matrix[0][1] = COMPLEX(1,0);
    expected.matrix[1][0] = COMPLEX(1,0);
    expected.matrix[1][1] = COMPLEX(1,0);

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
    input.matrix[0][0] = COMPLEX(1.0,0);
    input.matrix[0][1] = COMPLEX(2.0,0);
    input.matrix[1][0] = COMPLEX(3.0,0);
    input.matrix[1][1] = COMPLEX(4.0,0);
    printf("Input Matrix: \n");
    printMatrix(input);

    Complex f = COMPLEX(5,0);
    Matrix result = factor(input, f);
    printf("result: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(5.0,0);
    expected.matrix[0][1] = COMPLEX(10.0,0);
    expected.matrix[1][0] = COMPLEX(15.0,0);
    expected.matrix[1][1] = COMPLEX(20.0,0);

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
    input.matrix[0][0] = COMPLEX(1.0,0);
    input.matrix[0][1] = COMPLEX(0,0);
    input.matrix[1][0] = COMPLEX(0,0);
    input.matrix[1][1] = COMPLEX(4.0,0);
    printf("Input Matrix 1: \n");
    printMatrix(input);
    Complex f = COMPLEX(5,0);
    Matrix result = factorIpTri(input, f);
    printf("result: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(5.0,0);
    expected.matrix[0][1] = COMPLEX(0.0,0);
    expected.matrix[1][0] = COMPLEX(0.0,0);
    expected.matrix[1][1] = COMPLEX(20.0,0);

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
    input1.matrix[0][0] = COMPLEX(1.1,0);
    input1.matrix[0][1] = COMPLEX(2.2,0);
    input1.matrix[1][0] = COMPLEX(3.3,0);
    input1.matrix[1][1] = COMPLEX(4.4,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,0);
    input2.matrix[0][1] = COMPLEX(3.3,0);
    input2.matrix[1][0] = COMPLEX(2.2,0);
    input2.matrix[1][1] = COMPLEX(1.1,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    printf("result:\n");
    Matrix result = sum(input1, input2);
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(5.5,0);
    expected.matrix[0][1] = COMPLEX(5.5,0);
    expected.matrix[1][0] = COMPLEX(5.5,0);
    expected.matrix[1][1] = COMPLEX(5.5,0);

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
    input1.matrix[0][0] = COMPLEX(1.1,0);
    input1.matrix[0][1] = COMPLEX(0,0);
    input1.matrix[1][0] = COMPLEX(0,0);
    input1.matrix[1][1] = COMPLEX(4.4,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,0);
    input2.matrix[0][1] = COMPLEX(0,0);
    input2.matrix[1][0] = COMPLEX(0,0);
    input2.matrix[1][1] = COMPLEX(1.1,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    printf("result:\n");
    Matrix result = sumIpTri(input1, input2);
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(5.5,0);
    expected.matrix[0][1] = COMPLEX(0,0);
    expected.matrix[1][0] = COMPLEX(0,0);
    expected.matrix[1][1] = COMPLEX(5.5,0);

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
    input1.matrix[0][0] = COMPLEX(1.1,0);
    input1.matrix[0][1] = COMPLEX(0,0);
    input1.matrix[1][0] = COMPLEX(0,0);
    input1.matrix[1][1] = COMPLEX(4.4,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,0);
    input2.matrix[0][1] = COMPLEX(0,0);
    input2.matrix[1][0] = COMPLEX(0,0);
    input2.matrix[1][1] = COMPLEX(1.1,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    printf("result:\n");
    Matrix result = sumTri(input1, input2);
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(5.5,0);
    expected.matrix[0][1] = COMPLEX(0,0);
    expected.matrix[1][0] = COMPLEX(0,0);
    expected.matrix[1][1] = COMPLEX(5.5,0);

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
    input1.matrix[0][0] = COMPLEX(1.1,0);
    input1.matrix[0][1] = COMPLEX(2.2,0);
    input1.matrix[1][0] = COMPLEX(3.3,0);
    input1.matrix[1][1] = COMPLEX(4.4,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,0);
    input2.matrix[0][1] = COMPLEX(3.3,0);
    input2.matrix[1][0] = COMPLEX(2.2,0);
    input2.matrix[1][1] = COMPLEX(1.1,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix result = subtract(input1, input2);
    printf("result:\n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(-3.3,0);
    expected.matrix[0][1] = COMPLEX(-1.1,0);
    expected.matrix[1][0] = COMPLEX(1.1,0);
    expected.matrix[1][1] = COMPLEX(3.3,0);

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
    input1.matrix[0][0] = COMPLEX(1.1,0);
    input1.matrix[0][1] = COMPLEX(0,0);
    input1.matrix[1][0] = COMPLEX(0,0);
    input1.matrix[1][1] = COMPLEX(4.4,0);
    printf("Input Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,0);
    input2.matrix[0][1] = COMPLEX(0,0);
    input2.matrix[1][0] = COMPLEX(0,0);
    input2.matrix[1][1] = COMPLEX(1.1,0);
    printf("Input Matrix 2: \n");
    printMatrix(input2);

    Matrix result = subtractTri(input1, input2);
    printf("result:\n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(-3.3,0);
    expected.matrix[0][1] = COMPLEX(0,0);
    expected.matrix[1][0] = COMPLEX(0,0);
    expected.matrix[1][1] = COMPLEX(3.3,0);

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
    input[0] = COMPLEX(1,0);
    input[1] = COMPLEX(2,0);
    input[2] = COMPLEX(3,0);
    Matrix result = arrayToMatrix(input, 3);

    Matrix expected = createMatrix(3, 1);
    expected.matrix[0][0] = COMPLEX(1,0);
    expected.matrix[1][0] = COMPLEX(2,0);
    expected.matrix[2][0] = COMPLEX(3,0);

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
    input.matrix[0][0] = COMPLEX(1.0,0);
    input.matrix[1][0] = COMPLEX(2.0,0);
    input.matrix[2][0] = COMPLEX(3.0,0);
    Complex *result = matrixToArray(input);

    assertComplexEq(COMPLEX(1.0,0), result[0]);
    assertComplexEq(COMPLEX(2.0,0), result[1]);
    assertComplexEq(COMPLEX(3.0,0), result[2]);

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
        input1.matrix[i][i] = COMPLEX(-2,0);
    }
    for(int i = 0; i < 4; i++)
    {
        input1.matrix[i][i + 1] = COMPLEX(-1,0);
    }
    for(int i = 0; i < 4; i++)
    {
        input1.matrix[i + 1][i] = COMPLEX(-1,0);
    }
    printf("Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(5, 1);
    for(int i = 0; i < 5; i++)
    {
        input2.matrix[i][0] = COMPLEX(-1,0);
    }
    printf("Matrix 2: \n");
    printMatrix(input2);

    Matrix result = thomasSolve(input1, input2);
    printf("results: \n");
    printMatrix(result);

    Matrix expected = createMatrix(5, 1);
    expected.matrix[0][0] = COMPLEX(0.5,0);
    expected.matrix[1][0] = COMPLEX(0,0);
    expected.matrix[2][0] = COMPLEX(0.5,0);
    expected.matrix[3][0] = COMPLEX(0,0);
    expected.matrix[4][0] = COMPLEX(0.5,0);

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
    input1.matrix[0][0] = COMPLEX(1.1,4.4);
    input1.matrix[0][1] = COMPLEX(2.2,3.3);
    input1.matrix[1][0] = COMPLEX(3.3,2.2);
    input1.matrix[1][1] = COMPLEX(4.4,1.1);
    printf("Complexe Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,1.1);
    input2.matrix[0][1] = COMPLEX(3.3,2.2);
    input2.matrix[1][0] = COMPLEX(2.2,3.3);
    input2.matrix[1][1] = COMPLEX(1.1,4.4);
    printf("Complexe Matrix 2: \n");
    printMatrix(input2);

    Matrix result = sum(input1, input2);
    printf("result: \n");
    printMatrix(result);
    printf("%f, %f", result.matrix[0][0].real, result.matrix[0][0].imaginary);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(5.5,5.5);
    expected.matrix[0][1] = COMPLEX(5.5,5.5);
    expected.matrix[1][0] = COMPLEX(5.5,5.5);
    expected.matrix[1][1] = COMPLEX(5.5,5.5);

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
    input1.matrix[0][0] = COMPLEX(1.1,4.4);
    input1.matrix[0][1] = COMPLEX(2.2,3.3);
    input1.matrix[1][0] = COMPLEX(3.3,2.2);
    input1.matrix[1][1] = COMPLEX(4.4,1.1);
    printf("Complexe Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,1.1);
    input2.matrix[0][1] = COMPLEX(3.3,2.2);
    input2.matrix[1][0] = COMPLEX(2.2,3.3);
    input2.matrix[1][1] = COMPLEX(1.1,4.4);
    printf("Complexe Matrix 2: \n");
    printMatrix(input2);

    Matrix result = multiply(input1, input2);
    printf("multiplied Matrix: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(-6.05,35.09);
    expected.matrix[0][1] = COMPLEX(-18.15,30.25);
    expected.matrix[1][0] = COMPLEX(18.15,30.25);
    expected.matrix[1][1] = COMPLEX(6.05,35.09);

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
    input1.matrix[0][0] = COMPLEX(1.1,4.4);
    input1.matrix[0][1] = COMPLEX(2.2,3.3);
    input1.matrix[1][0] = COMPLEX(3.3,2.2);
    input1.matrix[1][1] = COMPLEX(4.4,1.1);
    printf("Complexe Matrix 1: \n");
    printMatrix(input1);

    Matrix input2 = createMatrix(2, 2);
    input2.matrix[0][0] = COMPLEX(4.4,1.1);
    input2.matrix[0][1] = COMPLEX(3.3,2.2);
    input2.matrix[1][0] = COMPLEX(2.2,3.3);
    input2.matrix[1][1] = COMPLEX(1.1,4.4);
    printf("Complexe Matrix 2: \n");
    printMatrix(input2);

    Matrix result = subtract(input1, input2);
    printf("result Matrix: \n");
    printMatrix(result);

    Matrix expected = createMatrix(2, 2);
    expected.matrix[0][0] = COMPLEX(-3.3,3.3);
    expected.matrix[0][1] = COMPLEX(-1.1,1.1);
    expected.matrix[1][0] = COMPLEX(1.1,-1.1);
    expected.matrix[1][1] = COMPLEX(3.3,-3.3);

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
    input.matrix[0][0] = COMPLEX(1.1,4.4);
    input.matrix[0][1] = COMPLEX(2.2,3.3);
    input.matrix[1][0] = COMPLEX(3.3,2.2);
    input.matrix[1][1] = COMPLEX(4.4,1.1);
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
    expected.matrix[0][0] = COMPLEX(-18.15,30.25);
    expected.matrix[0][1] = COMPLEX(-6.05,30.25);
    expected.matrix[1][0] = COMPLEX(6.05,30.25);
    expected.matrix[1][1] = COMPLEX(18.15,30.25);

    assertMatrixEq(expected, result);
    freeMatrix(result);
    freeMatrix(input);
    freeMatrix(expected);
    printf("----------------------------------------\n");
}
END_TEST

#endif
