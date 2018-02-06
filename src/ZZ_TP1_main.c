#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"
#include "ZZ_Liste_chainee.h"




void main(int argc, char *argv[])
{
	float **matrix;
	int codeError;
	int n,m; /* n = line, m = column */

	matrix = loadMatrixFromFile("../matrice1.txt",&n,&m,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");
		displayMatrix(matrix,n,m);
	}
	else
	{
		printf("[ERROR] : Error during creation\n");
	}

}
