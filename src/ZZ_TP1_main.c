#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"

void main(int argc, char *argv[])
{
	float **matrix;
	int codeError;
	int n,m; /* n = line, m = column */
	char *fileName = "matrice1.txt";

	matrix = loadMatrixFromFile(fileName,&n,&m,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");
		displayMatrix(matrix,n,m);
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
