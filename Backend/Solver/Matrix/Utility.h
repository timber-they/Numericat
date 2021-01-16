#include <stdbool.h>

#ifndef BACKEND_UTILITY_H
#define BACKEND_UTILITY_H

typedef struct Matrix {
    int rowCount;
    int columnCount;
    double **matrix;
    int dimension;
} Matrix;

Matrix createMatrix(int r, int c);
void freeMatrix(Matrix a);
Matrix ones(int r, int c);
Matrix identity(int n);
void printMatrix(Matrix m);
double getElement(const Matrix m, const int r, const int c);
Matrix multiply(Matrix a, Matrix b);
Matrix factor(Matrix a, double f);
Matrix sum(Matrix a, Matrix b);
Matrix subtract(Matrix a, Matrix b);
Matrix arrayToMatrix(double *array, int n);
double *matrixToArray(Matrix m);
double determinant(Matrix a);
void CoFactor(double **a,int n,double **b);
Matrix inverse(Matrix a);
/**
 * Efficiently solves a linear system mx=b with a three-diagonal matrix
 * @param m the matrix
 * @param b the supposed result result
 * @return x (the solution)
 */
Matrix thomasSolve(Matrix m, Matrix b);

#endif // BACKEND_UTILITY_H
