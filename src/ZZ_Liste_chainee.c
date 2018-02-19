#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ZZ_Liste_chainee.h"



production_t * rechElt(float v, production_t * pHead)
{
	production_t  *curr = pHead;

	while (curr != NULL && curr->value < v)
	{
			curr = curr->next;
	}

	return(curr);
}
/* ------------------------------------------------------------------------ */
/* insertKSorted     Insert a block in the sorted linked list of K length */
/*                                                                      */
/* En entrée: s1, s2 Deux chaînes de caractères                         */
/*                                                                      */
/* En sortie: La value entière retournée est 0 si les chaînes sont     */
/*            égales; négative si s1 < s2 et positive si s1 > s2.       */
/* -------------------------------------------------------------------- */
void insertKSorted(production_t ** pHead, production_t *adresse, production_t *element, int K)
{
	production_t  ** prev  =  pHead;
	production_t  *  curr  = *pHead;

	int j = 0;
	
	while (curr != NULL && curr != adresse)
	{
			prev = &(curr->next);
			curr = curr->next;

			j++;
	}

	if(adresse == NULL) /* If the block need to be put at the end of the linked list but length < K */
	{
		if(j <= K-1)
		{
			element->next = curr; /* create a specific function */
			*prev = element;
		}
	}
	else
	{
		
		element->next = curr; /* create a specific function */
		*prev = element;
		
		if(j <= K-1)
		{
			while (curr != NULL && j <= K-1)
			{
				prev = &(curr->next);
				curr = curr->next;
				
				j++;
			}
		}
		

		if(curr != NULL && curr->next != NULL)
		{
			curr->next = NULL;
		}
	}
}
void printLinkedList(struct production *pHead)
{
	production_t  *curr = pHead;

	while (curr != NULL)
	{
			printf("L'usine %d a une production de %f à la période %d \n",curr->factory,curr->value,curr->period);
			curr = curr->next;
	}

}
void insertProductionBlock(production_t **pHead, float value, int factory, int period, int K)
{	
	production_t *insertAdress;
	insertAdress = rechElt(value,*pHead);
	
	production_t *newElement = (production_t *)malloc(sizeof(production_t));
	newElement->value = value;
	newElement->factory = factory;
	newElement->period = period;
	newElement->next = NULL;

	insertKSorted(pHead,insertAdress,newElement,K);	
}
void freeLinkedList(production_t *pHead)
{
	production_t *curr = pHead;
	production_t *temp = NULL;

	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}