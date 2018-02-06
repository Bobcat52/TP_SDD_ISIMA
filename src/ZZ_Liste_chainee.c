#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ZZ_Liste_chainee.h"


float mat[I][J]={ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
float * tab (int tabsize) 
{
    return(malloc(tabsize*sizeof(float));
}
float min (float matrice[I][J])
{	float *tab=NULL;
	float m=matrice[0][0];
	int i,j;
	tab=getTabAlloc(3);		
	tab[0]=m;
	tab[1]=0;
	tab[2]=0;
	for(i=0;i<I;i++)
	{
		for (j=0;i<J;j++)
		{
			if (m> matrice[i][j])
			{	
				m= matrice[i][j];
				tab[0]=m;
				tab[1]=i;
				tab[2]=j;
			}
		}
	}
	
	return tab;
}


float max (float matrice[I][J])
{
	float  m= matrice[0][0];
	float *tab=NULL;
	int i,j;
	tab=getTabAlloc(3);
	tab[0]=m;
	tab[1]=0;
	tab[2]=0;
	for(i=0;i<I;i++)
	{
		for (j=0;i<J;j++)
		{
			if (m<  matrice[i][j])
			{
				
				m= matrice[i][j];
				tab[0]=m;
				tab[1]=i;
				tab[2]=j;;
			}
		}
	}
	return  tab;
}
/*
void petitK (float ** matrice[I][J])
{
	liste * cell= liste_t malloc(sizeof(liste_t));
	float M=max(matrice[N][N]);
	int i,j,k;
	for (k=0;k<K;k++)
	{
	

*/
int main()
{
	float  M=max(mat[I][J]);
	float  m=min(mat[I][J]);
	printf("Le max est %f et le min est %f \n", M , m);
	return 0;
} 	
	
