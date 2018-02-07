#include <stdlib.h>
#include <stdio.h>
#include "ZZ_matrix.h"

/*
void main()
{
	float **matrix;
	int codeError;
	int n,m;

	matrix = loadMatrixFromFile("matrice1.txt",&n,&m,&codeError);

	if(codeError == 1)
	{
		printf("Matrix successfully created !\n");
		printf("ligne = %d, colonne = %d\n",n,m);
		displayMatrix(matrix,n,m);
	}
	else
	{
		printf("[ERROR] : Error during creation\n");
	}
	
}
*/
/*
* -1 = problem while openin file
* 1 = no problem
* 0 = problem during allocation
*/
matrix_t loadMatrixFromFile(char* fileName,int *errorCode)
{
	FILE* file = fopen(fileName,"r");
	/* We create a matrix_t to store its value, column and line */
	matrix_t matrix;
	matrix.value = NULL;
	*errorCode = -1;

	if(file!= NULL) /* We make sure, we actually opened the file */
	{

		/* We can get dimension of the matrice n*m through the first line*/
		int i=0, j=0;
		*errorCode = 0;

		fscanf(file,"%d %d",&matrix.line,&matrix.column);


		matrix.value = malloc(matrix.line * sizeof(float*));

		if (matrix.value == NULL)
		{
			return(matrix);
		}

		/* TODO: free the memory already allocate if we encouter a problem */
		for(i=0; i< matrix.line; i++)
		{
			matrix.value[i]= malloc(matrix.column * sizeof(float));

			if(matrix.value[i]==NULL)
			{
				return(matrix);
			}
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
	
		
	}
	else
	{	
		*errorCode = -1; /* We had a problem while opening the file*/
	}
	return(matrix);
}

void displayMatrix(matrix_t matrix)
{
	int i=0,j=0;

	for(i = 0;i < matrix.line;i++)
	{
		for(j=0;j < matrix.column;j++)
		{
			printf("%f ",matrix.value[i][j]);
		}
		printf("\n");	
	}
}
matrix_t multiply(matrix_t A,matrix_t B)
{
	/* We first verify that we can't actualy do the multiplication */
	

}

































