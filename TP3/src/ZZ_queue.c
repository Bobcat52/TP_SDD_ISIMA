/* ########################################################## */
/* file's name : ZZ_queue.c				      */
/*							      */
/* Author : Mathieu Boutin & Jérémy Morceaux                  */
/* Date : March 2018					      */
/*							      */
/* This file contains source from the ZZ_queue.h	      */
/*							      */
/* Desc : this file create some function to work with         */
/*        queue (init, enter, leave, free)		      */
/* ########################################################## */

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
	queue_t * p0;

	*errorCode = -1;
	
	/* We create the queue */
	p0 = (queue_t*)malloc(sizeof(queue_t));

	if(p0 != NULL)
	{
		/* Init the queue data */
		p0->size = size;
		p0->number = 0;
	
		/* allocate an array to store the data */
		p0->base = (queueType*)malloc(size * sizeof(queueType));
		*errorCode = 0;

		/* If the allocation went well */
		if(p0->base != NULL)
		{		
			*errorCode = 1;
			p0->start = 0;
			p0->end = size-1;
		}	
	}

	return(p0); /* return the pointer of the queue */
}

/* -------------------------------------------------------------------- */
/* enterQueue         Put a value in the queue                 		*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue.                  		*/
/*            - element is the value that is entering the queue.	*/
/*	      - errorCode is an integer that stores the result of the 	*/
/*		function :   0 - the queue is full, no more data can    */
/*				 enter the queue            	        */
/*									*/
/*			     1 - everything went well !!		*/
/* -------------------------------------------------------------------- */
void enterQueue(queue_t* p0,queueType element,int* errorCode)
{
	*errorCode = 0;
	/* if the queue is not full */
	if(p0->number <= p0->size)
	{
		*errorCode = 1;
		/* we actualize the index end, and the number of value in the queue*/
		p0->end = (p0->end + 1) % p0->size;
		p0->base[p0->end] = element;
		p0->number += 1;
		
	}
	else /* the queue is full */
	{
		fprintf(stderr,"[WARNING] This queue is full \n");
	}
}

/* -------------------------------------------------------------------- */
/* leaveQueue         Remove a value in the queue			*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue.                  		*/
/*	      - errorCode is an integer that stores the result of the 	*/
/*		function :   0 - the queue is empty, there is no data 	*/
/*				 to retrieve          			*/
/*									*/
/*			     1 - everything went well			*/
/* -------------------------------------------------------------------- */
queueType leaveQueue(queue_t* p0,int* errorCode)
{
	queueType res;
	*errorCode = 0;

	/* Make sure the queue is not empty */
	if(!isQueueEmpty(p0))
	{
		*errorCode = 1;
		/* retrieve the value which will be returned */
		res = p0->base[p0->start];

		/* actualiaze the index start, and the number of value in the queue */
		p0->start = (p0->start + 1 ) % p0->size;
		p0->number -= 1;
	}

	return(res); /* return the value */
}

/* -------------------------------------------------------------------- */
/* isQueueEmpty         Check if the queue is empty or not		*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue.                  		*/
/*									*/
/* Ouput :  - 1 : the queue is empty					*/
/*          - 0 : it isn't						*/
/* -------------------------------------------------------------------- */
int isQueueEmpty(queue_t* p0)
{
	return(p0->number == 0); /* simply return either the queue is full or not */
}

/* -------------------------------------------------------------------- */
/* freeQueue         Free correctly a queue				*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue.                  		*/
/*									*/
/* -------------------------------------------------------------------- */
void freeQueue(queue_t* p0)
{
	if(p0->base != NULL) /* we first free the array */
	{	
		free(p0->base);
	}
	if(p0 != NULL) /* and then we can free the queue */
	{	
		free(p0);
	}
}

/* -------------------------------------------------------------------- */
/* printQueue         print a Queue to a terminal			*/
/*                                                                      */
/* Input :    - p0 is a pointer to the queue.                  		*/
/*									*/
/* -------------------------------------------------------------------- */
void printQueue(queue_t *p0)
{
	int i;

	/* simply display each value of the queue */
	for(i=0;i < p0->number;i++)
	{
		printf("%d ",p0->base[(p0->start +i ) % p0->size]);
	}
	printf("\n");
}