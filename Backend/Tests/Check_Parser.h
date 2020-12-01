#include "../Parser/Parser.h"
#include <stdio.h>
#include "check.h"

#ifndef BACKEND_CHECK_PARSER_H
#define BACKEND_CHECK_PARSER_H

static void validateEquality(char *function, Function expected, Function actual);

START_TEST(test_Parse_Functions)
{
    char *function1 = " 8861/7+x*6";
    char *function2 = "1/29+x*9-88/x";

    Element expected1[] =
    {
        (Element) {.atomType = value, .atom.value=8861},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = value, .atom.value=7},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = variable, .atom.value=0},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = value, .atom.value=6},
        (Element) {.atomType = end, .atom.value=0}
    };
    Element expected2[] =
    {
        (Element) {.atomType = value, .atom.value=1},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = value, .atom.value=29},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = variable, .atom.value=0},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = value, .atom.value=9},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=88},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = variable, .atom.value=0},
        (Element) {.atomType = end, .atom.value=0},
    };

    Function actual1 = Parse(function1);
    Function actual2 = Parse(function2);

    validateEquality(function1, expected1, actual1);
    validateEquality(function2, expected2, actual2);
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

    Function emptyRes = Parse(empty);
    Function nullRes = Parse(null);
    Function doubleOperatorRes = Parse(doubleOperator);
    Function doubleValueRes = Parse(doubleValue);
    Function valueVariableRes = Parse(valueVariable);
    Function variableValueRes = Parse(variableValue);
    Function doubleVariableRes = Parse(doubleVariable);
    Function tailingOperatorRes = Parse(tailingOperator);

    ck_assert(emptyRes == NULL);
    ck_assert(nullRes == NULL);
    ck_assert(doubleOperatorRes == NULL);
    ck_assert(doubleValueRes == NULL);
    ck_assert(valueVariableRes == NULL);
    ck_assert(variableValueRes == NULL);
    ck_assert(doubleVariableRes == NULL);
    ck_assert(tailingOperatorRes == NULL);
}
END_TEST

static void validateEquality(char *function, Function expected, Function actual)
{
    printf(">>> %s\n", function);
    printf("=== ");
    Print(expected);
    printf("<<< ");
    Print(actual);

    for (int i = 0;; i++)
    {
        ck_assert(actual[i].atomType == expected[i].atomType);
        switch(actual[i].atomType)
        {
            case value:
                ck_assert(actual[i].atom.value == expected[i].atom.value);
                break;
            case operator:
                ck_assert(actual[i].atom.op == expected[i].atom.op);
                break;
            case end:
                return;
            default:
                continue;
        }
    }
}

#endif //BACKEND_CHECK_PARSER_H
