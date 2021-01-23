#include "../Solver/Matrix/Complex.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BACKEND_COMPLEX_CHECK_H
#define BACKEND_COMPLEX_CHECK_H

START_TEST(test_sumComplex)
{
    printf("\n");
    printf("test_sumComplex: \n");
    Complex a = (Complex) {.real = 1.1, .imaginary = 4.4};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 4.4, .imaginary = 1.1};
    printComplex(b);
    printf("\n");
    Complex result = sumComplex(a,b);
    printf("result: \n");
    printComplex(result);
    ck_assert((result.real - (5.5)) < 0.0001 && (result.imaginary - (5.5)) > -0.0001);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_subtractComplex)
{
    printf("\n");
    printf("test_subtractComplex: \n");
    Complex a = (Complex) {.real = 4.4, .imaginary = 4.4};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 1.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = subtractComplex(a,b);
    printf("result: \n");
    printComplex(result);
    ck_assert((result.real - (3.3)) < 0.0001 && (result.imaginary - (2.2)) > -0.0001);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_multiplyComplex)
{
    printf("\n");
    printf("Complex Multiply Test: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = multiplyComplex(a,b);
    printf("result: \n");
    printComplex(result);
    ck_assert((result.real + 2.920000) < 0.0001 && (result.imaginary - (13.310000)) > -0.0001);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_divideComplex)
{
    printf("\n");
    printf("test_divideComplex: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    printComplex(b);
    printf("\n");
    Complex result = divideComplex(a,b);
    printf("result: \n");
    printComplex(result);
    ck_assert((result.real - (0.80276)) < 0.0001 && (result.imaginary - (0.49481)) > -0.0001);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

START_TEST(test_absSquareComplex)
{
    printf("\n");
    printf("test_absSquareComplex: \n");
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    printComplex(a);
    printf("\n");
    double result = absSquareComplex(a);
    printf("result: %lf\n", result);
    ck_assert((result - (12.85)) < 0.0001);
    printf("\n");
    printf("----------------------------------------\n");
}
END_TEST

#endif