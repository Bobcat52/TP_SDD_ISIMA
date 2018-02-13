#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ZZ_Liste_chainee.h"


float mat[I][J]={ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };




float min2(float matrice[I][J])
{		
		float tab=float malloc(3*sizeof(float));
		int i, j, k, l;
		for (k=0;k<K;k++)
		{
			
			²


float min (float matrice[I][J])
{	float * T=NULL;
	float m=matrice[0][0];
	int i,j;
	tab=getTabAlloc(3);		
	T[0]=m;
	T[1]=0;
	T[2]=0;
	for(i=0;i<I;i++)
	{
		for (j=0;i<J;j++)
		{
			if (m> matrice[i][j])
			{	
				m= matrice[i][j];
				T[0]=m;
				T[1]=i;
				T[2]=j;
			}
		}
	}
	
	return T;
}


float max (float matrice[I][J])
{
	float  m= matrice[0][0];
	float *T=NULL;
	int i,j;
	
	T[0]=m;
	T[1]=0;
	T[2]=0;
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

void listech (float ** matrice[I][J])
{
	liste * cell= liste_t malloc(sizeof(liste_t));
	float M[3]=max(matrice[I][J]);
	float m[3];
	int k, i ,j, v;
	for (k=0;k<K;k++)
	{	
		m=min(matrice[I][J]);
		v=m[0];
		i=m[1];
		j=m[2];
		cell->valeur= l;
		cell->ligne = i;
		cell->colonne= j;
		cell-suivant=liste_t malloc(sizeof(liste_t));
		matrice[i][j]=M[0];
	}


int main()
{
	float  M=max(mat[I][J]);
	float  m=min(mat[I][J]);
	printf("Le max est %f et le min est %f \n", M , m);
	return 0;
} 	
	
