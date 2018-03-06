#include "ZZ_File.h"

/* -------------------------------------------------------------------- */
/* initQueue         Init a queue properly                		*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue                  		*/
/*            - size is the size of the queue 				*/
/*	      - errorCode is an integer that stores the result of the 	*/
/*		function :  -1 - there is an issue while allocating 	*/
/*				 the queue            			*/
/*									*/
/*			     0 - there is an issue while allocation the	*/
/*				 the array in the queue			*/
/*									*/
/*			     1 - Everything went well !             	*/
/* -------------------------------------------------------------------- */
void initFile(file_t** p0,int size,int* errorCode) /* TODO = handle error */
{
	*errorCode = -1;
	*p0 = (file_t*)malloc(sizeof(file_t));
	if(*p0 != NULL)
	{
		(*p0)->size = size;
		(*p0)->number = 0;
	
		(*p0)->base = (typeFile*)malloc(size * sizeof(typeFile));
		*errorCode = 0;
		if((*p0)->base != NULL)
		{		
			*errorCode = 1;
			(*p0)->start = (*p0)->base;
			(*p0)->end = (*p0)->base + sizeof(typeFile) * (size-1);
		}	
	}
}
/* -------------------------------------------------------------------- */
/* enter         Put a value in the queue                 		*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue.                  		*/
/*            - element is the value that is entering the queue.	*/
/*	      - errorCode is an integer that stores the result of the 	*/
/*		function :  -1 - there is an issue while allocating 	*/
/*				 the queue            			*/
/*									*/
/*			     0 - there is an issue while allocation the	*/
/*				 the array in the queue			*/
/*									*/
/*			     1 - Everything went well !             	*/
/* -------------------------------------------------------------------- */
void push(file_t* p0,typeFile element,int* errorCode)
{
	*errorCode = 0;
	if(p0->number < p0->size)
	{
		*errorCode = 1;
		p0->end = ((p0->end - p0->base + sizeof(typeFile)) % p0->size) + p0->base;
		*p0->end = element;
		p0->number += 1;
		
	}
}
typeFile pop(file_t* p0,int* errorCode)
{
	typeFile res;
	*errorCode = 0;
	if(p0->number != 0)
	{
		*errorCode = 1;
		res = *(p0->start);
		p0->start = ((p0->start - p0->base + sizeof(typeFile)) % p0->size) + p0->base;
		p0->number -= 1;
	}
	return(res);
}
int estVide(file_t* p0)
{
	return(p0->number == 0);
}
void libererFile(file_t* p0)
{
	if(p0->base != NULL)
	{	
		free(p0->base);
	}
	if(p0 != NULL)
	{	
		free(p0);
	}
}
/*
int main()
{
	file_t* p0;
	p0 = NULL;
	int errorCode;

	initFile(&p0,3);
	push(p0,1,&errorCode);
	printf("valeur inserer = %d\n",*(p0->end));
	push(p0,2,&errorCode);
	printf("valeur inserer = %d\n",*(p0->end));
	push(p0,3,&errorCode);
	printf("valeur inserer = %d\n",*(p0->end));
	push(p0,4,&errorCode);
	printf("valeur inserer = %d\n",*(p0->end));


	printf("valeur retourne = %d\n",pop(p0,&errorCode));
	printf("valeur retourne = %d\n",pop(p0,&errorCode));
	printf("valeur retourne = %d\n",pop(p0,&errorCode));
	printf("valeur retourne = %d\n",pop(p0,&errorCode));

	libererFile(p0);
	return(0);

}*/
