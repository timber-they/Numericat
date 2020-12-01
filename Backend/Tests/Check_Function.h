#include "../Parser/Parser.h"
#include "../Parser/Function.h"
#include <float.h>
#include <stdio.h>

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
#ifdef INFINITY
    double expected02 = INFINITY;
    double expectedInfinity1 = INFINITY;
    double expectedInfinity2 = INFINITY;
#endif
#ifdef NAN
    double expectedNan1 = NAN;
    double expectedNan2 = NAN;
#endif

    double resNormal1 = Evaluate(parsed1, inNormal);
    double resNormal2 = Evaluate(parsed2, inNormal);
    double resNegative1 = Evaluate(parsed1, inNegative);
    double resNegative2 = Evaluate(parsed2, inNegative);
    double res11 = Evaluate(parsed1, in1);
    double res12 = Evaluate(parsed2, in1);
    double res01 = Evaluate(parsed1, in0);
#ifdef INFINITY
    double inInfinity = INFINITY;
    double res02 = Evaluate(parsed2, in0);
    double resInfinity1 = Evaluate(parsed1, inInfinity);
    double resInfinity2 = Evaluate(parsed2, inInfinity);
#endif
#ifdef NAN
    double inNan = NAN;
    double resNan1 = Evaluate(parsed1, inNan);
    double resNan2 = Evaluate(parsed2, inNan);
#endif

    assertFloatEq(expectedNormal1, resNormal1);
    assertFloatEq(expectedNormal2, resNormal2);
    assertFloatEq(expectedNegative1, resNegative1);
    assertFloatEq(expectedNegative2, resNegative2);
    assertFloatEq(expected11, res11);
    assertFloatEq(expected12, res12);
    assertFloatEq(expected01, res01);
#ifdef INFINITY
    assertFloatEq(expected02, res02);
    assertFloatEq(expectedInfinity1, resInfinity1);
    assertFloatEq(expectedInfinity2, resInfinity2);
#endif
#ifdef NAN
    assertFloatEq(expectedNan1, resNan1);
    assertFloatEq(expectedNan2, resNan2);
#endif
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
