/* ################################################## */
/* file's name : ZZ_TP1_main.c						  */
/*												      */
/* Author : Mathieu Boutin & Jérémy Morceaux		  */
/* Date : March 2018								  */
/*													  */
/* This file contains main source for the TP		  */
/*													  */
/* Desc : This file create a matrix from a file, get  */
/*		  the K-th smallest value in the matrix,      */
/*		  remove a particular factory, and eventually */
/*	      stores it in a file						  */
/* ################################################## */

#include <stdlib.h>
#include <stdio.h>

#include "ZZ_matrix.h"
#include "ZZ_linked_list.h"

#define NORMAL  "\x1B[0m"
#define ROUGE  "\x1B[31m"
#define VERT  "\x1B[32m"
#define JAUNE  "\x1B[33m"
#define BLEU  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define BLANC  "\x1B[37m"


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
		factoryIndex = atoi(argv[3]);

		printf("%sI/ Loading the matrix from the file %s.%s\n",VERT,argv[1],NORMAL);

		matrixA = loadMatrixFromFile(argv[1],&codeError);

		/* Start with the creation of the matrix, if we manage to load it */
		if(codeError == 1)
		{
			printMatrix(matrixA);
			pTete = NULL;

			printf("%sII/ Creating the linked list.%s\n",VERT,NORMAL);

			if(K > 0)
			{			
				if(matrixA.line > 0 && matrixA.column > 0) /* we are dealing with a non-null matrix */
				{
					

					if( K > matrixA.line * matrixA.column )
					{	
						fprintf(stdout,"%s[WARNING] K > number of data in the matrix.%s\n",JAUNE,NORMAL);
					}

					
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

					/* Delete the matrix, we don't need it anymore */
					freeMatrix(matrixA);

					printf("%sIII/ Displaying the result.%s\n",VERT,NORMAL);
					writeLinkedListToFile(stdout,pTete);

					printf("%sIV/ Removing the factory with the indice %d%s\n",VERT,factoryIndex,NORMAL);

					if(!(factoryIndex > matrixA.line ||  factoryIndex < 0))
					{
						/* Removing all the block having factoryIndex as value */
						removeFactory(&pTete,factoryIndex);
					}	
					else
					{
						fprintf(stdout,"%s[WARNING] You're attempting to remove a non-existing factory.%s\n",JAUNE,NORMAL);
					}
				
					
					/* Print the new linked list */
					writeLinkedListToFile(stdout,pTete);


					printf("%sV/ Saving the linked list in the file data.%s\n",VERT,NORMAL);
					file = fopen("data","w");

					if(file != NULL)
					{
						/* In order to re-use this linked list, we save it in a file */
						writeLinkedListToFile(file,pTete);
						fclose(file);
					}
					else
					{
						fprintf(stdout,"%s[WARNING] Unable to write the linked list to the file data.%s\n",JAUNE,NORMAL);
					}

					/* We can finally free the linked list properly */
					freeLinkedList(pTete);
				}
				else
				{
					fprintf(stdout,"%s[WARNING] Null Matrix. There is no data to work with.%s\n",JAUNE,NORMAL);
				}
			}
			else
			{
				fprintf(stdout,"%s[ERROR] K is negative. No data will be shown%s\n",ROUGE,NORMAL);
			}			
		}
		else
		{
			fprintf(stderr,"%s[ERROR]%s Can't create the matrix from the file : %s \n%s[ERROR]%s Reason : ",ROUGE,NORMAL,argv[1],ROUGE,NORMAL);
		
			if(codeError == 0)
			{
				fprintf(stderr,"Unable to allocate enough space for the matrix.\n");
			}
			else
			{
				fprintf(stderr,"The file doesn't exist.\n");
			}
		}
	}
	else
	{
		fprintf(stderr,"%s[ERROR] Too few/much arguments.%s\n",ROUGE,NORMAL);
		printf("[INFO] Usage : %s matrixFile A B \nWhere : \nmatrixFile - It's the name of the file where the matrix is stored. It needs to be in directory where you start the program \nA - It's the number of smallest value you want to keep from the matrix\nB - It's the indice of the factory you want to remove from the linked list containing the x smallest value \n",argv[0]);
		
	}
	return(0);
}
