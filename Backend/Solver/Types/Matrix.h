#include "Complex.h"

#ifndef BACKEND_UTILITY_H
#define BACKEND_UTILITY_H

typedef struct Matrix {
    int rowCount;
    int columnCount;
    Complex **matrix; // Row x Column
    int dimension;
} Matrix;

Matrix createMatrix(int r, int c);
void freeMatrix(Matrix a);
Matrix ones(int r, int c);
Matrix identity(int n);
void printMatrix(Matrix m);
Complex getElement(const Matrix m, const int r, const int c);
Matrix multiply(Matrix a, Matrix b);
/**
 * Assumes a is tridiagonal
 */
Matrix multiplyTri(Matrix a, Matrix b);
// TODO: Not only support nxn
Matrix factor(Matrix a, Complex f);
/**
 * Result will be stored in a and assumes a is tridigaonal
 */
Matrix factorIpTri(Matrix a, Complex f);
Matrix sum(Matrix a, Matrix b);
/**
 * Result will be stored in a. Assumes a and b are tridiagonal
 */
Matrix sumIpTri(Matrix a, Matrix b);
/**
 * Assumes a and b are tridiagonal
 */
Matrix sumTri(Matrix a, Matrix b);
Matrix subtract(Matrix a, Matrix b);
/**
 * Assumes a and b are tridiagonal
 */
Matrix subtractTri(Matrix a, Matrix b);
Matrix arrayToMatrix(Complex *array, int n);
Complex *matrixToArray(Matrix m);
/**
 * Efficiently solves a linear system mx=b with a three-diagonal matrix
 * @param m the matrix
 * @param b the supposed result result
 * @return x (the solution)
 */
Matrix thomasSolve(Matrix m, Matrix b);

#endif // BACKEND_UTILITY_H
