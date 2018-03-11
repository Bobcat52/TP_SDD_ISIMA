/* ################################################# */
/* file's name : ZZ_Matrix.c						 */
/*												     */
/* Author : Mathieu Boutin & Jérémy Morceaux		 */
/* Date : March 2018								 */
/*													 */
/* This file contains source from ZZ_matrix.h 		 */
/* Desc : It allows the user to manipulate a matrix  */ 
/* (loading, printing, etc ...)						 */
/* ################################################# */

#include <stdlib.h>
#include <stdio.h>
#include "ZZ_matrix.h"

/* ------------------------------------------------------------------------------------------------- */
/* loadMatrixFromFile  					Create a matrix from a file 								 */
/* 																									 */
/* Inputs: 	- fileName is the name of the file where it is written some data of production			 */
/*			  of a company 																			 */
/*          - errorCode is a pointer of an error message :											 */
/*					-1 = problem while openin file												     */
/* 					 1 = no problem																	 */
/* 					 0 = problem during allocation													 */	
/*																									 */
/* Output:  - Return a matrix created from a file         											 */
/* ------------------------------------------------------------------------------------------------- */
matrix_t loadMatrixFromFile(char* fileName,int *errorCode)
{
	
	/* We create a matrix_t to store its value, column and line */
	matrix_t 	matrix;
	int 		issue;
	FILE* 		file = fopen(fileName,"r"); /* creation of a flow */

	/* Initialization */
	matrix.value = NULL;
	*errorCode = -1;

	if(file!= NULL) /* We make sure, we actually opened the file */
	{
		int i = 0,
			j = 0;

		*errorCode = 0;

		/* We can get dimension of the matrice n*m through the first line*/
		fscanf(file,"%d %d",&matrix.line,&matrix.column);		

		matrix.value = malloc(matrix.line * sizeof(float*)); /* First, we create lines of the matrix */

		issue = 0;

		/* No error during first allocation */
		if (matrix.value != NULL)
		{

			for(i=0; i< matrix.line; i++)
			{
				if(issue == 0) /* So far so good */
				{

					matrix.value[i]= malloc(matrix.column * sizeof(float));	/* Now, we create columns of the matrix */

				}

				if(issue == 0 && matrix.value[i]==NULL) /* error during allocation, aborting */
				{

					issue = 1;
					freeMatrix(matrix); /* we had an issue during allocation, we free the matrix */

				}
			}

		}
		else /* error during allocation */
		{
			freeMatrix(matrix);
		}

		/* Then, we get the values of the matrix */
		*errorCode = 1;


		for(i = 0;i < matrix.line;i++)	/* we go through lines of the matrix */
		{

			for(j=0;j < matrix.column;j++)		/* we go through columns of the matrix */
			{

				fscanf(file,"%f",&matrix.value[i][j]); /* get the data from the file */

			}

		}

		fclose(file); /* Don't forget to close the flow */
	}
	else
	{
		*errorCode = -1; /* We had a problem while opening the file*/
	}


	return(matrix);
}

/* ------------------------------------------------------------------------------------------------- */
/* freeMatrix  			Free the matrix even if it is badly created.  								 */
/* 																									 */
/* Input: 	- matrix is a struct that stores values of the matrix and its size						 */
/*																									 */
/* ------------------------------------------------------------------------------------------------- */
void freeMatrix(matrix_t matrix)
{
	int i;

	if (matrix.value != NULL)
	{
		for(i=0; i< matrix.line; i++) /* For each line */
		{
			if(matrix.value[i] != NULL) /* We check that there is something to free */
			{

				free(matrix.value[i]); /* We free the line */
				matrix.value[i] = NULL;

			}
		}

		free(matrix.value); /* We free the main pointer */
		matrix.value = NULL;		
			
	}
	
}

/* ------------------------------------------------------------------------------------------------- */
/* printMatrix  			Display the matrix in the terminal                            			 */
/*																									 */
/* Input: 	- matrix is a struct that stores values of the matrix and its size						 */
/*      																							 */
/* ------------------------------------------------------------------------------------------------- */
void printMatrix(matrix_t matrix)
{
	int i,
		j;

	for(i = 0;i < matrix.line;i++) /* we go through lines of the matrix */
	{
		for(j=0;j < matrix.column;j++) /* we go through columns of the matrix */
		{

			printf("%f \t",matrix.value[i][j]); /* we display the value of the element in the line i and the column j */
		
		}

		printf("\n");
	}
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/* Don't look at these function, we wrote them just for fun		                                                                       */


matrix_t multiply(matrix_t A,matrix_t B,int *errorCode)
{
	int error;
	matrix_t matrixRes;
	int i,j;

	matrixRes.value = NULL;

	/* We first verify that we can't actualy do the multiplication */
	if(A.column == B.line)
	{
		/* We can perform the multiplication */
		matrixRes.line = A.line;
		matrixRes.column = B.column;

		
		matrixRes = zeroMatrix(A.line,B.column,&error);
		*errorCode = 1;

		if(error == 1)
		{
				for(i=0;i < matrixRes.line;i++)
				{
					for(j=0;j < matrixRes.column;j++)
					{
						int k=0;
						for(k=0;k < A.line;k++)
						{
							matrixRes.value[i][j] += A.value[i][k] * B.value[k][j];
						}
					}
				}
		}
		else
		{
			*errorCode = 0;
			printf("[ERROR] : Unable to allocate enough space to create a third matrix !\n");
		}


	}
	else
	{
		*errorCode = -1;
		printf("[ERROR] : Can't perform multiplication due to matrix's dimensions : (%d,%d) and (%d,%d)\n",A.line,A.column,B.line,B.column);
	}

	return(matrixRes);
}
/*
*	1 = no problem
* 0 = problem allocation
*/

matrix_t zeroMatrix(int line,int column,int *errorCode)
{
	int i, j;
	
	matrix_t matrix;
	matrix.value = NULL;
	matrix.line = line;
	matrix.column = column;

	/* We can get dimension of the matrice n*m through the first line*/
	
	*errorCode = 0;

	matrix.value = malloc(matrix.line * sizeof(float*));

	/* We ensure the allocation went well */
	if (matrix.value == NULL)
	{
		return(matrix);
	}

	/* TODO: free the memory already allocate if we encouter a problem */
	for(i=0; i< matrix.line; i++)
	{
		matrix.value[i]= malloc(matrix.column * sizeof(float));
		/* Again, we check if the allocation went well */
		if(matrix.value[i]==NULL)
		{
			return(matrix);
		}
	}
	/* Then we get the values of the matrix */
	*errorCode = 1;


	for(i = 0;i < matrix.line;i++)
	{
		for(j=0;j < matrix.column;j++)
		{
			matrix.value[i][j] = 0.0f;
		}
	}
	return(matrix);
}
