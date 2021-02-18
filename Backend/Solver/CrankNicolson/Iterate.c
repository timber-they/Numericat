#include "Iterate.h"
#include "../Matrix/Complex.h"
#include <stdlib.h>
#include <stdio.h>

// Rest energy for a proton in MeV
#define E0p 938.27
// In MeV pm
#define hBarc 0.1973
// Speed of light in pm/as
#define c 302

void normalize(Complex **normalized, int n)
{
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int j = 0; j < nx; j++)
        {
            sum += absSquareComplex(normalized[i][j]) * dx;
        }
        for (int j = 0; j < nx; j++)
        {
            normalized[i][j] = divideComplex(normalized[i][j], (Complex) {.real = sum, . imaginary = 0});
        }
    }
}

static Matrix createInitialDerivative()
{
    Matrix res = createMatrix(nx, nx);
    // Main diagonal
    for (int i = 0; i < nx; i++)
        res.matrix[i][i] = (Complex) {.real = -2, .imaginary = 0};
    // Secondary diagonals
    for (int i = 0; i < nx - 1; i++)
    {
        res.matrix[i + 1][i] = (Complex) {.real = 1, .imaginary = 0};
        res.matrix[i][i+1] = (Complex) {.real = 1, .imaginary = 0};
    }

    Complex f = (Complex) {.real = 0, .imaginary = -hBarc * c / (2 * E0p) / (dx * dx)};
    return factorIpTri(res, f);
}

static Matrix createPotentialMatrix(Matrix potentialValues)
{
    Matrix res = createMatrix(nx, nx);
    for (int i = 0; i < nx; i++)
        res.matrix[i][i] = potentialValues.matrix[i][0];

    Complex f = (Complex) {.real = 0, .imaginary = c / hBarc};
    return factorIpTri(res, f);
}

static Matrix functionToVector(Function func, double d, int n, double t)
{
    Complex *res = malloc(n * sizeof(*res));
    for (int i = 0; i < n; i++)
        res[i] = evaluate(func, (Input) {.x = d * i, .t = t});

    Matrix matrix = arrayToMatrix(res, n);
    free(res);
    return matrix;
}

Complex **Iterate1d(Function potential, Function psi0, int n)
{
    Complex **res = malloc(n * sizeof(*res));
    // nx * nx
    Matrix d2 = createInitialDerivative();
    // nx * nx
    Matrix ident = identity(nx);

    // 1 * nx
    Matrix psi = functionToVector(psi0, dx, nx, 0);

    Matrix potentialValues = functionToVector(potential, dx, nx, 0);
    Matrix potentialMatrix = createPotentialMatrix(potentialValues);
    int timeDependent = isTimeDependent(potential);

    for (int i = 0; i < n-1; i++)
    {
        printf("i=%d\n", i);
        res[i] = matrixToArray(psi);
        // A = (I - dt/2 * (D2 + V))
        Matrix s = sumTri(potentialMatrix, d2);
        Matrix f = factorIpTri(s, (Complex) {.real = dt/2, .imaginary = 0});
        Matrix a = subtractTri(ident, f);
        // b = (I + dt/2 * (D2 + V)) * Psi
        Matrix b = multiplyTri(sumIpTri(f, ident), psi);
        freeMatrix(f);

        Matrix psiN = thomasSolve(a, b);
        // Validate
        /*Matrix tB = multiply(a, psiN);
        for (int j = 0; j < tB.rowCount; j++)
        {
            double diff = absSquareComplex(subtractComplex(b.matrix[j][0], tB.matrix[j][0]));
            if (diff < 0)
                diff = -diff;
            if (diff > 0.00001)
                fprintf(stderr, "Diff is %lf\n", diff);
        }
        freeMatrix(tB);*/
        freeMatrix(a);
        freeMatrix(b);
        freeMatrix(psi);
        psi = psiN;
        if (timeDependent)
        {
            freeMatrix(potentialValues);
            freeMatrix(potentialMatrix);
            // 1 * nx
            potentialValues = functionToVector(potential, dx, nx, i * dt);
            // nx * nx
            potentialMatrix = createPotentialMatrix(potentialValues);
        }
    }
    normalize(res, n);
    res[n - 1] = matrixToArray(psi);

    freeMatrix(potentialValues);
    freeMatrix(potentialMatrix);
    freeMatrix(psi);
    freeMatrix(ident);
    freeMatrix(d2);

    return res;
}
