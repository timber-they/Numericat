#include "Utility.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void freeMatrix(Matrix a)
{
    for (int i = 0; i < a.dimension; i++)
        free(a.matrix[i]);
    free(a.matrix);
}

Matrix createMatrix(int r, int c)
{
    Matrix result = {r, c, calloc(r, sizeof(Complex *))};
    result.rowCount = r;
    result.columnCount = c;
    result.dimension = r;

    if (result.matrix == NULL)
    {
        // In case something goes wrong, I dont know what should go wrong
        fprintf(stderr, "Empty Matrix not allowed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < r; i++)
    {
        result.matrix[i] = calloc(c, sizeof result.matrix[i][0]);

        if (result.matrix[i] == NULL)
        {
            fprintf(stderr, "Empty Matrix Element not allowed\n");
            exit(EXIT_FAILURE);
        }
    }
    return result;
}

Matrix ones(int r, int c)
{
    Matrix m = createMatrix(r, c);
    for (int i = 0; i < m.rowCount; i++)
    {
        for (int j = 0; j < m.rowCount; j++)
        {
            m.matrix[i][j] = (Complex) {.real = 1.0, .imaginary = 0};
        }
    }
    return m;
}

Matrix identity(int n)
{
    Matrix result = createMatrix(n,n);
    for(int i = 0; i < n; i++)
    {
        result.matrix[i][i] = (Complex) {.real = 1.0, .imaginary = 0};
    }
    return result;
}

void printMatrix(Matrix m)
{
    int i,j;
    for(i = 0; i < m.rowCount ; i++)
    {
        for(j = 0; j < m.columnCount; j++)
        {
            printComplex(m.matrix[i][j]);
        }
        printf("\n");
    }
}

Matrix multiply(Matrix a, Matrix b)
{
    int l = a.rowCount;
    int m = a.columnCount;
    // check if multiplication is possible
    if (m != b.rowCount)
    {
        fprintf(stderr, "Error: columns of Matrix a = %d != %d = rows of Matrix b\n", a.columnCount, b.rowCount);
        exit(1);
    }
    int n = b.columnCount;

    Matrix result = createMatrix(l, n);

    for (int i = 0; i < l; i++)
        for (int k = 0; k < n; k++)
        {
            result.matrix[i][k] = (Complex) {0};
            for (int j = 0; j < m; j++)
                result.matrix[i][k] = sumComplex(result.matrix[i][k], multiplyComplex(a.matrix[i][j], b.matrix[j][k]));
        }
    return result;
}

Matrix multiplyTri(Matrix a, Matrix b)
{
    int l = a.rowCount;
    int m = a.columnCount;
    // check if multiplication is possible
    if (m != b.rowCount)
    {
        fprintf(stderr, "Error: columns of Matrix a = %d != %d = rows of Matrix b\n", a.columnCount, b.rowCount);
        exit(1);
    }
    if (l != m)
    {
        fprintf(stderr, "Error: a is not an nxn matrix and hence can't be tridiagonal\n");
        exit(2);
    }
    int n = b.columnCount;

    Matrix result = createMatrix(l, n);

    for (int i = 0; i < l; i++)
        for (int k = 0; k < n; k++)
        {
            result.matrix[i][k] = (Complex) {0};
            for (int j = (i == 0 ? 0 : i-1); j < (i == l-1 ? l : i + 2); j++)
                result.matrix[i][k] = sumComplex(result.matrix[i][k], multiplyComplex(a.matrix[i][j], b.matrix[j][k]));
        }
    return result;
}

Matrix sum(Matrix a, Matrix b)
{
    if(a.rowCount != b.rowCount || a.columnCount != b.columnCount){
        fprintf(stderr, "Error: a and b have different dimensions");
        exit(2);
    }
    int r = a.rowCount;
    int c = a.columnCount;
    Matrix result = createMatrix(r,c);
    int i,j;
    for(i = 0; i < r ; i++){
        for(j = 0; j < c; j++){
            result.matrix[i][j] = sumComplex(a.matrix[i][j], b.matrix[i][j]);
        }
    }

    return result;
}

Matrix sumIp(Matrix a, Matrix b)
{
    if(a.rowCount != b.rowCount || a.columnCount != b.columnCount){
        fprintf(stderr, "Error: a and b have different dimensions");
        exit(2);
    }
    int r = a.rowCount;
    int c = a.columnCount;
    Matrix result = a;
    int i,j;
    for(i = 0; i < r ; i++){
        for(j = 0; j < c; j++){
            result.matrix[i][j] = sumComplex(a.matrix[i][j], b.matrix[i][j]);
        }
    }

    return result;
}

Matrix subtract(Matrix a, Matrix b)
{
    if(a.rowCount != b.rowCount || a.columnCount != b.columnCount){
        fprintf(stderr, "Error: = matrices are not compatible for subtraction: a.rowCount != b.rowCount or "
                        "a.columnCount != b.columnCount");
        exit(2);
    }
    int r = a.rowCount;
    int c = a.columnCount;
    Matrix result = createMatrix(r,c);
    int i,j;
    for(i = 0; i < r ; i++){
        for(j = 0; j < c; j++){
            result.matrix[i][j] = subtractComplex(a.matrix[i][j], b.matrix[i][j]);

        }
    }
    return result;
}

Matrix arrayToMatrix(Complex *array, int n)
{
    Matrix result = createMatrix(n, 1);
    for(int i = 0; i < n; i++)
    {
        result.matrix[i][0] = array[i];
    }
    return result;
}

Complex *matrixToArray(Matrix m)
{
    Complex *result = malloc(m.rowCount * sizeof(*result));
    for(int i = 0; i < m.rowCount; i++)
    {
        result[i] = m.matrix[i][0];
    }
    return result;
}

Matrix factor(Matrix a, Complex f)
{
    int n = a.rowCount;
    Matrix result = createMatrix(n, n);

    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            result.matrix[i][j] = multiplyComplex(a.matrix[i][j], f);
        }
    }
    return result;
}

