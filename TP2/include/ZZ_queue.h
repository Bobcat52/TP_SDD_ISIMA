#ifndef ZZ_QUEUE_H
#define ZZ_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef int queueType;

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
void printQueue(queue_t* p0);
#endif
