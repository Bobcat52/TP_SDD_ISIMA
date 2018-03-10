#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ZZ_Liste_chainee.h"


/* ------------------------------------------------------------------------ */
/* findElt:  - Research an element in a sorted linked list.				    */
/*                                                                          */
/* Input:  	 - pHead is a ficticious head pointer of the linked list. 	    */
/* 			 - v is the value we search in the list. 						*/
/*                   														*/
/* ------------------------------------------------------------------------ */
production_t * findElt(float v, production_t * pHead)
{
	production_t  *curr = pHead;

	while (curr != NULL && curr->value < v)   /* while we aren't arrived at the end of the list and the value is lower that v, we go through the list */
	{
			curr = curr->next;	/* we move forward in the list */
	}

	return(curr); /* we return the adress of the element researched if we found it, otherwise return NULL */
}

/* -----------------------------------------------------------------------------*/
/* insertKSorted: - Insert a block in a linked list so that it stay sorted and	*/ 
/*				     not exceed a length of K  									*/
/*                                                                          	*/
/* Input:  		  - pHead is a ficticious head pointer of the linked list. 	    */
/* 			      - adress is the adress of a block. We want to place our		*/ 
/*				    block before this one.   									*/		
/*                - element is the block we want to place.						*/
/* 			      - K is the maximal length of our linked list 					*/
/*				    (note that she can obviously be of length < K).    			*/
/*                   															*/
/* -----------------------------------------------------------------------------*/
void insertKSorted(production_t ** pHead, production_t *adress, production_t *element, int K)
{
	production_t  ** prev  =   pHead;
	production_t  *  curr  = * pHead;

	if(curr != NULL)
	{
		int j = 0;

		/* We go through the linked list, searching for the adress */
		while (curr != NULL && curr != adress)
		{
			prev = &(curr->next);
			curr = curr->next;

			j++; /* We increment a counter, if it overpasses K, it means we can free the block because it has a to high value */
		}

		
		if(j <= K-1 )
		{

			if(adress == NULL)
			{
				element->next = curr; /* TODO : create a specific function */
				*prev = element;
			} 
			else
			{		
				element->next = curr; /* TODO : create a specific function */
				*prev = element;

				/* We need to set curr to the element because the block is inserted before it */
				curr = element;

				while (curr != NULL && j <= K-2)
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
		}
		else
		{
			free(element); /* we free the element because it's outranged */
	
		}
	}
	else
	{
		element->next = curr; /* TODO : create a specific function */
		*pHead = element;
	}

}

/* ----------------------------------------------------------------------------------------*/
/* removeFactory:  - Remove all the factory having "factory" as index in the linked list.  */
/*                                                                          			   */
/* Input:  		   - pHead is a ficticious head pointer of the sorted linked list.         */
/* 			       - factory is an intenger which represent the index of a factory.  	   */                   
/* ----------------------------------------------------------------------------------------*/
void removeFactory(production_t **pHead,int factory)
{
	/* We initiliaze a previous and a current pointer for the research */
	production_t  ** prev  =  pHead;
	production_t  *  curr  = *pHead;
	production_t  *  tmp;

	while (curr != NULL) /* while we  aren't arrived at the end of the list we go through the list */
	{	
		tmp = NULL;

		if(curr->factory == factory) /* if we found the factory researched  */
		{
			tmp = curr;
			*prev = curr->next;			
		}
		else /*  if the current element is not the factory researched */
		{
			prev = &(curr->next); /* the previous pointer points to the adress of the next element , and NOT to the next element !! */
		}
		
		curr = curr->next; /* we move forward in the list, the current pointer points to the next element */
		
		if(tmp != NULL)	
		{
			 free(tmp);	/* we free it to avoid a problem of memory not restored */
		}	
	}
}

/* -------------------------------------------------------------------------------------------------*/
/* printLinkedList:  - print a linked list in a file (it can be stdout, stderr, or a created file). */
/*                                                                          						*/
/* Input:  			 - pHead is a ficticious head pointer of the linked list.					    */
/*                   																			    */	
/* -------------------------------------------------------------------------------------------------*/
void writeLinkedListToFile(FILE* file,production_t *pHead)
{
	production_t  *curr = pHead; /* we initialize a current pointer which will go through the list  */

	while (curr != NULL) /* while we aren't arrived at the end of the list, we print a message with datas picked up in the list */
	{
		fprintf(file,"L'usine %d a une production de %f à la période %d \n",curr->factory,curr->value,curr->period);
		curr = curr->next;
	}

}

/* -----------------------------------------------------------------------------------------------------*/
/* insertProductionBlock: - Creates and insert a production block in the linked list.                   */
/*                                                                                                      */
/* Input:  				  - pHead is a ficticious head pointer of the linked list. 	                    */
/* 			    		  - value is the production of a factory.	   									*/
/*              		  - factory is an intenger which represent the index of a factory.	  	  		*/
/*						  - period is an integer which represent the period of the production.		  	*/
/*						  - K is the number of the smallest production we want to pick out.    			*/     
/* ---------------------------------------------------------------------------------------------------- */
void insertProductionBlock(production_t **pHead, float value, int factory, int period, int K)
{	
	production_t *insertAdress;
	production_t *newElement;		
	
	insertAdress = findElt(value,*pHead); /* we research the adress in the list where we could insert the new element */
	newElement = (production_t *)malloc(sizeof(production_t));  /* creation of a new block */
	
	/* If we were able to allocate the block */
	if(newElement != NULL)
	{
		/* we assign datas to the new block */
		newElement->value = value;
		newElement->factory = factory;
		newElement->period = period;
		newElement->next = NULL;

		insertKSorted(pHead,insertAdress,newElement,K); /* we insert the new block in the sorted linked list by keeping the list sorted */	
	}	
	else
	{
		printf("[ERROR]: Problem during allocation.\n");
	}
}

/* ---------------------------------------------------------------------------------*/
/* freeLinkedList:  - Free the linked list   										*/
/*                                                                          		*/
/* Input:  	        -pHead is a ficticious head pointer of the sorted linked list 	*/
/*                   																*/	
/* ---------------------------------------------------------------------------------*/
void freeLinkedList(production_t *pHead)
{
	/* We initiliaze a temp and a current pointer for the release */
	production_t *curr = pHead;
	production_t *temp = NULL;

	while(curr != NULL) /* while we  aren't arrived at the end of the list we go through the list */
	{
		temp = curr;   					
									
		curr = curr->next;/* we move forward in the list */
		free(temp);	/* we free the temporary pointer which pointed to the former current element */
	}
}

