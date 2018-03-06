#ifndef ZZ_Pile_h
#define ZZ_Pile_h

typedef int typeStack;

typedef struct stack
{
		int           sizeMax;
		int           numSummit;
		typeStack  *  begin;
}stack_t;


stack_t * initStack(int size, int * errorCode); 

void freeStack( stack_t * p)

int isEmpty(stack_t * p)

void stack (stack_t * p, typeStack v ,int * errorCode)

void unStack ( stack_t * p, typeStack * v, int * errorCode)

#endif
