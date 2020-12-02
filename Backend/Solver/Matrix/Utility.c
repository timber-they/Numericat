#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    int rowSize;
    int columnSize;
    double **ptr = (double**)matrix;
} Matrix;

double GetRandomNumber(double minimum, double maximum)
{ 
    Random random = new Random();
    return random.NextDouble() * (maximum - minimum) + minimum;
}

void randomize(Matrix *m){
    int i,j;
    for(i = 0; i < m->rowSize ; i++){
        for(j = 0; j < m->columnSize; j++){
            m->matrix[i][j] = GetRandomNumber(0,10) % 5000;
        }
    }
}

Matrix createMatrix(int r, int c){
    Matrix temp = {r, c, calloc(r, sizeof(double *))};

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
            printf("%d ", *(m->matrix + i*m->rowSize  + j));
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

    double r = a->rowSize;
    double c = b->columnSize;
    Matrix result = createMatrix(r,c);

    //multiply part
    int i,j;
    for(i = 0; i < r ; i++){
        for(j = 0; j < c; j++){
            long double sum = 0;
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

Matrix determinant(Matrix *a)
{
    float det, ratio;
     for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = a.matrix[j][i]/a.matrix[i][i];
                for(k = 0; k < n; k++){
                    a.matrix[j][k] -= ratio * a.matrix[i][k];
                }
            }
        }
    }
    det = 1; //storage for determinant
    for(i = 0; i < n; i++)
        det *= a.matrix[i][i];
    printf("Det is: %.2f\n\n", det);
    return det;
}


Matrix invert(Matrix *a){
    for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++)
        {
            a.matrix[i][j] = ((mat[(j+1)%3][(i+1)%3] * 
                               mat[(j+2)%3][(i+2)%3]) - 
                              (mat[(j+1)%3][(i+2)%3] * 
                               mat[(j+2)%3][(i+1)%3]))/ 
                               determinant(a));
		
		printf("\n");
        }
	}
    return a.matrix    
}