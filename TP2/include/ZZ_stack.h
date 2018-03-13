#ifndef ZZ_STACK_H
#define ZZ_STACK_H

typedef int typeStack;

typedef struct stack
{
		int           sizeMax;
		int           numSummit;
		typeStack  *  begin;
}stack_t;


stack_t * initStack(int size, int * errorCode); 

void freeStack( stack_t * p);

int isStackEmpty(stack_t * p);

void push(stack_t * p, typeStack v ,int * errorCode);

void pop(stack_t * p, typeStack * v, int * errorCode);

stack_t* initStackFromFile(char * fileName, int * errorCode);

void printStack(stack_t* p);
#endif
