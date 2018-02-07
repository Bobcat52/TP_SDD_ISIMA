#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"

void main(int argc, char *argv[])
{
	matrix_t matrixA;
	matrix_t matrixB;
	int codeError;

	char *fileName = "matrice1.txt";
	matrixA = loadMatrixFromFile(fileName,&codeError);

	char *fileName2 = "matrice2.txt";
	matrixB = loadMatrixFromFile(fileName2,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");

		matrix_t matrixC;
		matrixC = multiply(matrixA,matrixB,&codeError);
		displayMatrix(matrixC);


	}
	else
	{
		printf("[ERROR] : Can't create the matrix from the file : %s \n[ERROR] : Reason : ",fileName);
		if(codeError == 0)
		{
			printf("Unable to allocate enough space for the matrix\n");
		}
		else
		{
			printf("the file doesn't exist\n");
		}
	}

}
