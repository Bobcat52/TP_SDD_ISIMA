/* ###################################################### */
/* file's name : ZZ_linked_list.c						  */
/*												    	  */
/* Author : Mathieu Boutin & Jérémy Morceaux		 	  */
/* Date : March 2018								 	  */
/*													 	  */
/* This file contains headers for ZZ_linked_list.c		  */
/* Desc : It allows the user to manipulate a linked list  */ 
/* (insertion, printing, finding etc ...)				  */
/* ###################################################### */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ZZ_linked_list.h"


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

	while (curr != NULL && curr->value < v) /* while we aren't arrived at the end of the list and the value is lower that v, we go through the list */
	{
			curr = curr->next; /* we move forward in the list */
	}

	return(curr); /* we return the address of the element researched if we found it, otherwise return NULL */
}

/* -----------------------------------------------------------------------------*/
/* insertKSorted: - Insert a block in a linked list so that it stays sorted and	*/ 
/*				     not exceed a length of K  									*/
/*                                                                          	*/
/* Input:  		  - pHead is a ficticious head pointer of the linked list. 	    */
/* 			      - address is the address of a block. We want to place our		*/ 
/*				    block before this one.   									*/		
/*                - element is the block we want to place.						*/
/* 			      - K is the maximal length of our linked list 					*/
/*				    (note that she can obviously be of length < K).    			*/
/*                   															*/
/* -----------------------------------------------------------------------------*/
void insertKSorted(production_t ** pHead, production_t *address, production_t *element, int K)
{
	production_t  ** prev  =   pHead;
	production_t  *  curr  = * pHead;

	/* the linked list is not empty */
	if(curr != NULL)
	{
		int j = 0;

		/* We go through the linked list, searching for the address */
		while (curr != NULL && curr != address)
		{
			prev = &(curr->next);
			curr = curr->next;

			j++; /* We increment a counter, if it overpasses K, it means we can free the block because it has a to high value */
		}

		/* if j <= K-1 , we need to free the rest of the linked list so that its length stay <= K */
		if(j <= K-1 )
		{

			/* address = null means we are at the end of the linked list, so there is no block after this one */
			if(address == NULL)
			{
				/* We add the new block */	
				linkBlock(prev,element,curr);

			} 
			else
			{	
				/* We add the new block */	
				linkBlock(prev,element,curr);

				/* We need to set curr to the element because the block is inserted before it */
				curr = element;

				/* we find the last element of the linked list */
				while (curr != NULL && j <= K-2)
				{
					prev = &(curr->next);
					curr = curr->next;
				
					j++;
				}
				/* we free the rest of the linked list */
				if(curr != NULL)
				{
					production_t *tmp;

					tmp = curr->next; /* set next's last element to null */
					curr->next = NULL;

					freeLinkedList(tmp); /* free the rest of the linked list */
					tmp = NULL;
				}
				
			}
		}
		else /* j > k-1, this value is to high, we can free it */
		{
			free(element); /* we free the element because it's outranged */
	
		}
	}
	else /* the linked list is empty, just need to add the bloc to it */
	{
		linkBlock(pHead,element,curr);
	}

}

/* ----------------------------------------------------------------------------------------*/
/* linkBlock:					Link two block between them 							   */
/*                                                                          			   */
/* Input:  		   - prev is the struct that comes before element				           */
/* 			       - element is the struct we want to connect						  	   */ 
/* 			       - next is the struct that comes after element					  	   */  
/*                                                                          			   */                  
/* ----------------------------------------------------------------------------------------*/
void linkBlock(production_t ** prev,production_t * element,production_t * next)
{
	element->next = next; /* we simply modify the element's next and prev's next */
	*prev = element;

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
			prev = &(curr->next); /* the previous pointer points to the address of the next element , and NOT to the next element !! */
		}
		
		curr = curr->next; /* we move forward in the list, the current pointer points to the next element */
		
		if(tmp != NULL)	
		{
			 free(tmp); /* we free it to avoid a problem of memory not restored */
		}	
	}
}

/* --------------------------------------------------------------------------------------------------------*/
/* writeLinkedListToFile :  - print a linked list in a file (it can be stdout, stderr, or a created file). */
/*                                                                          							   */
/* Input:  			        - pHead is a ficticious head pointer of the linked list.					   */
/*                   																			           */	
/* --------------------------------------------------------------------------------------------------------*/
void writeLinkedListToFile(FILE* file,production_t *pHead)
{
	production_t  * curr = pHead; /* we initialize a current pointer which will go through the list  */

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
/* 			    		  - value is the production's cost of the factory.	   							*/
/*              		  - factory is an intenger which represent the index of the factory.	  	  	*/
/*						  - period is an integer which represent the period of the production.		  	*/
/*						  - K is the number of the smallest production we want to pick out.    			*/     
/* ---------------------------------------------------------------------------------------------------- */
void insertProductionBlock(production_t **pHead, float value, int factory, int period, int K)
{	
	production_t * insertaddress;
	production_t * newElement;		
	
	insertaddress = findElt(value,*pHead); /* we research the address in the list where we could insert the new element */
	newElement = (production_t *)malloc(sizeof(production_t));  /* creation of a new block */
	
	/* If we were able to allocate the block */
	if(newElement != NULL)
	{
		/* we assign datas to the new block */
		newElement->value = value;
		newElement->factory = factory;
		newElement->period = period;
		newElement->next = NULL;

		insertKSorted(pHead,insertaddress,newElement,K); /* we insert the new block in the sorted linked list by keeping the list sorted */	
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
	production_t * curr = pHead;
	production_t * temp = NULL;

	while(curr != NULL) /* while we  aren't arrived at the end of the list we go through the list */
	{
		temp = curr;   					
									
		curr = curr->next;/* we move forward in the list */
		free(temp);	/* we free the temporary pointer which pointed to the former current element */
	}
}

