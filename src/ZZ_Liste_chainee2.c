#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ZZ_Liste_chainee.h"

/* ------------------------------------------------------------------------ */
/* rechElt:   Research an element in a sorted linked list				    */
/*                                                                          */
/* Input:  		pHead is a ficticious head pointer of the linked list 	    */
/* 			    v is the value we search in the list  						*/
/*                   														*/
/* ------------------------------------------------------------------------ */

production_t * rechElt(float v, production_t * pHead)
{
	production_t  *curr = pHead;		/* we initialize a current pointer wich will go through the list */

	while (curr != NULL && curr->value < v)   /* while we  aren't arrived at the end of the list and the value is lower that v, we go through the list */
	{
			curr = curr->next;				/* we move forward in the list */
	}

	return(curr);							/* we return the adress of the element reserched if we found it, otherwise we return NULL */
}
/* ------------------------------------------------------------------------ */
/* insertKSorted:    Insert a block in the sorted linked list of K length   */
/*                                                                          */
/* Input:  		pHead is a ficticious head pointer of the linked list 	    */
/* 			   adresse is a pointer of production structure      		    */
/*             element is a pointer of a element in matrix 				    */
/* 			   K is the number of the smallest production in the matrix     */
/*                   														*/
/* ------------------------------------------------------------------------ */


void insertKSorted(production_t ** pHead, production_t *adresse, production_t *element, int K)
{
	production_t  ** prev  =  pHead;		/* we intialize a previous pointer wich points to the previous element of the list */
	production_t  *  curr  = *pHead;		/* we initialize a current pointer wich will go through the list  */

	int j = 0;
	
	while (curr != NULL && curr != adresse)
	{
			prev = &(curr->next);
			curr = curr->next;

			j++;
	}

	if(adresse == NULL) /* If the block need to be put at the end of the linked list but length < K */
	{
		if(j < K-2)
		{
			element->next = curr; /* create a specific function */
			*prev = element;
		} 
		else
		{
			free(element); /* we free the element because it's outrange */
		}
	}
	else
	{
		
		element->next = curr; /* create a specific function */
		*prev = element;
		
		if(j < K-2)
		{
			while (curr != NULL && j < K-2)
			{
				prev = &(curr->next);
				curr = curr->next;
				
				j++;
			}
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
}



/* ----------------------------------------------------------------------------------------*/
/* removeFactory:  Remove a factory by pointing the previous factory to the next factory   */
/*                                                                          			   */
/* Input:  		pHead is a ficticious head pointer of the sorted linked list               */
/* 			    factory is an intenger wich represent the number of a factory  			   */                   
/* ----------------------------------------------------------------------------------------*/


void removeFactory(production_t **pHead,int factory)
{
	production_t  ** prev  =  pHead;	/* we intialize a previous pointer wich points to the previous element of the list */
	production_t  *  curr  = *pHead;	/* we initialize a current pointer wich will go through the list  */
	production_t  *  tmp;				/* we initialize a temporary pointer */

	while (curr != NULL)				/* while we  aren't arrived at the end of the list we go through the list */
	{	
		tmp = NULL;
		if(curr->factory == factory)	/* if we found the factory researched  */
		{
			tmp = curr;
			*prev = curr->next;			/* the previous element points to the next element, now the current element isn't in the sorted linked list */
		}
		else                            /*  if the current element is not the factory researched */
		{
			prev = &(curr->next);		/* the previous pointer points to the adress of the next element , and NOT to the next element !! */
		}
		
		curr = curr->next;				/* we moove forward in the list, the current pointer points to the next element */
		
		if(tmp != NULL)					/* if the temporary pointer is not NULL */
		{
			 free(tmp);					/* we free it to avoid a problem of memory not restored */
		}	
	}
}

/* ------------------------------------------------------------------------ */
/* printLinkedList:  Display a message  									*/
/*                                                                          */
/* Input:  	pHead is a ficticious head pointer of the sorted linked list 	*/
/*                   														*/	
/* -------------------------------------------------------------------------*/
void printLinkedList(struct production *pHead)
{
	production_t  *curr = pHead;

	while (curr != NULL)
	{
			printf("L'usine %d a une production de %f à la période %d \n",curr->factory,curr->value,curr->period);
			curr = curr->next;
	}

}



/* -----------------------------------------------------------------------------------------------------*/
/* writeLinkedListToFile:  Write in a file a message by going through a list                            */
/*                                                                                                      */
/* Input:  		pHead is a ficticious head pointer of the linked list 	                                */
/* 			    fileName is a pointer of a file where we want to write a message wich stores some data  */                   
/* ---------------------------------------------------------------------------------------------------- */


void writeLinkedListToFile(char *fileName,production_t *pHead)
{
	FILE* file = fopen(fileName,"w");		/* we open a flow */
	production_t  *curr = pHead;            /* we initialize a current pointer */

	if(file != NULL)						/* if the flow is correctly opened */
	{
		while (curr != NULL)				/* while we aren't arrived at the end of the list */
		{
				fprintf(file,"L'usine %d a une production de %f à la période %d \n",curr->factory,curr->value,curr->period);
				curr = curr->next;			/* we move forward in the list by going to the next element of the list */
		}
		fclose(file);						/* Don't forget to close the file otherwise we will have problem with memory not restored */
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
