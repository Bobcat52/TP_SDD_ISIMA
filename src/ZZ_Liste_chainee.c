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
	production_t  ** prev  =   pHead;
	production_t  *  curr  = * pHead;

	if(curr != NULL)
	{
		int j = 0;
		printf("test\n");
		

		/* We go through the linked list, searching for the adress */
		while (curr != NULL && curr != adresse)
		{
			prev = &(curr->next);
			curr = curr->next;

			j++; /* We increment a counter, if it overpasses K, it means we can free the block because it has a to high 			value */
		}

		
		/* Once we found it, we either insert it into the list or we free the block */
		if(adresse == NULL)
		{

			if(j <= K-2 )
			{
				element->next = curr; /* TODO : create a specific function */
				*prev = element;
			} 
			else
			{
				free(element); /* we free the element because it's outranged */
			}
		}
		else
		{
		
			if(j <= K-2)
			{	
				element->next = curr; /* TODO : create a specific function */
				*prev = element;
		
				while (curr != NULL && j < K-2)
				{
					prev = &(curr->next);
					curr = curr->next;
				
					j++;
				}

				if(curr != NULL)
				{
					production_t *temp;
					temp = curr->next;
					curr->next = NULL;
					freeLinkedList(temp);
					temp = NULL;
				}

			}
			else
			{
				free(element); /* we free the element because it's outranged */
			}

		
		}
	}
	else
	{
		element->next = curr; /* TODO : create a specific function */
		*prev = element;
	}


}
void removeFactory(production_t **pHead,int factory)
{
	production_t  ** prev  =  pHead;
	production_t  *  curr  = *pHead;
	production_t  *  tmp;

	while (curr != NULL)
	{	
		tmp = NULL;
		if(curr->factory == factory)
		{
			tmp = curr;
			*prev = curr->next;
		}
		else
		{
			prev = &(curr->next);
		}
		
		curr = curr->next;
		
		if(tmp != NULL)
		{
			 free(tmp);
		}	
	}
}
void writeLinkedListToFile(FILE* file,production_t *pHead)
{
	production_t  *curr = pHead;

	while (curr != NULL)
	{
		fprintf(file,"L'usine %d a une production de %f à la période %d \n",curr->factory,curr->value,curr->period);
		curr = curr->next;
	}

}
void insertProductionBlock(production_t **pHead, float value, int factory, int period, int K)
{	
	production_t *insertAdress;
	production_t *newElement;
	
	insertAdress = rechElt(value,*pHead);
	newElement = (production_t *)malloc(sizeof(production_t));
	
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
