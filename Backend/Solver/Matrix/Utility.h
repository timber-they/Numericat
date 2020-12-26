#include <stdbool.h>

#ifndef BACKEND_UTILITY_H
#define BACKEND_UTILITY_H

typedef struct Matrix {
    int rowSize;
    int columnSize;
    double **matrix;
    int dimension;
} Matrix;

double GetRandomNumber(double minimum, double maximum);
void randomize(Matrix *m);
Matrix createMatrix(int r, int c);
void freeMatrix(Matrix *a);
Matrix createRandMatrix(int r, int c);
void printMatrix(Matrix *m);
double getElement(const Matrix *m, const int r, const int c);
Matrix multiply(Matrix *a, Matrix *b);
double determinant(double **a, int n);
void CoFactor(double **a,int n,double **b);
Matrix inverse(Matrix *a);

#endif // BACKEND_UTILITY_H
