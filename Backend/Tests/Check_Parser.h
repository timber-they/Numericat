#include "../Parser/Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "check.h"

#ifndef BACKEND_CHECK_PARSER_H
#define BACKEND_CHECK_PARSER_H

static void validateEquality(char *function, Function expected, Function actual);

START_TEST(test_Parse_Functions)
{
    char *function1 = " 8861/7+x*6";
    char *function2 = "(1/29+x*9-88/x^(x-1))";

    Element expected1[] =
    {
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 8861, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 7, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = variable, .atom.value=(Complex) {.real = 0, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 6, .imaginary = 0}},
        (Element) {.atomType = end, .atom.value=(Complex) {.real = 0, .imaginary = 0}}
    };
    Element expected2[] =
    {
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 1, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 29, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = variable, .atom.value=(Complex) {.real = 0, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 9, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 88, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = variable, .atom.value=(Complex) {.real = 0, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=power},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = variable, .atom.value=(Complex) {.real = 0, .imaginary = 0}},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=(Complex) {.real = 1, .imaginary = 0}},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = end, .atom.value=(Complex) {.real = 0, .imaginary = 0}},
    };

    Function actual1 = parseFunction(function1);
    Function actual2 = parseFunction(function2);

    validateEquality(function1, expected1, actual1);
    validateEquality(function2, expected2, actual2);

    free(actual1);
    free(actual2);
}
END_TEST

START_TEST(test_Parse_Failing)
{
    char *empty = "";
    char *null = NULL;
    char *doubleOperator = "2+/2";
    char *doubleValue = "1 1";
    char *valueVariable = "1 x";
    char *variableValue = "x 1";
    char *doubleVariable = "x x";
    char *tailingOperator = "2+";
    char *missingOperator = "(2+x)(3)";

    Function emptyRes = parseFunction(empty);
    Function nullRes = parseFunction(null);
    Function doubleOperatorRes = parseFunction(doubleOperator);
    Function doubleValueRes = parseFunction(doubleValue);
    Function valueVariableRes = parseFunction(valueVariable);
    Function variableValueRes = parseFunction(variableValue);
    Function doubleVariableRes = parseFunction(doubleVariable);
    Function tailingOperatorRes = parseFunction(tailingOperator);
    Function missingOperatorRes = parseFunction(missingOperator);

    ck_assert(emptyRes == NULL);
    ck_assert(nullRes == NULL);
    ck_assert(doubleOperatorRes == NULL);
    ck_assert(doubleValueRes == NULL);
    ck_assert(valueVariableRes == NULL);
    ck_assert(variableValueRes == NULL);
    ck_assert(doubleVariableRes == NULL);
    ck_assert(tailingOperatorRes == NULL);
    ck_assert(missingOperatorRes == NULL);
}
END_TEST

START_TEST(test_Validate_Dyck)
    {
        char *empty = "";
        char *noParanthesis = "bpnaöoiwe48th34";
        char *simple = "()";
        char *complex = "(abc(Hi) - bu((t)asldfk)]])";

        int emptyRes = validateDyck(empty);
        int noParanthesisRes = validateDyck(noParanthesis);
        int simpleRes = validateDyck(simple);
        int complexRes = validateDyck(complex);

        ck_assert(emptyRes == 0);
        ck_assert(noParanthesisRes == 0);
        ck_assert(simpleRes == 0);
        ck_assert(complexRes == 0);
    }
END_TEST

START_TEST(test_Validate_Dyck_Failing)
    {
        char *open = "(";
        char *close = ")";
        char *order = ")(";
        char *complex = "(abc(Hi) - bu((t)a)sldfk)]])";
        char *complex2 = "(abc(Hi) - bu((t)a(sldfk)]])";

        int openRes = validateDyck(open);
        int closeRes = validateDyck(close);
        int orderRes = validateDyck(order);
        int complexRes = validateDyck(complex);
        int complex2Res = validateDyck(complex2);

        ck_assert(openRes != 0);
        ck_assert(closeRes != 0);
        ck_assert(orderRes != 0);
        ck_assert(complexRes != 0);
        ck_assert(complex2Res != 0);
    }
END_TEST

static void validateEquality(char *function, Function expected, Function actual)
{
    printf(">>> %s\n", function);
    printf("=== ");
    printFunction(expected);
    printf("<<< ");
    printFunction(actual);

    for (int i = 0;; i++)
    {
        ck_assert(actual[i].atomType == expected[i].atomType);
        switch(actual[i].atomType)
        {
            case value:
                ck_assert(actual[i].atom.value.real == expected[i].atom.value.real);
                ck_assert(actual[i].atom.value.imaginary == expected[i].atom.value.imaginary);
                break;
            case operator:
                ck_assert(actual[i].atom.op == expected[i].atom.op);
                break;
            case paranthesis:
                ck_assert(actual[i].atom.paranthesis == expected[i].atom.paranthesis);
                break;
            case end:
                return;
            default:
                fprintf(stderr, "Unknown atom type: %d\n", actual[i].atomType);
                continue;
        }
    }
}

#endif //BACKEND_CHECK_PARSER_H
