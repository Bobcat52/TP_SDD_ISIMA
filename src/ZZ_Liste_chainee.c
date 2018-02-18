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
tableau_t * rechElt(float v, tableau_t * tableau)
{
	tableau_t  *cour = tableau;

	while (cour != NULL && cour->valeur < v)
	{
			cour = cour->suivant;
	}

	return(cour);
}
/* ------------------------------------------------------------------------ */
/* insertKSorted     Insert a block in the sorted linked list of K length */
/*                                                                      */
/* En entrée: s1, s2 Deux chaînes de caractères                         */
/*                                                                      */
/* En sortie: La valeur entière retournée est 0 si les chaînes sont     */
/*            égales; négative si s1 < s2 et positive si s1 > s2.       */
/* -------------------------------------------------------------------- */
void insertKSorted(tableau_t ** tableau, tableau_t *adresse,tableau_t *element,int K)
{
	tableau_t  **pprec= tableau;
	tableau_t  *cour= *tableau;
	int j;
	j=0; /* indice de parcours */
	while (cour != NULL && cour != adresse)
	{
			pprec = &(cour->suivant);
			cour = cour->suivant;

			j++;
	}

	if(adresse == NULL) /* If the block need to be put at the end of the linked list but length < K */
	{
		if(j < K)
		{
			element->suivant = cour; /* create a specific function */
			*pprec = element;
		}
	}
	else
	{
		
		element->suivant = cour; /* create a specific function */
		*pprec = element;
		
		if(j < K)
		{
			while (cour != NULL && j < K-2)
			{
				pprec = &(cour->suivant);
				cour = cour->suivant;
				j++;
			}
		}
	
		if(cour != NULL)
			cour->suivant = NULL;
		
	}
}
void afficherListeChaine(struct tableau *pTete)
{
	printf("Nouvelle liste chainée : \n");
	tableau_t  *cour = pTete;

	while (cour != NULL)
	{
			printf("L'usine %d a une production de %f à la période %d \n",cour->ligne,cour->valeur,cour->colonne);
			cour = cour->suivant;
	}
	printf("Fin nouvelle liste chainée \n\n");
}
void insertBlock(tableau_t **pTete,float valeur,int ligne,int colonne,int K)
{	
	tableau_t *adresseAInserer;
	adresseAInserer = rechElt(valeur,*pTete);
	
	tableau_t *nvElement = (struct tableau*)malloc(sizeof(struct tableau));
	nvElement->valeur = valeur;
	nvElement->ligne = ligne;
	nvElement->colonne = colonne;
	nvElement->suivant = NULL;

	insertKSorted(pTete,adresseAInserer,nvElement,K);	
}
