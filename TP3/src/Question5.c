#include "../include/Question5.h"


void repPostFixeBis(noeudModified_t a)
{
   
    noeudModified*  cur= a.vLink; /*we don't initialize on the first element but on the second, because the first element don't have value */
    int             end = 1;
    typeStack       elmt;
    int             processed = 0;
    
    if(cur != NULL) /* if the tree is not empty */               										
    {
		/* while we don't have gone throught the entire tree */ 
        while(cur != NULL && end != 0)   										
        {	
			if(processed==1) /* we have already processed this element */
			{
				printf(" %c ",cur->value); /* we display the element */
				if(cur->hLink!=NULL) /* Has it a brother ? */
				{
					cur = cur->hLink ;
					processed = 0; /* this element hasn't been processed yet */
				}
				else          /* we pull up the tree if it is possible */
				{
					if(cur->papa != NULL) /* it has a father */
					{
						cur = cur->papa;
					}
					else
					{
						end=0;
					}
				}
			}
			else
			{
				/* while there is a son */
				while(cur != NULL && cur->vLink != NULL)  						
                {
                    cur = cur->vLink; /* the pointer points to its son */
				}

				printf(" %c ", cur->value);
			
			
				if (cur->hLink != NULL) /*if it has a brother */
				{
					cur = cur->hLink; /* the pointer points to its brother */
				}
				else /* if there isn't a brother we pull up the tree if it's possible */
				{   
					if (cur->papa != NULL) /* if the stack is not empty we can pull up in the tree */
					{
                        cur = cur->papa;
                        processed = 1;
					}
					else
					{
						end = 0;
					}
				}
			}
		}
	}
	printf("\n");
}
    

