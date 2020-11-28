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
    while (!func->end)
    {
        if (func->isValue)
            printf("%f", func->atom.value);
        else
            switch (func->atom.operator)
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
        func++;
    }
    printf("\n");
}
