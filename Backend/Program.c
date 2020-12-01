#include "Program.h"
#include <stdio.h>
#include "Parser/Function.h"
#include "Parser/Parser.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
int main(int argc, char *argv[])
{
    double value;
    Function function;
    if (argc != 3)
    {
        fprintf(stderr, "Expected %s <function> <value> (2 arguments), but got %d argument%s\n",
                argv[0], argc - 1, argc == 1 ? "" : "s");
        return 1;
    }

    if (sscanf(argv[2], "%lf", &value) != 1)
    {
        fprintf(stderr, "Couldn't cast %s to double\n", argv[2]);
        return 1;
    }
    printf("x=%lf\n", value);

    function = Parse(argv[1]);
    if (function == NULL)
    {
        fprintf(stderr, "Couldn't parse '%s'\n", argv[1]);
        return 1;
    }
    Print(function);

    printf("Result: %lf\n", Evaluate(function, value));

    return 0;
}
#pragma clang diagnostic pop
