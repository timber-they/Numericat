#include "Iterate.h"
#include <stdlib.h>
#include <stdio.h>

#define nx 10//01
#define dx 0.001

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

static Matrix createPotentialMatrix(Matrix potentialValues)
{
    Matrix res = createMatrix(nx, nx);
    for (int i = 0; i < nx; i++)
        res.matrix[i][i] = potentialValues.matrix[i][0];
    return res;
}

static Matrix functionToVector(Function func, double d, int n)
{
    double *res = malloc(n * sizeof(*res));
    for (int i = 0; i < n; i++)
        res[i] = Evaluate(func, d * i);
    Matrix matrix = arrayToMatrix(res, n);
    free(res);
    return matrix;
}

double **Iterate1d(Function potential, Function psi0, double dt, int n)
{
    double **res = malloc(n * sizeof(*res));
    // nx * nx
    Matrix d2 = createInitialDerivative();
    // nx * nx
    Matrix ident = identity(nx);

    // 1 * nx
    Matrix psi = functionToVector(psi0, dx, nx);
    // 1 * nx
    Matrix potentialValues = functionToVector(potential, dx, nx);
    // nx * nx
    Matrix potentialMatrix = createPotentialMatrix(potentialValues);
    freeMatrix(potentialValues);

    for (int i = 0; i < n; i++)
    {
        printf("i=%d\n", i);
        res[i] = matrixToArray(psi);
        // A = (I - dt/2 * (D2 + V))
        Matrix a = subtract(ident, factor(sum(d2, potentialMatrix), dt/2));
        // b = (I + dt/2 * (D2 + V)) * Psi
        Matrix b = multiply(sum(ident, factor(sum(d2, potentialMatrix), dt/2)), psi);

        printf("Solving...\n");
        Matrix psiN = thomasSolve(a, b);
        printf("Solved\n");
        freeMatrix(b);
        freeMatrix(psi);
        psi = psiN;
    }
    res[n-1] = matrixToArray(psi);

    freeMatrix(psi);
    freeMatrix(potentialMatrix);
    freeMatrix(ident);
    freeMatrix(d2);

    return res;
}
