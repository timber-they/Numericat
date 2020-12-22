#include "Utility.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double GetRandomNumber(double minimum, double maximum) 
{
    return (int)drand48() * (maximum - minimum) + minimum;
}

void randomize(Matrix *m) 
{
    for (int i = 0; i < m->rowSize; i++) 
    {
        for (int j = 0; j < m->columnSize; j++) 
        {
            m->matrix[i][j] = (double)rand() / (double)(RAND_MAX / 10);
        }
    }
}

Matrix createMatrix(int r, int c) {
    Matrix temp = {r, c, calloc(r, sizeof(double *))};
    temp.rowSize = r;
    temp.columnSize = c;
    temp.dimension = getDimension(&temp);

    if (temp.matrix == NULL) 
    {
        fprintf(stderr, "Empty Matrix not allowed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < r; i++) 
    {
        temp.matrix[i] = calloc(c, sizeof temp.matrix[i][0]);

        if (temp.matrix[i] == NULL) 
        {
            fprintf(stderr, "Empty Matrix Element not allowed\n");
            exit(EXIT_FAILURE);
        }
    }

    return temp;
}

Matrix createRandMatrix(int r, int c) 
{
    Matrix temp = createMatrix(r, c);
    randomize(&temp);
    return temp;
}

void printMatrix(Matrix *m) 
{

    int i, j;
    for (i = 0; i < m->rowSize; i++) 
    {
        for (j = 0; j < m->columnSize; j++) 
        {
            printf("%f ", (**m->matrix + i * m->rowSize + j));
        }
        printf("\n");
    }
}

double getElement(const Matrix *m, const int r, const int c) 
{
    return (**m->matrix + r * m->rowSize + c);
}

Matrix multiply(Matrix *a, Matrix *b) 
{
    // Check if multiplication is possible
    if (a->columnSize != b->rowSize) 
    {
        fprintf(stderr, "Error: Incompatible sizes");
        exit(0);
    }

    int n = a->rowSize;
    Matrix result = createMatrix(n, n);

    int i, j, k;
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            result.matrix[i][j] = 0;
            for (k = 0; k < n; k++)
                result.matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
        }
    }
    return result;
}

int getDimension(Matrix *a) 
{ 
    // TODO: This doesn't make sense, as it only returns the size of a pointer
    int res = sizeof(a->matrix) / a->rowSize; 
    fprintf(stderr, "Dimension is: %d (%ld / %d)\n", res, sizeof(a->matrix), a->rowSize);
    return res;
}

void getCofactor(Matrix *a, Matrix *temp, int p, int q, int n) 
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) 
    {
        for (int col = 0; col < n; col++) 
        {
            if (row == p || col == q)
                continue;
            temp->matrix[i][j++] = a->matrix[row][col];

            if (j == n - 1) 
            {
                j = 0;
                i++;
            }
        }
    }
}

// n is the dimension of a.matrix
double determinant(double **a, int n) 
{
    int i, j, j1, j2;
    double det = 0;
    double **m = NULL;

    if (n < 1) 
    { 
        // Error
        fprintf(stderr, "dimension is < 1");
        exit(EXIT_FAILURE);
    } 
    else if (n == 1) 
    { 
        // Shouldn't get used
        det = a[0][0];
    } 
    else if (n == 2) 
    {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    } 
    else 
    {
        det = 0;
        for (j1 = 0; j1 < n; j1++) 
        {
            m = malloc((n - 1) * sizeof(*m));
            for (i = 0; i < n - 1; i++)
                m[i] = malloc((n - 1) * sizeof(*m[i]));
            for (i = 1; i < n; i++) 
            {
                j2 = 0;
                for (j = 0; j < n; j++) 
                {
                    if (j == j1)
                        continue;
                    m[i - 1][j2] = a[i][j];
                    j2++;
                }
            }
            det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * determinant(m, n - 1);
            for (i = 0; i < n - 1; i++)
                free(m[i]);
            free(m);
        }
    }
    return (det);
}

void adjoint(Matrix *a, Matrix *adj) 
{
    int n = getDimension(a);
    Matrix temp = createMatrix(a->rowSize, a->columnSize);
    if (n == 1) 
    {
        adj->matrix[0][0] = 1;
        return;
    }
    int sign = 1;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            getCofactor(a, &temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj->matrix[j][i] = (sign) * (determinant(temp.matrix, n - 1));
        }
    }
}

// N is the dimension of a.matrix
bool invert(Matrix *a, Matrix *inverse) 
{
    int N = a->dimension;
    Matrix adj = createMatrix(a->columnSize, a->rowSize);
    adjoint(a, &adj);
    int det = (float)determinant(a->matrix, N);
    if (det == 0) 
    {
        fprintf(stderr, "determinant is 0");
        return false;
    }
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            inverse->matrix[i][j] = adj.matrix[i][j] / det;
        }
    }
    return true;
}
