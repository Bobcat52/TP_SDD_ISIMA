#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ZZ_Liste_chainee.h"



void insererListe(struct tableau **pTete, struct tableau *element)
{
	element->suivant = *pTete;
	*pTete = element;
}
tableau_t * addNewElement( tableau_t **ptete)
{
		tableau_t *newelmt= (struct tableau *)malloc(sizeof(struct tableau));
		insererListe(ptete,newelmt);
}
float* rechElt(int v, tableau_t * tableau)
{
	tableau_t  *pprec= tableau;
	tableau_t  *cour= &tableau->valeur;
	while (cour!=NULL && cour->valeur < v)
	{
			pprec = &(cour->suivant);
			cour = pprec->suivant;
	}
	return(&pprec->valeur);
}
void afficherListeChaine(struct tableau *pTete)
{
	
}
/*

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

*/
int main()
{
	tableau_t *pTete;
	pTete = (struct tableau*)malloc(sizeof(struct tableau));
	pTete->valeur = 5;
	pTete->ligne = 5;
	pTete->colonne = 2;
	
	tableau_t *nvElement = (struct tableau*)malloc(sizeof(struct tableau));
	nvElement->valeur = 3;
	nvElement->ligne = 2;
	nvElement->colonne = 5;
	
	insererListe(&pTete,nvElement);
	
	
	tableau_t *nvElement1 = (struct tableau*)malloc(sizeof(struct tableau));
	nvElement1->valeur = 6;
	nvElement1->ligne = 5;
	nvElement1->colonne = 7;
	
	insererListe(&pTete,nvElement1);
	
	
	tableau_t *nvElement2 = (struct tableau*)malloc(sizeof(struct tableau));
	nvElement2->valeur = 1;
	nvElement2->ligne = 2;
	nvElement2->colonne = 6;
	
	insererListe(&pTete,nvElement2);	
	
} 	
	
