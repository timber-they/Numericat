#include "Utility.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void freeMatrix(Matrix *a)
{
    for (int i = 0; i < a->dimension; i++)
        free(a->matrix[i]);
    free(a->matrix);
}

Matrix createMatrix(int r, int c) 
{
    Matrix result = {r, c, calloc(r, sizeof(double *))};
    result.rowSize = r;
    result.columnSize = c;
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

void printMatrix(Matrix *m) 
{
    int i,j;
    for(i = 0; i < m->rowSize ; i++)
    {
        for(j = 0; j < m->columnSize; j++)
        {
            printf("%f  ", m->matrix[i][j]);
        }
        printf("\n");
    }
}

double getElement(const Matrix *m, const int r, const int c) 
{
    return **m->matrix + r * m->rowSize + c;
}

Matrix multiply(Matrix *a, Matrix *b)
{
    // check if multiplication is possible 
    if(a->columnSize != b->rowSize )
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

// n is the dimension of a.matrix
double determinant(double **a, int n)
{
    int i, j, x, y;
    double det = 0;
    double **m = NULL;

    if (n < 1) 
    { /* Error */
        fprintf(stderr, "dimension is < 1");
        exit(EXIT_FAILURE);
    } 
    else if (n == 1)
    { /* Shouldn't not get 1x1 Matrix */
        det = a[0][0];
    } 
    else if (n == 2) 
    {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];    
    } 
    else 
    {
        det = 0;
        for (x = 0; x < n ; x++) 
        {
            m = malloc((n-1)*sizeof(double *));
            for (i=0;i<n-1;i++)
            {
                m[i] = malloc((n-1)*sizeof(double));
            }
            for (i=1;i<n;i++) 
            {
                y = 0;
                for (j=0;j<n;j++) 
                {
                    if (j == x)
                    {
                        continue;
                    }
                    m[i-1][y] = a[i][j];
                    y++;
                }
            }
            det += pow(-1.0,1.0+x+1.0) * a[0][x] * determinant(m,n-1);
            for (i=0;i<n-1;i++)
                free(m[i]);
            free(m);
        }
    }
    return(det);
}

void CoFactor(double **a,int n,double **b)
{
    int i,j,m,z,y,x;
    double det;
    double **c;

    c = malloc((n-1)*sizeof(double *));
    for (i=0;i<n-1;i++)
        c[i] = malloc((n-1)*sizeof(double));

    for (j=0;j<n;j++) 
    {
        for (i=0;i<n;i++) 
        {

            /* Form the adjoint a_ij */
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
                    c[y][x] = a[m][z];
                    x++;
                }
                y++;
            }
            det = determinant(c,n-1);

            /* Fill in the elements of the cofactor */
            b[i][j] = pow(-1.0,i+j+2.0) * det;
        }
    }
    for (i=0;i<n-1;i++)
        free(c[i]);
    free(c);
}

// only works for n x n at the moment
Matrix inverse(Matrix *a)
{
    int i, j;
    Matrix Inverse = createMatrix(a->rowSize, a->columnSize);
    Matrix adj = createMatrix(a->rowSize, a->columnSize);
    double det = determinant(a->matrix, a->rowSize);
    CoFactor(a->matrix, a->rowSize, adj.matrix);     

    for(i = 0; i < a->rowSize; i++)
    {
        for(j=0; j < a->columnSize; j++)
        {
            Inverse.matrix[i][j] = (1/det) *  adj.matrix[i][j];
        }
    }
    freeMatrix(&adj);
    return Inverse;
}

