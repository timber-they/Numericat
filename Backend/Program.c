#include "Program.h"
#include <stdio.h>
#include "Parser/Parser.h"
#include "Solver/CrankNicolson/Iterate.h"
#include <stdlib.h>

#define FILE_NAME "output"

int main(int argc, char *argv[])
{
    Function potential, initial;
    if (argc != 3)
    {
        fprintf(stderr, "Expected %s <potential function> <initial function> (2 arguments), but got %d argument%s\n",
                argv[0], argc - 1, argc == 1 ? "" : "s");
        return 1;
    }

    potential = parseFunction(argv[1]);
    if (potential == NULL)
    {
        fprintf(stderr, "Couldn't parse '%s'\n", argv[1]);
        return 1;
    }
    initial = parseFunction(argv[2]);
    if (initial == NULL)
    {
        fprintf(stderr, "Couldn't parse '%s'\n", argv[2]);
        return 1;
    }
    printFunction(potential);
    printFunction(initial);

    int n = 200;
    Complex **res = Iterate1d(potential, initial, n);
    writeResults(res, potential, n);

    for (int i = 0; i < n; i++)
        free(res[i]);
    free(res);
    free(potential);
    free(initial);

    return 0;
}

void writeResults(Complex **data, Function potential, int n)
{
    FILE *fp = fopen(FILE_NAME, "w");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            double el = absSquareComplex(data[i][j]);
            if (el < 0)
                el = -el;
            fprintf(fp, "%5f ", el);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            fprintf(fp, "%5f ", evaluate(potential, (Input) {.x = dx * j, .t = dt * i}).real);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

