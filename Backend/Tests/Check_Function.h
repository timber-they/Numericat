#include "../Parser/Parser.h"
#include "../Parser/Function.h"
#include <float.h>
#include <stdio.h>
#include "check.h"

#ifndef BACKEND_CHECK_FUNCTION_H
#define BACKEND_CHECK_FUNCTION_H

static void assertFloatEq(double expected, double actual);

// Note that these tests depends on Parser to work properly
START_TEST(test_Evaluate)
{
    char *function1 = " 8861/7+x*6";
    char *function2 = "1/29+x*9-88/x";

    Function parsed1 = Parse(function1);
    Function parsed2 = Parse(function2);

    double inNormal = 42;
    double inNegative = -42;
    double in1 = 1;
    double in0 = 0;

    double expectedNormal1 = 7847.142857;
    double expectedNormal2 = 6.912151067;
    double expectedNegative1 = 7343.142857;
    double expectedNegative2 = 11.08784893;
    double expected11 = 7601.142857;
    double expected12 = -78.68965517;
    double expected01 = 7595.142857;

    double resNormal1 = Evaluate(parsed1, inNormal);
    double resNormal2 = Evaluate(parsed2, inNormal);
    double resNegative1 = Evaluate(parsed1, inNegative);
    double resNegative2 = Evaluate(parsed2, inNegative);
    double res11 = Evaluate(parsed1, in1);
    double res12 = Evaluate(parsed2, in1);
    double res01 = Evaluate(parsed1, in0);

    assertFloatEq(expectedNormal1, resNormal1);
    assertFloatEq(expectedNormal2, resNormal2);
    assertFloatEq(expectedNegative1, resNegative1);
    assertFloatEq(expectedNegative2, resNegative2);
    assertFloatEq(expected11, res11);
    assertFloatEq(expected12, res12);
    assertFloatEq(expected01, res01);

    free(parsed1);
    free(parsed2);
}
END_TEST

static void assertFloatEq(double expected, double actual)
{
    printf(">>> %lf\n<<< %lf\n", expected, actual);
    double diff = expected - actual;
    if (diff < 0)
        diff = -diff;
    ck_assert(diff < 0.00001);
}

#endif //BACKEND_CHECK_FUNCTION_H
