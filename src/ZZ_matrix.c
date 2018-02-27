#include <stdlib.h>
#include <stdio.h>
#include "ZZ_matrix.h"



/*-1 = problem while openin file	*/
/* 1 = no problem				*/
/* 0 = problem during allocation	*/


/* ------------------------------------------------------------------------------------------------- */
/* loadMatrixFromFile  Create a matrix from a file 													 */
/* Inputs: fileName is a pointer of a file where it is written some data of production	of a company */
/*        errorCode is a pointer of an error message												 */
/* Output: return a matrix created from a file         												 */
/* ------------------------------------------------------------------------------------------------- */

matrix_t loadMatrixFromFile(char* fileName,int *errorCode)
{
	FILE* file = fopen(fileName,"r");
	/* We create a matrix_t to store its value, column and line */
	matrix_t matrix;
	int issue;	
	matrix.value = NULL;
	*errorCode = -1;

	if(file!= NULL) /* We make sure, we actually opened the file */
	{

		/* We can get dimension of the matrice n*m through the first line*/
		int i=0, j=0;
		*errorCode = 0;

		fscanf(file,"%d %d",&matrix.line,&matrix.column);

		matrix.value = malloc(matrix.line * sizeof(float*));

		issue = 0;

		if (matrix.value != NULL)
		{
			for(i=0; i< matrix.line; i++)
			{
				if(issue == 0)
				{
					matrix.value[i]= malloc(matrix.column * sizeof(float));
				}

				if(issue == 0 && matrix.value[i]==NULL)
				{
					issue = 1;
					freeMatrix(matrix);
				}
			}
		}
		else
		{
			freeMatrix(matrix);
		}

		/* We then, get the values of the matrix */
		*errorCode = 1;


		for(i = 0;i < matrix.line;i++)
		{
			for(j=0;j < matrix.column;j++)
			{
				fscanf(file,"%f",&matrix.value[i][j]);
			}
		}

		fclose(file);
	}
	else
	{
		*errorCode = -1; /* We had a problem while opening the file*/
	}


	return(matrix);
}

/* ------------------------------------------------------------------------------------------------- */
/*																									 */
/* freeMatrix  Free the memory of the matrix even if it is badly created.                            */
/* Inputs: matrix is a list of list where is stored some data of production of a company	         */
/*      																							 */
/* ------------------------------------------------------------------------------------------------- */

void freeMatrix(matrix_t matrix)
{
	int i;

	if (matrix.value != NULL)
	{
		for(i=0; i< matrix.line; i++)
		{
			if(matrix.value[i] != NULL)
			{
				free(matrix.value[i]);
				matrix.value[i] = NULL;
			}
		}
		free(matrix.value);
		matrix.value = NULL;		
			
	}
	
}

/* ------------------------------------------------------------------------------------------------- */
/*																									 */
/* printMatrix  Display the matrix in the terminal                            						 */
/* Inputs: matrix is a list of list where is stored some data of production of a company	         */
/*      																							 */
/* ------------------------------------------------------------------------------------------------- */



void printMatrix(matrix_t matrix)
{
	int i,j;

	for(i = 0;i < matrix.line;i++)
	{
		for(j=0;j < matrix.column;j++)
		{
			printf("%f ",matrix.value[i][j]);
		}
		printf("\n");
	}
}


/*-------------------------------------------------------------------------------------------------------------------------------------*/
/* Don't look at these function, we wrote them to help us                                                                              */


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
