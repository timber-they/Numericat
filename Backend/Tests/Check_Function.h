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
        char *function0 = "10^2";
        char *function1 = " 8861/7+x*6";
        char *function2 = "1/29+x*9-88/x";
        // Gaussian wave packet
        char *function3 = "(2/(3.14159265358979323*3^2))^(1/4)*2.718281828^(0-x^2/3^2)*2.718281828^(i*x)";
        char *function4 = "(2)^x+1";

        Function parsed0 = parseFunction(function0);
        Function parsed1 = parseFunction(function1);
        Function parsed2 = parseFunction(function2);
        printf("Parsing 3...\n");
        Function parsed3 = parseFunction(function3);
        printFunction(parsed3);
        Function parsed4 = parseFunction(function4);

        Complex inNormal = {.real = 42, .imaginary = 0};
        Complex inNegative = {.real = -42, .imaginary = 0};
        Complex in1 = {.real = 1, .imaginary = 0};
        Complex in0 = {.real = 0, .imaginary = 0};

        double expected0 = 100;
        double expectedNormal1 = 8861.0 / 7.0 + inNormal.real * 6.0;
        double expectedNormal2 = 1.0 / 29.0 + inNormal.real * 9.0 - 88.0 / inNormal.real;
        Complex expectedNormal3 = (Complex)
            {
                .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNormal.real, 2) / pow(3, 2)))
                            * cos(inNormal.real),
                .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNormal.real, 2) / pow(3, 2)))
                             * sin(inNormal.real)
            };
        double expectedNormal4 = pow(2, inNormal.real) + 1;
        double expectedNegative1 = 8861.0 / 7.0 + inNegative.real * 6;
        double expectedNegative2 = 1.0 / 29.0 + inNegative.real * 9.0 - 88.0 / inNegative.real;
        Complex expectedNegative3 = (Complex)
            {
                .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNegative.real, 2) / pow(3, 2)))
                        * cos(inNegative.real),
                .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(inNegative.real, 2) / pow(3, 2)))
                        * sin(inNegative.real)
            };
        double expectedNegative4 = pow(2, inNegative.real) + 1;
        double expected11 = 8861.0 / 7.0 + in1.real * 6;
        double expected12 = 1.0 / 29.0 + in1.real * 9.0 - 88.0 / in1.real;
        Complex expected13 = (Complex)
                {
                        .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in1.real, 2) / pow(3, 2)))
                                * cos(in1.real),
                        .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in1.real, 2) / pow(3, 2)))
                                     * sin(in1.real)
                };
        double expected14 = pow(2, in1.real) + 1;
        double expected01 = 8861.0 / 7.0 + in0.real * 6;
        Complex expected03 = (Complex)
                {
                        .real = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in0.real, 2) / pow(3, 2)))
                                * cos(in0.real),
                        .imaginary = pow((2 / (3.14159265358979323 * pow(3, 2))), (1.0 / 4)) * pow(2.718281828, (-pow(in0.real, 2) / pow(3, 2)))
                                     * sin(in0.real)
                };
        double expected04 = pow(2, in0.real) + 1;

        Complex res0 = evaluate(parsed0, in0);
        Complex resNormal1 = evaluate(parsed1, inNormal);
        Complex resNormal2 = evaluate(parsed2, inNormal);
        Complex resNormal3 = evaluate(parsed3, inNormal);
        Complex resNormal4 = evaluate(parsed4, inNormal);
        Complex resNegative1 = evaluate(parsed1, inNegative);
        Complex resNegative2 = evaluate(parsed2, inNegative);
        Complex resNegative3 = evaluate(parsed3, inNegative);
        Complex resNegative4 = evaluate(parsed4, inNegative);
        Complex res11 = evaluate(parsed1, in1);
        Complex res12 = evaluate(parsed2, in1);
        Complex res13 = evaluate(parsed3, in1);
        Complex res14 = evaluate(parsed4, in1);
        Complex res01 = evaluate(parsed1, in0);
        Complex res03 = evaluate(parsed3, in0);
        Complex res04 = evaluate(parsed4, in0);

        printf("Line %d\n", __LINE__);
        assertFloatEq(expected0, res0.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNormal1, resNormal1.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNormal2, resNormal2.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNormal3.real, resNormal3.real);
        assertFloatEq(expectedNormal3.imaginary, resNormal3.imaginary);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNormal4, resNormal4.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNegative1, resNegative1.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNegative2, resNegative2.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNegative3.real, resNegative3.real);
        assertFloatEq(expectedNegative3.imaginary, resNegative3.imaginary);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expectedNegative4, resNegative4.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected11, res11.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected12, res12.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected13.real, res13.real);
        assertFloatEq(expected13.imaginary, res13.imaginary);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected14, res14.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected01, res01.real);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected03.real, res03.real);
        assertFloatEq(expected03.imaginary, res03.imaginary);
        printf("Line %d\n", __LINE__);
        assertFloatEq(expected04, res04.real);

        free(parsed1);
        free(parsed2);
        free(parsed3);
        free(parsed4);
        free(parsed0);
    }
END_TEST

static void assertFloatEq(double expected, double actual)
{
    printf(">>> %lf\n<<< %lf\n", expected, actual);
    double diff = expected - actual;
    if (diff < 0)
        diff = -diff;
    if (expected < 0)
        expected = -expected;
    ck_assert(diff < 0.001);
}

#endif //BACKEND_CHECK_FUNCTION_H
