#include "../Solver/Matrix/Complex.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef BACKEND_COMPLEX_CHECK_H
#define BACKEND_COMPLEX_CHECK_H

START_TEST(test_sumComplex)
{
    Complex a = (Complex) {.real = 1.1, .imaginary = 4.4};
    Complex b = (Complex) {.real = 4.4, .imaginary = 1.1};
    Complex result = sumComplex(a,b);
    ck_assert((result.real - (5.5)) < 0.0001 && (result.real - (5.5)) > -0.0001);
}
END_TEST

START_TEST(test_subtractComplex)
{
    Complex a = (Complex) {.real = 4.4, .imaginary = 4.4};
    Complex b = (Complex) {.real = 1.1, .imaginary = 2.2};
    Complex result = subtractComplex(a,b);
    ck_assert((result.real - (3.3)) < 0.0001 && (result.real - (2.2)) > -0.0001);
}
END_TEST

START_TEST(test_multiplyComplex)
{
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    Complex result = multiplyComplex(a,b);
    ck_assert((result.real - (-2.92)) < 0.0001 && (result.real - (13.31)) > -0.0001);
}
END_TEST

START_TEST(test_divideComplex)
{
    Complex a = (Complex) {.real = 1.4, .imaginary = 3.3};
    Complex b = (Complex) {.real = 3.1, .imaginary = 2.2};
    Complex result = multiplyComplex(a,b);
    ck_assert((result.real - (0.80276)) < 0.0001 && (result.real - (0.49481)) > -0.0001);
}
END_TEST

START_TEST(test_absSquareComplex)
{

}
END_TEST

#endif