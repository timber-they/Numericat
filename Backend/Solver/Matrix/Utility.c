#include "Utility.h"
#include <math.h>
#include <stdbool.h>
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
    Matrix result = {r, c, calloc(r, sizeof(double *))};
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
            m.matrix[i][j] = 1;
        }
    }
    return m;
}

Matrix identity(int n)
{
    Matrix result = createMatrix(n,n);
    for(int i = 0; i < n; i++)
    {
        result.matrix[i][i] = 1;
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
            printf("%f  ", m.matrix[i][j]);
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
            result.matrix[i][k] = 0;
            for (int j = 0; j < m; j++)
                result.matrix[i][k] += a.matrix[i][j] * b.matrix[j][k];
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
            result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }

    return result;
}

Matrix subtract(Matrix a, Matrix b)
{
    if(a.rowCount != b.rowCount || a.columnCount != b.columnCount){
        fprintf(stderr, "Error: columns of Matrix a != rows of Matrix b");
        exit(2);
    }
    int r = a.rowCount;
    int c = a.columnCount;
    Matrix result = createMatrix(r,c);
    int i,j;
    for(i = 0; i < r ; i++){
        for(j = 0; j < c; j++){
            result.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];

        }
    }
    return result;
}

Matrix arrayToMatrix(double *array, int n)
{
    Matrix result = createMatrix(n, 1);
    for(int i = 0; i < n; i++)
    {
        result.matrix[i][0] = array[i];
    }
    return result;
}

double *matrixToArray(Matrix m)
{
    double *result = malloc(m.rowCount * sizeof(*result));
    for(int i = 0; i < m.rowCount; i++)
    {
        result[i] = m.matrix[i][0];
    }
    return result;
}

Matrix factor(Matrix a, double f)
{
    int n = a.rowCount;
    Matrix result = createMatrix(n, n);

    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            result.matrix[i][j] = a.matrix[i][j] * f;
        }
    }
    return result;
}

double determinant(Matrix a)
{
    int i, j, x, y;
    double det = 0;
    Matrix m = createMatrix(a.columnCount - 1, a.rowCount - 1);
    int n = a.rowCount;

    if (n < 1)
    { /* Error */
        fprintf(stderr, "dimension is < 1");
        exit(EXIT_FAILURE);
    }
    else if (n == 1)
    {
        det = a.matrix[0][0];
    }
    else if (n == 2)
    {
        det = a.matrix[0][0] * a.matrix[1][1] - a.matrix[1][0] * a.matrix[0][1];
    }
    else
    {
        det = 0;
        for (x = 0; x < n ; x++)
        {
            // determinant expansion by minors
            for (i=1; i<n; i++)
            {
                y = 0;
                for (j=0; j<n; j++)
                {
                    if (j == x)
                    {
                        continue;
                    }
                    m.matrix[i-1][y] = a.matrix[i][j];
                    y++;
                }
            }
            det += pow(-1.0,1.0+x+1.0) * a.matrix[0][x] * determinant(m);
        }
    }
    freeMatrix(m);
    return(det);
}

void CoFactor(double **a,int n,double **b)
{
    int i,j,m,z,y,x;
    double det;

    Matrix c = createMatrix(n-1,n-1);

    for (j=0;j<n;j++)
    {
        for (i=0;i<n;i++)
        {

            /* Form the adjoin a_ij */
            y = 0;
            for (m=0;m<n;m++)
            {
                if (m == i)
                    continue;
                x = 0;
                for (z=0;z<n;z++)
                {
                    if (z == j)
                        continue;
                    c.matrix[y][x] = a[m][z];
                    x++;
                }
                y++;
            }
            det = determinant(c);

            /* Fill in the elements of the cofactor */
            b[i][j] = pow(-1.0,i+j+2.0) * det;
        }
    }
    freeMatrix(c);
}

Matrix inverse(Matrix a)
{
    int i, j;
    Matrix result_inverse = createMatrix(a.rowCount, a.columnCount);
    Matrix adj = createMatrix(a.rowCount, a.columnCount);
    double det = determinant(a);
    CoFactor(a.matrix, a.rowCount, adj.matrix);

    if(a.rowCount != a.columnCount)
    {
        fprintf(stderr, "no nxn Matrix");
        exit(0);
    }

    if(det == 0)
    {
        fprintf(stderr, "cant divide by 0");
        exit(0);
    }

    for(i = 0; i < a.rowCount; i++)
    {
        for(j=0; j < a.columnCount; j++)
        {
            result_inverse.matrix[i][j] = (1/det) *  adj.matrix[i][j];
        }
    }
    freeMatrix(adj);
    return result_inverse;
}

// Mutable (result will be in d). Parameters are similar to https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm#Method
static double *thomasHelperSolve(double *a, double *b, double *c, double *d, int n)
{
    c[0] = c[0] / b[0];
    for (int i = 1; i < n-1; i++)
        c[i] = c[i] / (b[i] - a[i] * c[i-1]);

    d[0] = d[0] / b[0];
    for (int i = 1; i < n; i++)
        d[i] = (d[i] - a[i] * d[i-1]) / (b[i] - a[i] * c[i-1]);

    // Back substitution
    double *x = d;
    x[n-1] = d[n-1];
    for (int i = n-2; i >= 0; i--)
        x[i] = d[i] - c[i] * x[i+1];
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
    double *a = malloc(n * sizeof(*a));
    double *b = malloc(n * sizeof(*b));
    double *c = malloc((n-1) * sizeof(*c));
    double *d = malloc(n * sizeof(*d));

    for (int i = 1; i < n; i++)
        a[i] = m.matrix[i][i-1];
    for (int i = 0; i < n; i++)
        b[i] = m.matrix[i][i];
    for (int i = 0; i < n-1; i++)
        c[i] = m.matrix[i][i+1];
    for (int i = 0; i < n; i++)
        d[i]= r.matrix[i][0];

    double *res = thomasHelperSolve(a, b, c, d, n);
    Matrix mRes = arrayToMatrix(res, n);

    free(a);
    free(b);
    free(c);
    free(d);

    return mRes;
}

