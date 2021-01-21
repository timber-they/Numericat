#include "Iterate.h"
#include <stdlib.h>
#include <stdio.h>

static Matrix createInitialDerivative()
{
    // TODO: Constants aren't applied yet
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
    printf("n=%d, d=%lf\n", n, d);
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
    printf("V:\n");
    printMatrix(potentialValues);
    freeMatrix(potentialValues);

    for (int i = 0; i < n-1; i++)
    {
        printf("Psi:\n");
        printMatrix(psi);
//        printf("D2:\n");
//        printMatrix(d2);
        printf("i=%d\n", i);
        res[i] = matrixToArray(psi);
        // A = (I - dt/2 * (D2 + V))
        Matrix s = sum(d2, potentialMatrix);
//        printf("D2+V\n");
//        printMatrix(s);
        Matrix f = factor(s, dt/2);
//        printf("dt/2 (%lf) * (D2+V)\n", dt/2);
//        printMatrix(f);
        freeMatrix(s);
        Matrix a = subtract(ident, f);
        // b = (I + dt/2 * (D2 + V)) * Psi
        s = sum(ident, f);
//        printf("I + dt/2 * (D2 + V)\n");
//        printMatrix(s);
        freeMatrix(f);
        Matrix b = multiply(s, psi);
        freeMatrix(s);

//        printf("A:\n");
//        printMatrix(a);
//        printf("b:\n");
//        printMatrix(b);

        Matrix psiN = thomasSolve(a, b);
//        printf("PsiN:\n");
//        printMatrix(psiN);
        // Validate
        Matrix tB = multiply(a, psiN);
        for (int j = 0; j < tB.rowCount; j++)
        {
            double diff = b.matrix[j][0] - tB.matrix[j][0];
            if (diff < 0)
                diff = -diff;
            if (diff > 0.00001)
                fprintf(stderr, "Diff is %lf\n", diff);
        }
        freeMatrix(tB);
        freeMatrix(a);
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
