/* ########################################################## */
/* file's name : ZZ_queue.h				                      */
/*							                                  */
/* Author : Mathieu Boutin & Jérémy Morceaux                  */
/* Date : March 2018					                      */
/*							                                  */
/* This file contains headers for the file ZZ_queue.c         */
/*							                                  */
/* ########################################################## */

#ifndef ZZ_QUEUE_H
#define ZZ_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/ZZ_tree.h"
typedef struct elmtFile
{
	adresse adr;
}elmtFile_t;

typedef elmtFile_t queueType; 

typedef struct queue{

	int size;
	int number;
	int start;
	int end;
	queueType* base;

} queue_t;


queue_t* initQueue(int size,int* errorCode);
void enterQueue(queue_t* p0,queueType element, int* errorCode);
queueType leaveQueue(queue_t* p0, int* errorCode);
int isQueueEmpty(queue_t* p0);
void freeQueue(queue_t* p0);
#endif
