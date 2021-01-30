#include "../Parser/Parser.h"
#include "../Parser/Function.h"
#include <float.h>
#include <stdio.h>
#include <math.h>
#include "check.h"

#ifndef BACKEND_CHECK_FUNCTION_H
#define BACKEND_CHECK_FUNCTION_H

static void assertFloatEq(double expected, double actual);

// Note that these tests depends on Parser to work properly
START_TEST(test_Evaluate)
{
    char *function1 = " 8861/7+x*6";
    char *function2 = "1/29+x*9-88/t";
    // Gaussian wave packet, ignoring the phase
    char *function3 = "(2/(3.14159265358979323*3^2))^(1/4)*2.718281828^(0-x^2/3^2)";
    char *function4 = "(2)^x+1";

    Function parsed1 = parseFunction(function1);
    Function parsed2 = parseFunction(function2);
    Function parsed3 = parseFunction(function3);
    Function parsed4 = parseFunction(function4);

    Input inNormal = {.x = 42, .t = 25};
    Input inNegative = {.x = -42, .t = -25};
    Input in1 = {.x = 1, .t = 2};
    Input in0 = {.x = 0, .t = -1};

    double expectedNormal1 = 8861.0/7.0+inNormal.x*6.0;
    double expectedNormal2 = 1.0/29.0+inNormal.x*9.0-88.0/inNormal.t;
    double expectedNormal3 = pow((2/(3.14159265358979323*pow(3,2))),(1.0/4))*pow(2.718281828,(-pow(inNormal.x,2)/pow(3,2)));
    double expectedNormal4 = pow(2,inNormal.x)+1;
    double expectedNegative1 = 8861.0/7.0+inNegative.x*6;
    double expectedNegative2 = 1.0/29.0+inNegative.x*9.0-88.0/inNegative.t;
    double expectedNegative3 = pow((2/(3.14159265358979323*pow(3,2))),(1.0/4))*pow(2.718281828,(-pow(inNegative.x,2)/pow(3,2)));
    double expectedNegative4 = pow(2,inNegative.x)+1;
    double expected11 = 8861.0/7.0+in1.x*6;
    double expected12 = 1.0/29.0+in1.x*9.0-88.0/in1.t;
    double expected13 = pow((2/(3.14159265358979323*pow(3,2))),(1.0/4))*pow(2.718281828,(-pow(in1.x,2)/pow(3,2)));
    double expected14 = pow(2,in1.x)+1;
    double expected01 = 8861.0/7.0+in0.x*6;
    double expected02 = 1.0/29.0+in0.x*9.0-88.0/in0.t;
    double expected03 = pow((2/(3.14159265358979323*pow(3,2))),(1.0/4))*pow(2.718281828,(-pow(in0.x,2)/pow(3,2)));
    double expected04 = pow(2,in0.x)+1;

    double resNormal1 = evaluate(parsed1, inNormal);
    double resNormal2 = evaluate(parsed2, inNormal);
    double resNormal3 = evaluate(parsed3, inNormal);
    double resNormal4 = evaluate(parsed4, inNormal);
    double resNegative1 = evaluate(parsed1, inNegative);
    double resNegative2 = evaluate(parsed2, inNegative);
    double resNegative3 = evaluate(parsed3, inNegative);
    double resNegative4 = evaluate(parsed4, inNegative);
    double res11 = evaluate(parsed1, in1);
    double res12 = evaluate(parsed2, in1);
    double res13 = evaluate(parsed3, in1);
    double res14 = evaluate(parsed4, in1);
    double res01 = evaluate(parsed1, in0);
    double res02 = evaluate(parsed2, in0);
    double res03 = evaluate(parsed3, in0);
    double res04 = evaluate(parsed4, in0);

    assertFloatEq(expectedNormal1, resNormal1);
    assertFloatEq(expectedNormal2, resNormal2);
    assertFloatEq(expectedNormal3, resNormal3);
    assertFloatEq(expectedNormal4, resNormal4);
    assertFloatEq(expectedNegative1, resNegative1);
    assertFloatEq(expectedNegative2, resNegative2);
    assertFloatEq(expectedNegative3, resNegative3);
    assertFloatEq(expectedNegative4, resNegative4);
    assertFloatEq(expected11, res11);
    assertFloatEq(expected12, res12);
    assertFloatEq(expected13, res13);
    assertFloatEq(expected14, res14);
    assertFloatEq(expected01, res01);
    assertFloatEq(expected02, res02);
    assertFloatEq(expected03, res03);
    assertFloatEq(expected04, res04);

    free(parsed1);
    free(parsed2);
    free(parsed3);
    free(parsed4);
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
