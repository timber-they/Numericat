#include "Program.h"
#include <stdio.h>
#include "Parser/Function.h"
#include "Parser/Parser.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Expected %s <function> (1 argument), but got %d arguments\n", argv[0], argc - 1);
        return 1;
    }

    Function function = Parse(argv[1]);
    if (function == NULL)
    {
        fprintf(stderr, "Couldn't parse '%s'\n", argv[1]);
        return 1;
    }
    Print(function);

    return 0;
}
