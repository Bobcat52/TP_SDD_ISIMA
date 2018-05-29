#ifndef ZZ_POSTFIXE_H
#define ZZ_POSTFIXE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ZZ_stack.h"
#include "../include/ZZ_tree.h"


int isStackEmpty(stack_t * p);
void push(stack_t * p, typeStack v ,int * errorCode);
void pop( stack_t * p, typeStack * v, int * errorCode);
void repPostFixe(noeud_t* a,int* errorCode);

stack_t * initStack(int size, int * errorCode);


#endif