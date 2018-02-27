#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"
#include "ZZ_Liste_chainee.h"

int main(int argc, char * argv[])
{
	if(argc == 4) /* if we have enough arguments */
	{	
		/* Declare variables */
		matrix_t matrixA;
		int codeError;
		int i,j;
		int K,factoryIndex;
		production_t *pTete;
		FILE* file;

		/* Load some of them thanks to arguments of the program */
		K = atoi(argv[2]);
		factoryIndex = atoi(argv[2]); 
		matrixA = loadMatrixFromFile(argv[1],&codeError);

		/* Start with the creation of the matrix, if we manage to load it */
		if(codeError == 1)
		{
			/* printMatrix(matrixA);*/ /* You can uncomment this to see the matrix in the terminal  */
			pTete = NULL;

			for(i = 0;i < matrixA.line;i++)
			{
				for(j = 0;j < matrixA.column;j++)
				{
					if( K != 0) /* there is no use in allocating block when we don't need to sort any value */
					{
						insertProductionBlock(&pTete,matrixA.value[i][j],i,j,K);
					}				
				}
			}

			/*Delete the matrix */
			freeMatrix(matrixA);

			writeLinkedListToFile(stdout,pTete);
			printf("After removing the factory with the indice %d\n",factoryIndex);

			removeFactory(&pTete,factoryIndex);
			writeLinkedListToFile(stdout,pTete);


			file = fopen("data","w");

			if(file != NULL)
			{
				/* In order to re-use this linked list, we save it in a file */
				writeLinkedListToFile(file,pTete);
				fclose(file);
			}
			/* We can finally free the linked list properly */
			freeLinkedList(pTete);

		}
		else
		{
			fprintf(stderr,"[ERROR] Can't create the matrix from the file : %s \n[ERROR] : Reason : ",argv[1]);
		
			if(codeError == 0)
			{
				fprintf(stderr,"Unable to allocate enough space for the matrix.\n");
			}
			else
			{
				fprintf(stderr,"The file doesn't exist in the current directory.\n");
			}
		}
	}
	else
	{
		fprintf(stderr,"[ERROR] Too few/much arguments.\n");
		printf("[INFO] Usage : %s matrixFile A B \nWhere : \nmatrixFile - It's the name of the file where the matrix is stored. It needs to be in directory where you start the program \nA - It's the number of smallest value you want to keep from the matrix\nB - It's the indice of the factory you want to remove from the linked list containing the x smallest value \n",argv[0]);
		
	}
	return(0);
}
