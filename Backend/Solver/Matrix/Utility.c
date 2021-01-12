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

Matrix ones(int r, int c)
{
    Matrix m = createMatrix(r, c);
    for (int i = 0; i < m->rowSize; i++)
    {
        for (int j = 0; j < m->columnSize; j++)
        {
            m->matrix[i][j] = 1;
        }
    }

    return m;
}

Matrix identity(int n);
{
    Matrix result = createMatrix(n,n);
    for(int i = 0; i < n; i++)
    {
        result.matrix[n][n] = 1;
    }
    return result
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

Matrix multiply(Matrix *a, Matrix *b)
{
    // check if multiplication is possible 
    if(a->columnSize != b->rowSize )
    {
        fprintf(stderr, "Error: comlumnSize of Matrix a != rowSize of Matrix b");
        exit(1);
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

// n is the dimension of a->matrix
double determinant(Matrix *a)
{
    int i, j, x, y;
    double det = 0;
    Matrix m = createMatrix(a->columnSize-1, a->rowSize-1);
    int n = a->rowSize;

    if (n < 1) 
    { /* Error */
        fprintf(stderr, "dimension is < 1");
        exit(EXIT_FAILURE);
    } 
    else if (n == 1)
    {
        det = a->matrix[0][0];
    } 
    else if (n == 2) 
    {
        det = a->matrix[0][0] * a->matrix[1][1] - a->matrix[1][0] * a->matrix[0][1];
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
                    m.matrix[i-1][y] = a->matrix[i][j];
                    y++;
                }
            }
            det += pow(-1.0,1.0+x+1.0) * a->matrix[0][x] * determinant(&m);
        }
    }
    freeMatrix(&m);
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
                    c.matrix[y][x] = a[m][z];
                    x++;
                }
                y++;
            }
            det = determinant(&c);

            /* Fill in the elements of the cofactor */
            b[i][j] = pow(-1.0,i+j+2.0) * det;
        }
    }
    freeMatrix(&c);
}

Matrix inverse(Matrix *a)
{
    int i, j;
    Matrix result_inverse = createMatrix(a->rowSize, a->columnSize);
    Matrix adj = createMatrix(a->rowSize, a->columnSize);
    double det = determinant(a);
    CoFactor(a->matrix, a->rowSize, adj.matrix);

    if(a->rowSize != a->columnSize)
    {
        fprintf(stderr, "no nxn Matrix");
        exit(0);
    }

    if(det == 0)
    {
        fprintf(stderr, "cant devide by 0");
        exit(0);
    }

    for(i = 0; i < a->rowSize; i++)
    {
        for(j=0; j < a->columnSize; j++)
        {
            result_inverse.matrix[i][j] = (1/det) *  adj.matrix[i][j];
        }
    }
    freeMatrix(&adj);
    return result_inverse;
}

