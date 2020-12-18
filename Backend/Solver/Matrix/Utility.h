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
void getCofactor(Matrix *a, int p, int q, int n);
int getDimension(Matrix *   a);
int determinant(Matrix *a, int n);
Matrix adjoint(Matrix *a);
Matrix invert(Matrix *a);

#endif // BACKEND_UTILITY_H
