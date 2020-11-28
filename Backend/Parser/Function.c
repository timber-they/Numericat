#include "Function.h"
#include <stdio.h>

double Evaluate(Function func, double in)
{
    printf("In: %f, for func with size %lu\n", in, sizeof(func));
    // TODO
    return -1;
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
