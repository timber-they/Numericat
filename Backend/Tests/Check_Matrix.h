#include "../Solver/Matrix/Utility.h"

typedef struct Matrix {
    int rowSize;
    int columnSize;
    double **matrix;
    int dimension;
}Matrix;

START_TEST(test_determinant)
{
    Matrix tmp = createMatrix(2,2);
    tmp.matrix[0][0] = 2;
    tmp.matrix[0][1] = 2;
    tmp.matrix[1][0] = 2;
    tmp.matrix[1][1] = 2;
    int dimension = getDimension(&tmp);
    int det = determinant(&tmp, dimension);
    ck_assert(determinant == det);
}
END_TEST

START_TEST(test_Inverse)
{
    Matrix temp = createMatrix(2,2);
    temp.matrix[0][0] = 3;
    temp.matrix[0][1] = 2;
    temp.matrix[1][0] = 2;
    temp.matrix[1][1] = 3;
    Matrix Inverse = invert(&temp);
    ck_assert(Inverse.matrix[0][0] == 0.6);
    ck_assert(Inverse.matrix[1][0] == -0.4);
    ck_assert(Inverse.matrix[0][1] == -0.4);
    ck_assert(Inverse.matrix[1][1] == 0.6);
}
END_TEST

START_TEST(test_multiply)
{
    Matrix Matrix_1 = createMatrix(2,2);
    Matrix_1.matrix[0][0] = 2;
    Matrix_1.matrix[0][1] = 2;
    Matrix_1.matrix[1][0] = 2;
    Matrix_1.matrix[1][1] = 2;
    Matrix Matrix_2 = createMatrix(2,2);
    Matrix_2.matrix[0][0] = 2;
    Matrix_2.matrix[0][1] = 2;
    Matrix_2.matrix[1][0] = 2;
    Matrix_2.matrix[1][1] = 2;
    Matrix multiplied = multiply(&Matrix_1, &Matrix_2);
    ck_assert(multiplied.matrix[0][0] == 8);
    ck_assert(multiplied.matrix[1][0] == 8);
    ck_assert(multiplied.matrix[0][1] == 8);
    ck_assert(multiplied.matrix[1][1] == 8);
}
END_TEST
