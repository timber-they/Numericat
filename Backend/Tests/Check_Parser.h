#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../Parser/Parser.h"
#include "TestHelper.h"

#ifndef BACKEND_CHECK_PARSER_H
#define BACKEND_CHECK_PARSER_H

START_TEST(test_Parse_Functions)
{
    char *function1 = " 8861/7i+x*6";
    char *function2 = "(1/29+x*9-88/t^((x-1)))-i";
    char *function3 = "s(2*x)*d(t-3)+e(x^2)/c(x+a(42i))*hx";

    Element expected1[] =
    {
        (Element) {.atomType = value, .atom.value=COMPLEX(8861,0)},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = value, .atom.value=COMPLEX(0,7)},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = variable, .atom.value=COMPLEX(0,0)},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = value, .atom.value=COMPLEX(6,0)},
        (Element) {.atomType = end, .atom.value={0}}
    };
    Element expected2[] =
    {
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = value, .atom.value=COMPLEX(1,0)},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = value, .atom.value=COMPLEX(29,0)},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = variable, .atom.variable=variableX},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = value, .atom.value=COMPLEX(9,0)},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=COMPLEX(88,0)},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = variable, .atom.variable=variableT},
        (Element) {.atomType = operator, .atom.op=power},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = variable, .atom.variable=variableX},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=COMPLEX(1,0)},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=COMPLEX(0,1)},
        (Element) {.atomType = end, .atom.value={0}}
    };

    Element expected3[] =
    {
        (Element) {.atomType = function, .atom.function=fsin},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = value, .atom.value=COMPLEX(2,0)},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = variable, .atom.variable=variableX},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = function, .atom.function=fdelta},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = variable, .atom.variable=variableT},
        (Element) {.atomType = operator, .atom.op=minus},
        (Element) {.atomType = value, .atom.value=COMPLEX(3,0)},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = function, .atom.function=fexp},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = variable, .atom.variable=variableX},
        (Element) {.atomType = operator, .atom.op=power},
        (Element) {.atomType = value, .atom.value=COMPLEX(2,0)},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = operator, .atom.op=divide},
        (Element) {.atomType = function, .atom.function=fcos},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = variable, .atom.variable=variableX},
        (Element) {.atomType = operator, .atom.op=plus},
        (Element) {.atomType = function, .atom.function=ftan},
        (Element) {.atomType = paranthesis, .atom.paranthesis=open},
        (Element) {.atomType = value, .atom.value=COMPLEX(0,42)},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = paranthesis, .atom.paranthesis=close},
        (Element) {.atomType = operator, .atom.op=times},
        (Element) {.atomType = function, .atom.function=ftheta},
        (Element) {.atomType = variable, .atom.variable=variableX},
        (Element) {.atomType = end, .atom.value={0}}
    };

    Function actual1 = parseFunction(function1);
    Function actual2 = parseFunction(function2);
    Function actual3 = parseFunction(function3);

    assertFunctionsEq(function1, expected1, actual1);
    assertFunctionsEq(function2, expected2, actual2);
    assertFunctionsEq(function3, expected3, actual3);

    free(actual1);
    free(actual2);
    free(actual3);
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
    char *doubleVariable = "x t";
    char *tailingOperator = "2+";
    char *missingOperator = "(2+x)(3)";
    char *complexInNumber = "1i2";

    Function emptyRes = parseFunction(empty);
    Function nullRes = parseFunction(null);
    Function doubleOperatorRes = parseFunction(doubleOperator);
    Function doubleValueRes = parseFunction(doubleValue);
    Function valueVariableRes = parseFunction(valueVariable);
    Function variableValueRes = parseFunction(variableValue);
    Function doubleVariableRes = parseFunction(doubleVariable);
    Function tailingOperatorRes = parseFunction(tailingOperator);
    Function missingOperatorRes = parseFunction(missingOperator);
    Function complexInNumberRes = parseFunction(complexInNumber);

    ck_assert(emptyRes == NULL);
    ck_assert(nullRes == NULL);
    ck_assert(doubleOperatorRes == NULL);
    ck_assert(doubleValueRes == NULL);
    ck_assert(valueVariableRes == NULL);
    ck_assert(variableValueRes == NULL);
    ck_assert(doubleVariableRes == NULL);
    ck_assert(tailingOperatorRes == NULL);
    ck_assert(missingOperatorRes == NULL);
    ck_assert(complexInNumberRes == NULL);
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

#endif //BACKEND_CHECK_PARSER_H
