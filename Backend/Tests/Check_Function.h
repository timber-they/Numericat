#include <float.h>
#include <stdio.h>
#include <math.h>
#include <check.h>
#include "../Parser/Parser.h"
#include "../Parser/Function.h"
#include "TestHelper.h"

#ifndef BACKEND_CHECK_FUNCTION_H
#define BACKEND_CHECK_FUNCTION_H

// Note that these tests depends on Parser to work properly
START_TEST(test_Evaluate)
{
    char *function0 = "(1/10000)^(1/2)";
    char *function1 = " 8861/7+x*6";
    char *function2 = "1/29+x*9-88/t";
    // Gaussian wave packet
    char *function3 = "(2/(3.14159265358979323*3^2))^(1/4)*2.718281828^(0-x^2/3^2)*2.718281828^(i*x)";
    char *function4 = "(2)^x+1+1/(2*3*1/1000)^(1/2)*0";
    char *function5 = "3-2-1+1/1*0";
    char *function6 = "1/(2*3*1/1000)^(1/2)*2.718281828^(0-x^2*1000/2)";

    Function parsed0 = parseFunction(function0);
    Function parsed1 = parseFunction(function1);
    Function parsed2 = parseFunction(function2);
    Function parsed3 = parseFunction(function3);
    Function parsed4 = parseFunction(function4);
    Function parsed5 = parseFunction(function5);
    Function parsed6 = parseFunction(function6);

    Input inNormal = {.x = 42, .t = 25};
    Input inNegative = {.x = -42, .t = -25};
    Input in1 = {.x = 1, .t = 2};
    Input in0 = {.x = 0, .t = -1};

    double expected0 = 0.01;
    double expectedNormal1 = 8861.0 / 7.0 + inNormal.x * 6.0;
    double expectedNormal2 = 1.0 / 29.0 + inNormal.x * 9.0 - 88.0 / inNormal.t;
    Complex expectedNormal3 = (Complex)
        {
            .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNormal.x, 2) / pow(3, 2)))
                        * cos(inNormal.x),
            .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNormal.x, 2) / pow(3, 2)))
                         * sin(inNormal.x)
        };
    double expectedNormal4 = pow(2, inNormal.x) + 1;
    double expectedNormal5 = 3-2-1;
    double expectedNegative1 = 8861.0 / 7.0 + inNegative.x * 6;
    double expectedNegative2 = 1.0 / 29.0 + inNegative.x * 9.0 - 88.0 / inNegative.t;
    Complex expectedNegative3 = (Complex)
        {
            .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNegative.x, 2) / pow(3, 2)))
                    * cos(inNegative.x),
            .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNegative.x, 2) / pow(3, 2)))
                    * sin(inNegative.x)
        };
    double expectedNegative4 = pow(2, inNegative.x) + 1;
    double expected11 = 8861.0 / 7.0 + in1.x * 6;
    double expected12 = 1.0 / 29.0 + in1.x * 9.0 - 88.0 / in1.t;
    Complex expected13 = (Complex)
            {
                    .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in1.x, 2) / pow(3, 2)))
                            * cos(in1.x),
                    .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in1.x, 2) / pow(3, 2)))
                                 * sin(in1.x)
            };
    double expected14 = pow(2, in1.x) + 1;
    double expected01 = 8861.0 / 7.0 + in0.x * 6;
    double expected02 = 1.0/29.0+in0.x*9.0-88.0/in0.t;
    Complex expected03 = (Complex)
            {
                    .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in0.x, 2) / pow(3, 2)))
                            * cos(in0.x),
                    .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in0.x, 2) / pow(3, 2)))
                                 * sin(in0.x)
            };
    double expected04 = pow(2, in0.x) + 1;
    double expected06 = pow(1.0/(2*3*1.0/1000), (1.0/2))*pow(2.7,(0-pow(in0.x, 2)*1000.0/2));

    Complex res0 = evaluate(parsed0, in0);
    Complex resNormal1 = evaluate(parsed1, inNormal);
    Complex resNormal2 = evaluate(parsed2, inNormal);
    Complex resNormal3 = evaluate(parsed3, inNormal);
    Complex resNormal4 = evaluate(parsed4, inNormal);
    Complex resNormal5 = evaluate(parsed5, inNormal);
    Complex resNegative1 = evaluate(parsed1, inNegative);
    Complex resNegative2 = evaluate(parsed2, inNegative);
    Complex resNegative3 = evaluate(parsed3, inNegative);
    Complex resNegative4 = evaluate(parsed4, inNegative);
    Complex res11 = evaluate(parsed1, in1);
    Complex res12 = evaluate(parsed2, in1);
    Complex res13 = evaluate(parsed3, in1);
    Complex res14 = evaluate(parsed4, in1);
    Complex res01 = evaluate(parsed1, in0);
    Complex res02 = evaluate(parsed2, in0);
    Complex res03 = evaluate(parsed3, in0);
    Complex res04 = evaluate(parsed4, in0);
    Complex res06 = evaluate(parsed6, in0);

    printf("Line %d\n", __LINE__);
    assertFloatEq(expected0, res0.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNormal1, resNormal1.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNormal2, resNormal2.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNormal3.real, resNormal3.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNormal3.imaginary, resNormal3.imaginary);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNormal4, resNormal4.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNormal5, resNormal5.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNegative1, resNegative1.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNegative2, resNegative2.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNegative3.real, resNegative3.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNegative3.imaginary, resNegative3.imaginary);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expectedNegative4, resNegative4.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected11, res11.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected12, res12.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected13.real, res13.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected13.imaginary, res13.imaginary);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected14, res14.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected01, res01.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected02, res02.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected03.real, res03.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected03.imaginary, res03.imaginary);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected04, res04.real);
    printf("Line %d\n", __LINE__);
    assertFloatEq(expected06, res06.real);

    free(parsed0);
    free(parsed1);
    free(parsed2);
    free(parsed3);
    free(parsed4);
    free(parsed5);
    free(parsed6);
}
END_TEST

START_TEST(test_TimeDependence)
{
    char *empty = "";
    char *no = "(2/(3.14159265358979323*3^2))^(1/4)*2.718281828^(0-x^2/3^2)*2.718281828^(i*x)";
    char *yes = "1/29+t*9-88/x";

    Function parsedEmpty = parseFunction(empty);
    Function parsedNo = parseFunction(no);
    Function parsedYes = parseFunction(yes);

    int expectedEmpty = 0;
    int expectedNo = 0;
    int expectedYes = 1;

    int resEmpty = isTimeDependent(parsedEmpty);
    int resNo = isTimeDependent(parsedNo);
    int resYes = isTimeDependent(parsedYes);

    ck_assert(expectedEmpty == resEmpty);
    ck_assert(expectedNo == resNo);
    ck_assert(expectedYes == resYes);

    free(parsedEmpty);
    free(parsedNo);
    free(parsedYes);
}
END_TEST

#endif //BACKEND_CHECK_FUNCTION_H
