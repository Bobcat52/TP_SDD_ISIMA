#include <stdio.h>
#include <stdlib.h>

typedef struct matrix
{
	float **value;
	int line;
	int column;

} matrix_t;

matrix_t loadMatrixFromFile(char* fileName,int *errorCode);
void displayMatrix(matrix_t matrix);
matrix_t multiply(matrix_t A, matrix_t B,int *errorCode);
matrix_t zeroMatrix(int line,int column,int *errorCode);
