#include "Function.h"
#include <stdio.h>

static double applyOperator(double current, double operand, Operator operator);

double Evaluate(Function func, double in)
{
    double operand;
    double current = 0;
    while (1)
    {
        switch (func->atomType)
        {
            case value:
                // Must be the start
                current = func->atom.value;
                func++;
                break;
            case variable:
                // Must be the start
                current = in;
                func++;
                break;
            case operator:
                switch ((func+1)->atomType)
                {
                    case value:
                        operand = (func+1)->atom.value;
                        break;
                    case variable:
                        operand = in;
                        break;
                    default:
                        fprintf(stderr, "Unexpected operand\n");
                        return -1;
                }
                current = applyOperator(current, operand, func->atom.op);
                func += 2;
                break;
            case end:
                return current;
        }
    }
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
        default:
            fprintf(stderr, "Unexpected operator %d\n", operator);
            return -1;
    }
}

void Print(Function func)
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
