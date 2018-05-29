
#include "../include/ZZ_postfixe.h"


stack_t * initStack(int size, int * errorCode)	
{	
	stack_t * p;   /* we declare a pointer of the stack */
	
	*errorCode=-1;

	p = malloc(sizeof(stack_t));	/* we initialize the pointer */

	if (p != NULL)   /* If the pointer is not null we initialize the point stack */
	{
			p->begin = malloc(size * sizeof(typeStack)); /* we initalize the contiguous list which is pointed by the last block of the stack */ 
			*errorCode = 0;

			if ((p->begin)!= NULL)           /* if the previous allocation went wrong */  
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

int isStackEmpty(stack_t * p)
{
		return (p->numSummit == -1);  /* if the stack is empty so there is 0 element , so numSummit = -1 */
}

/* --------------------------------------------------------------------- */
/* push:            Push a value in the stack                	      	 */
/*                                                                       */
/* Inputs :  	- p0 is a pointer of the stack                     		 */
/*           	- v is a value we want to stack                          */
/*	            - errorCode is an integer that stores the result of the  */
/*		          function :  0 - the stack is full !				 	 */
/*				                 				       		         	 */
/*			                  1 - Everything went well ! 				 */
/* --------------------------------------------------------------------- */
void push(stack_t * p, typeStack v ,int * errorCode)
{		
		*errorCode = 0;

		if (p->numSummit+1 <= (p->sizeMax) ) /* if the stack is not full */
		{
				p->begin[p->numSummit+1] = v; /* we assign to the first free block of the contiguous list the value v */
				p->numSummit += 1;  /* there is a further element in the stack */
				*errorCode = 1;
		}
		
}

/* ----------------------------------------------------------------------*/
/* pop:        Unstack a value from the stack              	             */
/*                                                                       */
/* Inputs :  	- p0 is a pointer of the stack                     		 */
/*           	- *v is the adress of the value                          */
/*			       we want to unstack                                    */
/*	            - errorCode is an integer that stores the result of the  */
/*		          function :  0 - the stack is empty, nothing to         */
/*				                 retrieve           		         	 */
/*																		 */
/*			                  1 - Everything went well !                 */
/* --------------------------------------------------------------------- */
void pop( stack_t * p, typeStack * v, int * errorCode)
{
		*errorCode = 0;
		
		if (!isStackEmpty(p))      /* if the stack is not empty so we can unstack */
		{
				*v = p->begin[p->numSummit];  /*  we pick up the value of the last element added and we assign it in a variable */
				p->numSummit -= 1; /* we unstack the last element added so there is one element less stored in the stack */
								
				*errorCode = 1;
		}
}


void repPostFixe(noeud_t* a, int* errorCode)
{
   
    noeud_t*  cur= a;
    stack_t*  stack = NULL;
    typeStack elmt;
    int       end = 1;
    
    *errorCode=0;
    stack = initStack(100, errorCode);
    
    if(cur != NULL)                   // si l'arbre n'est pas vide
    {
        while(cur!=NULL && end!=0)   // Tant qu'on a pas parcourru tout l'arbre 
        {
            
            while(cur!=NULL && cur->vLink != NULL)  // Tant qu'il existe un fils
            {   
                elmt.adr = cur;
                elmt.nb_fils = 1;
                push(stack, elmt, errorCode);
                cur = cur->vLink;      
            }
            printf("| %c | 0 |", cur->value);
            if (cur->hLink != NULL)  //Si l'élément possède un frere
            {
                cur = cur->hLink;
                if (!isStackEmpty(stack))
                {
                    pop(stack,&elmt, errorCode);
                    elmt.nb_fils+=1;
                    push(stack,elmt,errorCode);
                }
            }
            else             // s'il n'a pas de frere alors on remonte dans l'arbre si cela est possible
            {   
				if (!isStackEmpty(stack)) //si la pile est non vide, on peut remonter dans l'arbre
                {
                    pop(stack,&elmt,errorCode);
                    cur = elmt.adr;                        // on fait pointer le pointeur vers le pere
                    printf("| %c | %d |", cur->value, elmt.nb_fils);
                    if (cur->hLink != NULL)                // si le père possède un frere
                    {
                        if (!isStackEmpty(stack))   // a-t-il un pere? 
                        {
                            cur = cur->hLink;
                            pop(stack,&elmt,errorCode);
                            elmt.nb_fils+=1;
                            push(stack,elmt,errorCode);
                        }
                        cur = cur->hLink;
                    }
                    else                    // le pere n'a pas de frere
                    {
                        if (!isStackEmpty(stack))  // a-t-il un pere?
                        {
                            pop(stack,&elmt,errorCode);
                            cur = elmt.adr;    // on fait pointer le pointeur vers le pere
                        }
                        else               //on a parcouru tout l'arbre
                        {
                            end = 0;
                        }
                    }
                }
				else              //on a parcouru tout l'arbre
                {	
					
                    end = 0;
                }
            }
        }
    }
    
}
int main()
{
    noeud_t*  arbre;
    
    stack_t* stack;
    int      errorCode;
    arbre = (noeud_t *)malloc(sizeof(noeud_t));
    arbre->value = 'a';
    arbre->vLink = (noeud_t *)malloc(sizeof(noeud_t));
    arbre->hLink = (noeud_t *)malloc(sizeof(noeud_t));
    arbre->vLink->value = 'b';
    arbre->vLink->vLink = NULL;
    arbre->vLink->hLink = NULL;
    arbre->hLink->value = 'c';
    arbre->hLink->vLink = NULL;
    arbre->hLink->hLink = NULL;
    printf("Début du test: \n");
    repPostFixe(arbre,&errorCode);
    return 0;
}
