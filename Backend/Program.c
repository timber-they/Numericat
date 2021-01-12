#include "Program.h"
#include <stdio.h>
#include "Parser/Function.h"
#include "Parser/Parser.h"
#include "Solver/CrankNicolson/Iterate.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Function potential, initial;
    if (argc != 3)
    {
        fprintf(stderr, "Expected %s <potential function> <initial function> (2 arguments), but got %d argument%s\n",
                argv[0], argc - 1, argc == 1 ? "" : "s");
        return 1;
    }

    potential = Parse(argv[1]);
    if (potential == NULL)
    {
        fprintf(stderr, "Couldn't parse '%s'\n", argv[1]);
        return 1;
    }
    initial = Parse(argv[2]);
    if (initial == NULL)
    {
        fprintf(stderr, "Couldn't parse '%s'\n", argv[2]);
        return 1;
    }
    Print(potential);
    Print(initial);

    double **res = Iterate1d(potential, initial, 0.1, 1);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 10; j++)
            printf("%5f ", res[i][j]);
        printf("\n");
    }

    free(potential);
    free(initial);

    return 0;
}

