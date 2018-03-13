#include "ZZ_queue.h"

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
queue_t* initQueue(int size,int* errorCode)
{
	queue_t* p0;

	*errorCode = -1;
	
	p0 = (queue_t*)malloc(sizeof(queue_t));
	if(p0 != NULL)
	{
		p0->size = size;
		p0->number = 0;
	
		p0->base = (queueType*)malloc(size * sizeof(queueType));
		*errorCode = 0;
		if(p0->base != NULL)
		{		
			*errorCode = 1;
			p0->start = p0->base;
			p0->end = p0->base + sizeof(queueType) * (size-1);
		}	
	}

	return(p0);
}
/* -------------------------------------------------------------------- */
/* enterQueue         Put a value in the queue                 		*/
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
void enterQueue(queue_t* p0,queueType element,int* errorCode)
{
	*errorCode = 0;
	if(p0->number < p0->size)
	{
		*errorCode = 1;
		p0->end = ((p0->end - p0->base + sizeof(queueType)) % p0->size) + p0->base;
		*p0->end = element;
		p0->number += 1;
		
	}
}
queueType leaveQueue(queue_t* p0,int* errorCode)
{
	queueType res;

	*errorCode = 0;

	if(p0->number != 0)
	{

		*errorCode = 1;
		res = *(p0->start);
		p0->start = ((p0->start - p0->base + sizeof(queueType)) % p0->size) + p0->base;
		p0->number -= 1;

	}

	return(res);

}
int isQueueEmpty(queue_t* p0)
{
	return(p0->number == 0);
}
void freeQueue(queue_t* p0)
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
