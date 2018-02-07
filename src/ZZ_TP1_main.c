#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"

void main(int argc, char *argv[])
{
	matrix_t matrix;
	int codeError;

	char *fileName = "matrice1.txt";

	matrix = loadMatrixFromFile(fileName,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");
		displayMatrix(matrix);
		printf("Le nombre de ligne de la matrice est : %d\n",matrix.line);
		printf("Le nombre de colone de la matrice est : %d\n",matrix.column);
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
