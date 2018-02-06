#include <stdlib.h>
#include <stdio.h>
#include "ZZ_matrix.h"


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

float** loadMatrixFromFile(char* fileName,int*line,int*column,int *errorCode)
{
	FILE* file = fopen(fileName,"r");
	float ** matrix = NULL;
	*errorCode = -1;

	if(file!= NULL) /* We make sure, we actually opened the file */
	{

		/* We can get dimension of the matrice n*m through the first line*/
		int n=0, m=0, i=0, j=0;
	
		fscanf(file,"%d %d",&n,&m);
		printf("n = %d, m = %d\n",n,m);
		matrix=malloc(n*sizeof(float*));

		if (matrix == NULL)
		{
			return(NULL);
		}


		for(i=0; i<n; i++)
		{
			matrix[i]= malloc(m*sizeof(float));

			if(matrix[i]==NULL)
			{
				return(NULL);
			}
		}
		/* We then, get the values of the matrix */
		*errorCode = 1;
		*line = n;
		*column = m;

		for(i = 0;i < n;i++)
		{
			for(j=0;j < m;j++)
			{
				fscanf(file,"%f",&matrix[i][j]);
			}
		}
	
		
	}
	else
	{	
		*errorCode = -1; /* We had a problem while opening the file*/
	}
	return(matrix);
}

void displayMatrix(float **matrix,int n,int m)
{
	int i=0,j=0;

	for(i=0;i< n;i++)
	{
		for(j=0;j< m;j++)
		{
			printf("%f ",matrix[i][j]);
		}
		printf("\n");	
	}
}


