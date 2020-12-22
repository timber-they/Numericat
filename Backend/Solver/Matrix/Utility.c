#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

double GetRandomNumber(double minimum, double maximum)
{ 
    return (int) drand48() * (maximum - minimum) + minimum;
}   

void randomize(Matrix *m){
    int i,j;
    for(i = 0; i < m->rowSize ; i++){
        for(j = 0; j < m->columnSize; j++){
            m->matrix[i][j] = (double)rand()/(double)(RAND_MAX/10);
        }
    }
}

Matrix createMatrix(int r, int c){
    Matrix temp = {r, c, calloc(r, sizeof(double *))};
    temp.rowSize = r;
    temp.columnSize = c;
    temp.dimension = r;

    if (temp.matrix == NULL) {
        fprintf(stderr, "Empty Matrix not allowed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < r; i++) {
        temp.matrix[i] = calloc(c, sizeof temp.matrix[i][0]);

        if (temp.matrix[i] == NULL) {
            fprintf(stderr, "Empty Matrix Element not allowed\n");
        exit(EXIT_FAILURE);
        }
    }

    return temp;
}

Matrix createRandMatrix(int r, int c){
    Matrix temp = createMatrix(r,c);
    randomize(&temp);
    return temp;
}

void printMatrix(Matrix *m){

    int i,j;
    for(i = 0; i < m->rowSize ; i++){
        for(j = 0; j < m->columnSize; j++){
            printf("%f  ", m->matrix[i][j]);
        }
        printf("\n");
    }
}

double getElement(const Matrix *m, const int r, const int c){
    return (**m->matrix + r * m->rowSize + c);
}

Matrix multiply(Matrix *a, Matrix *b){
    // check if multiplication is possible 
    if(a->columnSize != b->rowSize )
    {
        fprintf(stderr, "Error: Incompatible sizes");
        exit(0);
    }

    int n = a->rowSize;
    Matrix result = createMatrix(n,n);

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
    int i,j,j1,j2;
    double det = 0;
    double **m = NULL;

    if (n < 1) 
    { /* Error */
        fprintf(stderr, "dimension is < 1");
        exit(1);
    } 
    else if (n == 1)
    { /* Shouldn't get used */
        det = a[0][0];
    } 
    else if (n == 2) 
    {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];    
    } 
    else 
        {
        det = 0;
        for (j1 = 0; j1 < n ; j1++) {
            m = malloc((n-1)*sizeof(double *));
            for (i=0;i<n-1;i++)
                m[i] = malloc((n-1)*sizeof(double));
            for (i=1;i<n;i++) 
            {
                j2 = 0;
                for (j=0;j<n;j++) {
                    if (j == j1)
                        continue;
                m[i-1][j2] = a[i][j];
                j2++;
            }
            }
        det += pow(-1.0,1.0+j1+1.0) * a[0][j1] * determinant(m,n-1);
        for (i=0;i<n-1;i++)
        free(m[i]);
        free(m);
      }
   }
   return(det);
}

void CoFactor(double **a,int n,double **b)
{
   int i,j,ii,jj,i1,j1;
   double det;
   double **c;

   c = malloc((n-1)*sizeof(double *));
   for (i=0;i<n-1;i++)
     c[i] = malloc((n-1)*sizeof(double));

   for (j=0;j<n;j++) {
      for (i=0;i<n;i++) {

         /* Form the adjoint a_ij */
         i1 = 0;
         for (ii=0;ii<n;ii++) {
            if (ii == i)
               continue;
            j1 = 0;
            for (jj=0;jj<n;jj++) {
               if (jj == j)
                  continue;
               c[i1][j1] = a[ii][jj];
               j1++;
            }
            i1++;
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
    Matrix Adj = createMatrix(a->rowSize, a->columnSize);
    double det = determinant(a->matrix, a->rowSize);
    CoFactor(a->matrix, a->rowSize, Adj.matrix);     

    for(i = 0; i < a->rowSize; i++)
    {
        for(j=0; j < a->columnSize; j++)
        {
            Inverse.matrix[i][j] = (1/det) *  Adj.matrix[i][j];
        }
    }
    return Inverse;
}
