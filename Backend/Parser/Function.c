#include "Function.h"
#include <stdio.h>
#include <math.h>

static Complex applyOperator(Complex current, Complex operand, Operator operator);

static Function findClosingParanthesis(Function start);

// Note that this finds the _last_ operator in order to preserve precedence
static Function findOperator(Operator op, Function func);

static Function findEnd(Function func);

static Complex evaluateAtomic(Function func, Input in);

// TODO: This function is too long
Complex evaluate(Function func, Input in) // NOLINT(misc-no-recursion)
{
    Complex lhs, rhs;
    Operator op;
    AtomType prevType;

    Function ptr = NULL;
    Function plusPtr = findOperator(plus, func),
             minusPtr = findOperator(minus, func),
             timesPtr = findOperator(times, func),
             dividePtr = findOperator(divide, func),
             powerPtr = findOperator(power, func);

    if (plusPtr != NULL && (minusPtr == NULL || plusPtr < minusPtr)) {
        ptr = plusPtr;
        op = plus;
    } else if (minusPtr != NULL) {
        ptr = minusPtr;
        op = minus;
    } else if (timesPtr != NULL && (dividePtr == NULL || timesPtr < dividePtr)) {
        ptr = timesPtr;
        op = times;
    } else if (dividePtr != NULL) {
        ptr = dividePtr;
        op = divide;
    } else if (powerPtr != NULL) {
        ptr = powerPtr;
        op = power;
    }

    if (ptr == NULL)
    {
        if (func->atomType == paranthesis)
        {
            // Must be opening
            Function closing = findClosingParanthesis(func);
            if (closing == NULL)
                return (Complex) {.real = -1, .imaginary = 0};
            prevType = closing->atomType;
            closing->atomType = end;
            lhs = evaluate(func + 1, in);
            closing->atomType = prevType;

            if (closing[1].atomType == end) {
                return lhs;
            }
        }
        else
            // Length must be 1
            return evaluateAtomic(func, in);
    }

    prevType = ptr->atomType;
    ptr->atomType = end;
    lhs = evaluate(func, in);
    rhs = evaluate(ptr + 1, in);
    ptr->atomType = prevType;

    return applyOperator(lhs, rhs, op);
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
    for (iter = findEnd(func); iter > func && (depth != 0 || iter->atomType != operator || iter->atom.op != op); iter--)
    {
        if (iter->atomType != paranthesis)
            continue;
        if (iter->atom.paranthesis == open)
            depth--;
        if (iter->atom.paranthesis == close)
            depth++;
    }
    return iter->atomType == operator && iter->atom.op == op ? iter : NULL;
}

static Function findEnd(Function func)
{
    Function iter;
    for (iter = func; iter->atomType != end; iter++);
    return iter;
}

static Complex evaluateAtomic(Function func, Input in)
{
    switch(func->atomType)
    {
        case value:
            return func->atom.value;
        case variable:
            switch(func->atom.variable)
            {
                case variableX:
                    return (Complex) {.real = in.x, .imaginary = 0};
                case variableT:
                    return (Complex) {.real = in.t, .imaginary = 0};
                default:
                    fprintf(stderr, "Unexpected variable: %d\n", func->atom.variable);
                    return (Complex) {.real = -1, .imaginary = 0};
            }
            break;
        default:
            fprintf(stderr, "Unexpected atomic: %d\n", func->atomType);
            return (Complex) {.real = -1, .imaginary = 0};
    }
}

static Complex applyOperator(Complex current, Complex operand, Operator operator)
{
    switch (operator)
    {
        case plus:
            return sumComplex(current, operand);
        case minus:
            return subtractComplex(current, operand);
        case times:
            return multiplyComplex(current, operand);
        case divide:
            return divideComplex(current, operand);
        case power:
            return powerComplex(current, operand);
        default:
            fprintf(stderr, "Unexpected operator %d\n", operator);
            return (Complex) {.real = -1, .imaginary = 0};
    }
}

void printFunction(Function func)
{
    while (1)
    {
        switch (func->atomType)
        {
            case value:
                printComplex(func->atom.value);
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
