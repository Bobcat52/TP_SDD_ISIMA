#include <stdio.h>
#include <stdlib.h>
#include "ZZ_Pile.h"


/* -------------------------------------------------------------------- */
/* initStack        Init a stack properly                	         	*/
/*                                                                      */
/* Inputs :   - p0 is a pointer of the stack                     		*/
/*            - size is the size of the queue 			            	*/
/*	          - errorCode is an integer that stores the result of the 	*/
/*		        function :  -1 - there is an issue while allocating 	*/
/*				                 the queue            		         	*/
/*								                                     	*/
/*			                 0 - there is an issue while allocation the	*/
/*				                 the array in the queue			        */
/*									                                    */
/*			                 1 - Everything went well !                 */
/*                                                                      */
/* Output :  Return the adress of the pointer of the head of the stack  */ 
/* -------------------------------------------------------------------- */

stack_t * initStack(int size, int * errorCode)	
{	
	stack_t * p;   /* we declare a pointer of the stack */
	
	
	*errorCode=-1;
	p = malloc(sizeof(stack_t));	/* we initialize the pointer */

	if (p != NULL)   /* If the pointer is not null we initialize the point stack */
	{
			p->begin = malloc(size*sizeof(typeStack)); /* we initalize the contiguous list which is pointed by the last block of the stack */ 
			*errorCode = 0;
			if ((p->begin)!= NULL)           /* if the previous allocation didn't go wrong */  
			{
					p->sizeMax = size;
					p->numSummit = -1;     /*there is 0 element in the stack but the stack is created so we put -1 */
					*errorCode = 1;           
			}
			else 
			{
				free(p);
				p=NULL;
			}
	}
	
	return p; 
}


/* -------------------------------------------------------------------- */
/* freeStack:        Free a stack properly                	         	*/
/*                                                                      */
/* Inputs :   - p0 is a pointer of the stack                     		*/
/*                                                                      */
/* -------------------------------------------------------------------- */

void freeStack( stack_t * p)
{
	if (p->begin != NULL)  /* if there is a contiguous list, we free the pointer which link the stack to the contigous list */
	{
		free(p->begin);
		
	}
	else          /* so the pointer of the contiguous list is maybe null but we have to free the stack */
	{
		free(p);
	}
	p = NULL;
	
}

/* -------------------------------------------------------------------- */
/* isEmpty:       Check if the stack is empty                	        */
/*                                                                      */
/* Input :   	- p0 is a pointer of the stack                     		*/
/* Output:   	Return  boolean :                                       */
/*                      * 0 if the stack is not isEmpty                 */
/*						* 1 if it is                                    */
/* -------------------------------------------------------------------- */


int estVide(stack_t * p)
{
		return (p->numSummit == -1);  /* if the stack is empty so there is 0 element , so numSummit = -1 */
}

/* --------------------------------------------------------------------- */
/* stack:        Stack a value in the stack                	         	 */
/*                                                                       */
/* Inputs :  	- p0 is a pointer of the stack                     		 */
/*           	- v is a value we want to stack                          */
/*	            - errorCode is an integer that stores the result of the  */
/*		          function :  -1 - there is an issue while allocating 	 */
/*				                 the queue            		         	 */
/*			                   1 - Everything went well !                */
/* --------------------------------------------------------------------- */

void stack (stack_t * p, typeStack v ,int * errorCode)
{		
		*errorCode = -1;
		if (p->numSummit < (p->sizeMax) ) /* if the stack is not full */
		{
				*((p->begin) + (p->numSummit +1)*sizeof(typeStack)) = v; /* we assign to the first free block of the contiguous list the value v */
				p->numSummit += 1;  /* there is a further element in the stack */
				*errorCode = 1;
		}
		
}

/* -------------------------------------------------------------------- */
/* unStack:        Unstack a value from the stack              	        */
/*                                                                      */
/* Inputs :  	- p0 is a pointer of the stack                     		*/
/*           	- *v is the adress of the value                         */
/*			       we want to unstack                                   */
/*	          - errorCode is an integer that stores the result of the 	*/
/*		        function :  -1 - there is an issue while allocating 	*/
/*				                 the queue            		         	*/
/*			                 1 - Everything went well !                 */
/* -------------------------------------------------------------------- */

void unStack ( stack_t * p, typeStack * v, int * errorCode)
{
		*errorCode = -1;
		
		if (!estVide(p))      /* if the stack is not empty so we can unstack */
		{
				*v = *((p->begin) + (p->numSummit)*sizeof(typeStack));  /*  we pick up the value of the last element added and we assign it in a variable */
				p->numSummit -= 1; /* we unstack the last element added so there is one element less stored in the stack */
				errorCode = 1;
		}
}

int main()
{
	stack_t * p;
	int      i, v=2;
	p = NULL;
	p = initPile(3);
	printf(" la pile est initialisée \n ");
	i = estVide(p);
	printf ( "%d\n", i);
	empiler(p , v);
	i = estVide(p);
	printf ( "%d\n", i);
	int val;
	depiler(p, &val);
	printf("%d \n",val);
	
	return 0;
}
