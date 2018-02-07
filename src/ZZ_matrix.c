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
matrix_t multiply(matrix_t A,matrix_t B,int *errorCode)
{

	matrix_t matrixRes;
	matrixRes.value = NULL;
	/* We first verify that we can't actualy do the multiplication */
	if(A.column == B.line)
	{
		/* We can perform the multiplication */
		matrixRes.line = A.line;
		matrixRes.column = B.column;

		int errorCode;
		matrixRes = zeroMatrix(A.line,B.column,&errorCode);

		if(errorCode == 1)
		{
				int i=0,j=0;
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
			printf("[ERROR] : Unable to allocate enough space to create a third matrix !\n");
		}


	}
	else
	{
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
	matrix_t matrix;
	matrix.value = NULL;
	matrix.line = line;
	matrix.column = column;

	/* We can get dimension of the matrice n*m through the first line*/
	int i=0, j=0;
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
	/* We then, get the values of the matrix */
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
