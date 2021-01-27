#include "Function.h"
#include <stdio.h>
#include <math.h>

static double applyOperator(double current, double operand, Operator operator);

static Function findClosingParanthesis(Function start);

static Function findOperator(Operator op, Function func);

static double evaluateAtomic(Function func, double in);

// TODO: This function is too long
double evaluate(Function func, double in) // NOLINT(misc-no-recursion)
{
    printf("Evaluating ");
    printFunction(func);
    double lhs, rhs;
    Operator op;
    AtomType prevType;

    Function ptr = NULL;
    Function plusPtr = findOperator(plus, func);
    Function minusPtr = findOperator(minus, func);
    Function timesPtr = findOperator(times, func);
    Function dividePtr = findOperator(divide, func);
    Function powerPtr = findOperator(power, func);

    if (plusPtr != NULL && (minusPtr == NULL || plusPtr < minusPtr)) {
        printf("Plus...\n");
        ptr = plusPtr;
        op = plus;
    } else if (minusPtr != NULL) {
        printf("Minus...\n");
        ptr = minusPtr;
        op = minus;
    } else if (timesPtr != NULL && (dividePtr == NULL || timesPtr < dividePtr)) {
        printf("Times...\n");
        ptr = timesPtr;
        op = times;
    } else if (dividePtr != NULL) {
        printf("Divide...\n");
        ptr = dividePtr;
        op = divide;
    } else if (powerPtr != NULL) {
        printf("Power...\n");
        ptr = powerPtr;
        op = power;
    }

    if (ptr == NULL) {
        if (func->atomType == paranthesis)
        {
            printf("Paranthesis...\n");
            // Must be opening
            Function closing = findClosingParanthesis(func);
            if (closing == NULL)
                return -1;
            prevType = closing->atomType;
            closing->atomType = end;
            lhs = evaluate(func + 1, in);
            closing->atomType = prevType;

            if (closing[1].atomType == end) {
                return lhs;
            }
        }
        else
        {
            printf("Atomic...\n");
            // Length must be 1
            return evaluateAtomic(func, in);
        }
    }

    prevType = ptr->atomType;
    ptr->atomType = end;
    lhs = evaluate(func, in);
    rhs = evaluate(ptr + 1, in);
    ptr->atomType = prevType;

    double res = applyOperator(lhs, rhs, op);
    printf("\t = %lf\n", res);
    return res;
}

static Function findClosingParanthesis(Function start)
{
    int depth = 1;
    Function iter;
    for (iter = start+1; iter->atomType != end; iter++)
    {
        if (iter->atomType != paranthesis)
            continue;
        if (iter->atom.paranthesis == open)
            depth++;
        if (iter->atom.paranthesis == close)
            depth--;
        if (depth == 0)
            break;
    }

    if (depth != 0)
    {
        fprintf(stderr, "Couldn't find closing paranthesis\n");
        return NULL;
    }
    if (iter->atomType != paranthesis)
        fprintf(stderr, "Hang on what?\n");

    return iter;
}

static Function findOperator(Operator op, Function func)
{
    int depth = 0;
    Function iter;
    for (iter = func; iter->atomType != end &&
                      (depth != 0 || iter->atomType != operator || iter->atom.op != op); iter++)
    {
        if (iter->atomType != paranthesis)
            continue;
        if (iter->atom.paranthesis == open)
            depth++;
        if (iter->atom.paranthesis == close)
            depth--;
    }
    return iter->atomType == operator && iter->atom.op == op ? iter : NULL;
}

static double evaluateAtomic(Function func, double in)
{
    if (func->atomType == value)
        return func->atom.value;
    if (func->atomType == variable)
        return in;
    fprintf(stderr, "Expected atomic\n");
    return -1;
}

static double applyOperator(double current, double operand, Operator operator)
{
    switch (operator)
    {
        case plus:
            return current + operand;
        case minus:
            return current - operand;
        case times:
            return current * operand;
        case divide:
            return current / operand;
        case power:
            return pow(current, operand);
        default:
            fprintf(stderr, "Unexpected operator %d\n", operator);
            return -1;
    }
}

void printFunction(Function func)
{
    while (1)
    {
        switch (func->atomType)
        {
            case value:
                printf("%f", func->atom.value);
                break;
            case operator:
                switch (func->atom.op)
                {
                    case plus:
                        printf("+");
                        break;
                    case minus:
                        printf("-");
                        break;
                    case times:
                        printf("*");
                        break;
                    case divide:
                        printf("/");
                        break;
                    case power:
                        printf("^");
                        break;
                }
                break;
            case paranthesis:
                switch(func->atom.paranthesis)
                {
                    case open:
                        printf("(");
                        break;
                    case close:
                        printf(")");
                        break;
                }
                break;
            case variable:
                printf("x");
                break;
            case end:
                printf("\n");
                return;
        }
        func++;
    }
}
