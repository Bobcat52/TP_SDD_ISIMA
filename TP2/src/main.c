#include <stdio.h>
#include <stdlib.h>

#include "ZZ_stack.h"
#include "ZZ_queue.h"

int main()
{

	/* Declare our two structures */	
	queue_t* queue;
	stack_t* stack;
	int 	errorCode;
	char * fileName;
	fileName = "Stack/stack1.txt";

	/* Init our stack */
	stack = initStackFromFile(fileName,&errorCode);
	
	if(errorCode == 1)
	{
		printStack(stack);
	}
	else
	{
		if(errorCode == -1)
		{
			fprintf(stderr,"[ERROR] Can't open the file %s !\n",fileName);
		}
		else
		{
			fprintf(stderr,"[ERROR] Don't have enough space to allocate this stack \n");
		}
	}
}
