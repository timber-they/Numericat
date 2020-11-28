#include "Parser.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>

Function Parse(char *raw)
{
    printf("Raw: %s\n", raw);
    // TODO
    return NULL;
}

double Evaluate(Function func, double in)
{
    printf("In: %f, for func with size %lu\n", in, sizeof(func));
    // TODO
    return -1;
}
