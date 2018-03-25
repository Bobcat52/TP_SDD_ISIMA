#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMAL  "\x1B[0m"
#define ROUGE  "\x1B[31m"
#define VERT  "\x1B[32m"
#define JAUNE  "\x1B[33m"
#define BLEU  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define BLANC  "\x1B[37m"

#include "ZZ_stack.h"
#include "ZZ_queue.h"

int main(int argc, char * argv[])
{
	if(argc == 2)
	{
		/* Declare our two structures */	
		queue_t		* queue;
		stack_t		* stack;
		int 		  errorCode;
		char 		* fileName;

		/* we registered some stack in the Stack directory */
		fileName = argv[1];

		printf("%sI/ Loading the stack from the file %s.%s\n",VERT,fileName,NORMAL);
		
		/* Init our stack */
		stack = initStackFromFile(fileName,&errorCode);

		if(errorCode == 1)
		{
			int i;
			int numberSummit; /* save the number of summit */
			int empty;
			int full;

			empty = 0; /* once a stack is empty, we have to stop the iteration */
			full = 0; /* same thing here*/

			numberSummit = stack->numSummit + 1;

			/* Init our queue */
			queue = initQueue(numberSummit,&errorCode);

			/* Display it to the screen */
			printf("Current stack : ");
			printStack(stack);

			printf("%sII/ Emptying the stack to fill the queue.%s\n",VERT,NORMAL);
			/* We empty our stack and fill in a queue */
			for(i=0;i < numberSummit; i++)
			{
				if(empty == 0 && full == 0)
				{
					typeStack valueStack;

					/* We retrieve the value from the stack */
					pop(stack,&valueStack,&errorCode);

					/* If the stack is not empty, we fill the value to the queue */
					if(errorCode == 1)
					{
						enterQueue(queue,valueStack,&errorCode);

						/* We can't enter the value to the queue because the queue is full */
						if(errorCode == 0)
						{
							fprintf(stderr,"[WARNING] You're trying to push data to a full queue \n");
							full = 1;		
						}
					}
					else /* We can stop iteration */
					{
						fprintf(stderr,"[WARNING] You're trying to remove data from an empty stack \n");
						empty = 1;
					}
				}
			}

			empty = 0; /* reinit empty and full */
			full = 0;
			printf("%sIII/ Emptying the queue to fill the stack.%s\n",VERT,NORMAL);
			for(i=0;i < numberSummit; i++)
			{
				if(empty == 0 && full == 0)
				{
					queueType valueQueue;

					/* We retrieve the value from the queue */
					valueQueue = leaveQueue(queue,&errorCode);

					/* If the queue is not empty, we fill the value to the stack */
					if(errorCode == 1)
					{
						push(stack,valueQueue,&errorCode);

						/* We can't push the value because the stack is full */
						if(errorCode == 0)
						{
							fprintf(stderr,"[WARNING] You're trying to push data to a full stack \n");
							full = 1;		
						}
					}
					else
					{
						fprintf(stderr,"[WARNING] You're trying to remove data from an empty queue \n");
						empty = 1;
					}
				}
			}

			printf("%sIV/ Result : %s\n",VERT,NORMAL);

			/* Once it's done, we can print the reversed stack */
			printf("Reversed stacked : ");
			printStack(stack);

			/* And of course, don't forget to free the stack and the queue */
			freeStack(stack);
			freeQueue(queue);
		}
		else
		{
			if(errorCode == -1)
			{
				fprintf(stdout,"%s[ERROR] Can't open the file %s !%s\n",ROUGE,fileName,NORMAL);
			}
			else
			{
				fprintf(stdout,"%s[ERROR] Don't have enough space to allocate this stack%s\n",ROUGE,NORMAL);
			}
		}
	}
	else
	{
		fprintf(stdout,"%s[ERROR] Too few arguments ! %s\n",ROUGE,NORMAL);
	}
	return(EXIT_SUCCESS);
}
