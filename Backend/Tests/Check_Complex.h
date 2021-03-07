#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../Solver/Types/Complex.h"
#include "TestHelper.h"

#ifndef BACKEND_COMPLEX_CHECK_H
#define BACKEND_COMPLEX_CHECK_H

START_TEST(test_sumComplex)
{
    printf("\ntest_sumComplex: \n");
    Complex a = COMPLEX(1.1,4.4);
    printComplex(a);
    printf("\n");
    Complex b = COMPLEX(4.4,1.1);
    printComplex(b);
    printf("\n");
    Complex result = sumComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq(COMPLEX(5.5,5.5), result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_subtractComplex)
{
    printf("\ntest_subtractComplex: \n");
    Complex a = COMPLEX(4.4,4.4);
    printComplex(a);
    printf("\n");
    Complex b = COMPLEX(1.1,2.2);
    printComplex(b);
    printf("\n");
    Complex result = subtractComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq(COMPLEX(3.3,2.2), result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_multiplyComplex)
{
    printf("\nComplex Multiply Test: \n");
    Complex a = COMPLEX(1.4,3.3);
    printComplex(a);
    printf("\n");
    Complex b = COMPLEX(3.1,2.2);
    printComplex(b);
    printf("\n");
    Complex result = multiplyComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq(COMPLEX(-2.02,13.31), result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_divideComplex)
{
    printf("\ntest_divideComplex: \n");
    Complex a = COMPLEX(1.4,3.3);
    printComplex(a);
    printf("\n");
    Complex b = COMPLEX(3.1,2.2);
    printComplex(b);
    printf("\n");
    Complex result = divideComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq(COMPLEX(0.80276,0.49481), result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_powerComplex)
{
    printf("\ntest_pwerComplex: \n");
    Complex a = COMPLEX(1.4,3.3);
    printComplex(a);
    printf("\n");
    Complex b = COMPLEX(3.1,2.2);
    printComplex(b);
    printf("\n");
    Complex result = powerComplex(a,b);
    printf("result: \n");
    printComplex(result);
    assertComplexEq(COMPLEX(3.94783,0.601310), result);
    printf("\n----------------------------------------\n");
}
END_TEST

START_TEST(test_absSquareComplex)
{
    printf("\ntest_absSquareComplex: \n");
    Complex a = COMPLEX(1.4,3.3);
    printComplex(a);
    printf("\n");
    double result = absSquareComplex(a);
    printf("result: %lf\n", result);
    ck_assert((result - (12.85)) < 0.0001 && (result - (12.85)) > -0.0001);
    printf("\n----------------------------------------\n");
}
END_TEST

#endif
