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
Matrix createRandMatrix(int r, int c);
void printMatrix(Matrix *m);
double getElement(const Matrix *m, const int r, const int c);
Matrix multiply(Matrix *a, Matrix *b);
void getCofactor(Matrix *a,Matrix *temp, int p, int q, int n);
int getDimension(Matrix *a);
double Determinant(double **a, int n);
void adjoint(Matrix *a,  Matrix *adj);
bool invert(Matrix *a, Matrix *inverse);

#endif // BACKEND_UTILITY_H
