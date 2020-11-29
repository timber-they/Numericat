#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    int rowSize;
    int columnSize;
    long int** matrix;
} Matrix;

void randomize(Matrix *m){
    int i,j;
    for(i = 0; i < m->rowSize ; i++){
        for(j = 0; j < m->columnSize; j++){
            m->matrix[i][j] = rand() % 5000;
        }
    }
}


Matrix createMatrix(int r, int c){
    Matrix temp = {r, c, calloc(r, sizeof(long int *))};

    if (temp.matrix == NULL) {
        fprintf(stderr, "Empty Matrix not allowed\n");
        return 1;
    }

    for (int i = 0; i < r; i++) {
        temp.matrix[i] = calloc(c, sizeof temp.matrix[i][0]);

        if (temp.matrix[i] == NULL) {
            fprintf(stderr, "Empty Matrix Element not allowed\n");
        return 1;
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
            printf("%li ", *(m->matrix + i*m->rowSize  + j));
        }
        printf("\n");
    }
}

Matrix multiply(Matrix *a, Matrix *b){
    // check if multiplication is possible 
    if(a->columnSize != b->rowSize ){
        fprintf(stderr, "Error: Incompatible sizes");
        exit(0);
    }

    int r = a->rowSize;
    int c = b->columnSize;
    Matrix result = createMatrix(r,c);

    //multiply part
    int i,j;
    for(i = 0; i < r ; i++){
        for(j = 0; j < c; j++){
            long int sum = 0;
            int k;
            for(k = 0; k < a->columnSize; k++){
                //sum += a[i][k] * b[k][j]
                sum = sum + (*(a->matrix + i*a->rowSize  + k)**(b->matrix + k*b->rowSize  + j));
            }
            // not optimal at the moment
            *(result.matrix+ i*r  + j) = sum;
        }
    }
    return result;
}

Matrix invert(Matrix *a){
    // TODO implement
}