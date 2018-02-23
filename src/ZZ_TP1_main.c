#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"
#include "ZZ_Liste_chainee.h"

int main()
{
	matrix_t matrixA;
	int codeError;
	int i,j;
	char *fileName = "matrice1.txt";
	production_t *pTete;

	matrixA = loadMatrixFromFile(fileName,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");
		printMatrix(matrixA);

		pTete = NULL;

		for(i = 0;i < matrixA.line;i++)
		{
			for(j = 0;j < matrixA.column;j++)
			{
				insertProductionBlock(&pTete,matrixA.value[i][j],i,j,10);
			}
		}

		/*Delete the matrix */
		freeMatrix(matrixA);

		/* We can now free the linked list properly */
		freeLinkedList(pTete);

	}
	else
	{
		printf("[ERROR] : Can't create the matrix from the file : %s \n[ERROR] : Reason : ",fileName);
		
		if(codeError == 0)
		{
			printf("Unable to allocate enough space for the matrix.\n");
		}
		else
		{
			printf("the file doesn't exist in the current directory.\n");
		}
	}

	return(0);
}
