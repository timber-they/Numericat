#include "Function.h"
#include <stdio.h>
#include <math.h>

struct Splitter{
    Function ptr;
    Operator op;
};

static Complex applyOperator(Complex current, Complex operand, Operator operator);

static Function findClosingParanthesis(Function start);

// Note that this finds the _last_ operator in order to preserve precedence
static Function findOperator(Operator op, Function func, Function end);

static Function findEnd(Function func);

static Complex evaluateAtomic(Function func, Input in);

static struct Splitter getSplitter(Function func);

static Complex evaluateParanthesis(Function func, Function closing, Input in);

static Complex evaluateFunction(Function func, Complex rhs);

Complex evaluate(Function func, Input in) // NOLINT(misc-no-recursion)
{
    Complex lhs, rhs;
    AtomType prevType;

    struct Splitter splitter = getSplitter(func);
    Function ptr = splitter.ptr;
    Operator op = splitter.op;

    if (ptr == NULL)
    {

        Function closing;
        switch (func->atomType)
        {
            case paranthesis:
                // Must be opening
                closing = findClosingParanthesis(func);
                if (closing == NULL)
                    return (Complex) {.real = -1, .imaginary = 0};

                lhs = evaluateParanthesis(func, closing, in);

                if (closing[1].atomType == end)
                    return lhs;
                fprintf(stderr, "Expected end after paranthesis\n");
                return (Complex) {.real = -1, .imaginary = 0};
            case function:
                switch((func+1)->atomType)
                {
                    case end:
                        fprintf(stderr, "Expected parameter after function call\n");
                        return (Complex) {.real = -1, .imaginary = 0};
                    case paranthesis:
                        closing = findClosingParanthesis(func+1);
                        if (closing == NULL)
                            return (Complex) {.real = -1, .imaginary = 0};

                        rhs = evaluateParanthesis(func+1, closing, in);
                        break;
                    default:
                        rhs = evaluateAtomic(func+1, in);
                        break;
                }
                return evaluateFunction(func, rhs);
                break;
            default:
                // Length must be 1
                return evaluateAtomic(func, in);
        }
    }

    prevType = ptr->atomType;
    ptr->atomType = end;
    lhs = evaluate(func, in);
    rhs = evaluate(ptr + 1, in);
    ptr->atomType = prevType;

    return applyOperator(lhs, rhs, op);
}

static Complex evaluateFunction(Function func, Complex rhs)
{
    switch(func->atom.function)
    {
        case fsin:
            break;
        case fcos:
            break;
        case ftan:
            break;
        case fexp:
            break;
        case fdelta:
            break;
        case ftheta:
            break;
    }
    return (Complex) {0};
}

static Complex evaluateParanthesis(Function func, Function closing, Input in)
{
    AtomType prevType = closing->atomType;
    closing->atomType = end;
    Complex res = evaluate(func + 1, in);
    closing->atomType = prevType;
    return res;
}

static struct Splitter getSplitter(Function func)
{
    Operator op = {0};
    Function endPtr = findEnd(func);
    Function ptr = NULL;
    Function plusPtr = findOperator(plus, func, endPtr),
            minusPtr = findOperator(minus, func, endPtr);

    if (plusPtr != NULL && (minusPtr == NULL || plusPtr > minusPtr))
    {
        ptr = plusPtr;
        op = plus;
    } else if (minusPtr != NULL)
    {
        ptr = minusPtr;
        op = minus;
    } else
    {
        Function timesPtr = findOperator(times, func, endPtr),
                dividePtr = findOperator(divide, func, endPtr);
        if (timesPtr != NULL && (dividePtr == NULL || timesPtr > dividePtr))
        {
            ptr = timesPtr;
            op = times;
        } else if (dividePtr != NULL)
        {
            ptr = dividePtr;
            op = divide;
        } else
        {
            Function powerPtr = findOperator(power, func, endPtr);
            if (powerPtr != NULL)
            {
                ptr = powerPtr;
                op = power;
            }
        }
    }

    return (struct Splitter) {.op = op, .ptr = ptr};
}

static Function findClosingParanthesis(Function start)
{
    int depth = 1;
    Function iter;
    for (iter = start + 1; iter->atomType != end; iter++)
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

static Function findOperator(Operator op, Function func, Function end)
{
    int depth = 0;
    Function iter;
    for (iter = end; iter > func && (depth != 0 || iter->atomType != operator || iter->atom.op != op); iter--)
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
    switch (func->atomType)
    {
        case value:
            return func->atom.value;
        case variable:
            switch (func->atom.variable)
            {
                case variableX:
                    return (Complex) {.real = in.x, .imaginary = 0};
                case variableT:
                    return (Complex) {.real = in.t, .imaginary = 0};
                default:
                    fprintf(stderr, "Unexpected variable: %d\n", func->atom.variable);
                    return (Complex) {.real = -1, .imaginary = 0};
            }
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
                switch (func->atom.paranthesis)
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
            case function:
                switch(func->atom.function)
                {
                    case fsin:
                        printf("sin");
                        break;
                    case fcos:
                        printf("cos");
                        break;
                    case ftan:
                        printf("tan");
                        break;
                    case fexp:
                        printf("exp");
                        break;
                    case fdelta:
                        printf("delta");
                        break;
                    case ftheta:
                        printf("theta");
                        break;
                }
            case end:
                printf("\n");
                return;
        }
        func++;
    }
}

int isTimeDependent(Function func)
{
    if (func == NULL)
        return 0;
    int i = 0;
    for (Function iter = func; iter->atomType != end; iter++)
    {
        if (iter->atomType == variable && iter->atom.variable == variableT)
        {
            printf("Found t at %d\n", i);
            return 1;
        }
        i++;
    }
    return 0;
}
