#include <stdio.h>
#include <stdlib.h>
#include "../Solver/Types/Complex.h"
#include "check.h"
#include "TestHelper.h"

#ifndef BACKEND_COMPLEX_CHECK_H
#define BACKEND_COMPLEX_CHECK_H

START_TEST(test_sumComplex)
{
    printf("\ntest_sumComplex: \n");
    Complex a = (Complex) {.real = 1.1, .imaginary = 4.4};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 4.4, .imaginary = 1.1};
    printComplex(b);
    printf("\n");
    Complex result = sumComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq((Complex) {.real = 5.5, .imaginary = 5.5}, result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_subtractComplex)
{
    printf("\ntest_subtractComplex: \n");
    Complex a = (Complex) {.real = 4.4, .imaginary = 4.4};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 1.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = subtractComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq((Complex) {.real = 3.3, .imaginary = 2.2}, result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_multiplyComplex)
{
    printf("\nComplex Multiply Test: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = multiplyComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq((Complex) {.real = -2.920000, .imaginary = 13.310000}, result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_divideComplex)
{
    printf("\ntest_divideComplex: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = divideComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq((Complex) {.real = 0.80276, .imaginary = 0.49481}, result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_powerComplex)
{
    printf("\ntest_pwerComplex: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = powerComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq((Complex) {.real = 3.94783, .imaginary = 0.601310}, result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_absSquareComplex)
{
    printf("\ntest_absSquareComplex: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    double result = absSquareComplex(a);
    printf("result: %lf\n", result);
    ck_assert((result - (12.85)) < 0.0001 && (result - (12.85)) > -0.0001);
    printf("\n----------------------------------------\n");
}
END_TEST

#endif