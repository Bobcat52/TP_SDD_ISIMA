/* ###################################################### */
/* file's name : ZZ_linked_list.h						  */
/*												    	  */
/* Author : Mathieu Boutin & Jérémy Morceaux		 	  */
/* Date : March 2018								 	  */
/*													 	  */
/* This file contains source from ZZ_linked_list.h		  */
/* Desc : It allows the user to manipulate a linked list  */ 
/* (insertion, printing, finding etc ...)				  */
/* ###################################################### */


#ifndef ZZ_LINKED_LIST_H
#define ZZ_LINKED_LIST_H


/* Struct */
typedef struct production
{	
	float 					value;
	int 					factory;
	int 					period;
	struct production 	  * next;

} production_t;


/* Function */
production_t * findElt(float v, production_t * pHead);
void linkBlock(production_t ** prev,production_t * element,production_t * next);
void insertKSorted(production_t ** pHead, production_t *address,production_t *element,int K);
void insertProductionBlock(production_t **pHead,float value,int factory,int period,int K);
void freeLinkedList(production_t *pHead);
void removeFactory(production_t **pHead,int factory);
void writeLinkedListToFile(FILE *file,production_t *pHead);

#endif
