#ifndef INSERTION_H
#define INSERTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ZZ_tree.h"
#include "../include/ZZ_queue.h"

queue_t* initQueue(int size,int* errorCode);
void enterQueue(queue_t* p0,queueType element, int* errorCode);
queueType leaveQueue(queue_t* p0, int* errorCode);
int isQueueEmpty(queue_t* p0);
void freeQueue(queue_t* p0);

noeud_t *  rechercher(noeud_t * a, char v, int * errorCode);
void insert(noeud_t* v,char w,int * errorCode);


#endif