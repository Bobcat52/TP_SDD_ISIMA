#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"
#include "ZZ_Liste_chainee.h"

void main(int argc, char *argv[])
{
	matrix_t matrixA;

	int codeError;

	char *fileName = "matrice1.txt";
	matrixA = loadMatrixFromFile(fileName,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");

	
		displayMatrix(matrixA);

		tableau_t *pTete;
		pTete = NULL;

		int i,j;
		for(i =0;i < matrixA.line;i++)
		{
			for(j =0;j < matrixA.column;j++)
			{
				insertBlock(&pTete,matrixA.value[i][j],i,j,10);
			}
		}
		afficherListeChaine(pTete);
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
