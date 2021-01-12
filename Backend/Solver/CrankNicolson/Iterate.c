#include "Iterate.h"
#include <stdlib.h>

#define nx 1001
#define dx 0.001
// MeV pm
#define hbar 0.1973

static Matrix createInitialDerivative()
{
    Matrix res = createMatrix(nx, nx);
    // Main diagonal
    for (int i = 0; i < nx; i++)
        res.matrix[i][i] = -2;
    // Secondary diagonals
    for (int i = 0; i < nx - 1; i++)
    {
        res.matrix[i + 1][i] = 1;
        res.matrix[i][i+1] = 1;
    }

    return res;
}

static Matrix createPotentialMatrix(double *potentialValues)
{
    Matrix res = createMatrix(nx, nx);
    for (int i = 0; i < nx; i++)
        res.matrix[i][i] = potentialValues[i];
}

static double *functionToArray(Function func, double d, int n)
{
    double *res = malloc(n * sizeof(*res));
    for (int i = 0; i < n; i++)
        res[i] = Evaluate(func, d * i);
    return res;
}

double **Iterate1d(Function potential, Function psi0, double dt, int n)
{
    double **res = malloc(n * sizeof(*res));
    Matrix d2 = createInitialDerivative();
    Matrix identity = identity(nx);

    double *psi = functionToArray(psi0, dx, nx);
    double *potentialValues = functionToArray(potential, dx, nx);
    Matrix potential = createPotentialMatrix(potentialValues);
    free(potentialValues);

    for (int i = 0; i < n; i++)
    {
        double t = i * dt;

    }

    free(psi);


    return NULL;
}
