#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>

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
    temp.dimension = getDimension(&temp);

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
            printf("%f ", (**m->matrix + i * m->rowSize  + j));
        }
        printf("\n");
    }
}

double getElement(const Matrix *m, const int r, const int c){
    return (**m->matrix + r * m->rowSize + c);
}

Matrix multiply(Matrix *a, Matrix *b){
    // check if multiplication is possible 
    if(a->columnSize != b->rowSize ){
        fprintf(stderr, "Error: Incompatible sizes");
        exit(0);
    }

    int n = a->rowSize;
    Matrix result = createMatrix(n,n);

    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            result.matrix[i][j] = 0;
            for (k = 0; k < n; k++)
                result.matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
        }
    }
    return result;
}
void getCofactor(Matrix *a, int p, int q, int n)
{
    double temp[a->rowSize][a->columnSize];
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++) 
        {
            if (row != p && col != q) 
            {
                temp[i][j++] = a->matrix[row][col];

                if (j == n - 1) 
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int getDimension(Matrix *a)
{
    return sizeof(a->matrix)/a->rowSize;
}

// n is the dimension of a.matrix
int determinant(Matrix *a, int n)
{
    int Det = 0;
    if (n ==  1)
        return a->matrix[0][0];
    double sign = 1.0;
    for(int f = 0; f < n; f++)
    {
        getCofactor(a, 0, f, n);
        Det += sign * a->matrix[0][f]
             * determinant(a, n - 1);
 
        sign = -sign;
    }
    return Det;
}

Matrix adjoint(Matrix *a){
    int n = getDimension(a);
    Matrix adj = createMatrix(a->rowSize, a->columnSize);
    Matrix temp = createMatrix(a->rowSize, a->columnSize);
    if (n == 1) 
    { 
        adj.matrix[0][0] = 1; 
        return adj; 
    } 
    int sign = 1;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            getCofactor(a, i, j, n); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj.matrix[j][i] = (sign)*(determinant(&temp, n-1)); 
        }
    }
    return adj; 

}
// n is the dimension of a.matrix
Matrix invert(Matrix *a){
    int n = getDimension(a);
    int det = determinant(a, n);
    if (det == 0) 
    { 
        fprintf(stderr,"Singular matrix"); 
        exit(EXIT_FAILURE); 
    } 
    Matrix inverse = createMatrix(a->rowSize,a->columnSize);
    Matrix adj = adjoint(a);

    for (int i=0; i<n; i++) 
        for (int j=0; j<n; j++) 
            inverse.matrix[i][j] = adj.matrix[i][j]/ (float) det ; 

    return inverse;
}