Matrix factorIp(Matrix a, Complex f)
{
    int n = a.rowCount;
    Matrix result = a;

    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            result.matrix[i][j] = multiplyComplex(a.matrix[i][j], f);
        }
    }
    return result;
}

// Mutable (result will be in d). Parameters are similar to https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm#Method
static Complex *thomasHelperSolve(Complex *a, Complex *b, Complex *c, Complex *d, int n)
{
    c[0] = divideComplex(c[0], b[0]);
    for (int i = 1; i < n-1; i++)
        c[i] = divideComplex(c[i], (subtractComplex(b[i], multiplyComplex(a[i], c[i-1]))));

    d[0] = divideComplex(d[0], b[0]);
    for (int i = 1; i < n; i++)
        d[i] = divideComplex(subtractComplex(d[i], multiplyComplex(a[i], d[i-1])),
                (subtractComplex(b[i], multiplyComplex(a[i], c[i-1]))));

    // Back substitution
    Complex *x = d;
    x[n-1] = d[n-1];
    for (int i = n-2; i >= 0; i--)
        x[i] = subtractComplex(d[i], multiplyComplex(c[i], x[i+1]));
    return x;
}

Matrix thomasSolve(Matrix m, Matrix r)
{
    if (m.columnCount != m.rowCount || m.columnCount != r.rowCount || r.columnCount != 1)
    {
        fprintf(stderr, "Invalid dimensions\n");
        exit(2);
    }

    int n = m.columnCount;
    Complex *a = malloc(n * sizeof(*a));
    Complex *b = malloc(n * sizeof(*b));
    Complex *c = malloc((n-1) * sizeof(*c));
    Complex *d = malloc(n * sizeof(*d));

    for (int i = 1; i < n; i++)
        a[i] = m.matrix[i][i-1];
    for (int i = 0; i < n; i++)
        b[i] = m.matrix[i][i];
    for (int i = 0; i < n-1; i++)
        c[i] = m.matrix[i][i+1];
    for (int i = 0; i < n; i++)
        d[i]= r.matrix[i][0];

    Complex *res = thomasHelperSolve(a, b, c, d, n);
    Matrix mRes = arrayToMatrix(res, n);

    free(a);
    free(b);
    free(c);
    free(d);

    return mRes;
}

