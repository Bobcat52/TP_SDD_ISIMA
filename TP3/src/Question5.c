#include "../include/Question5.h"


void repPostFixeBis(noeud_t* a, int* errorCode)
{
   
    noeud_t*  cur= a;
    typeStack elmt;
    int       end = 1;
    
    *errorCode=0;
    
    
    if(cur != NULL)                                 /* if the tree is not empty */
    {
        while(cur!=NULL && end!=0)                  /* while we don't have gone throught the entire tree */ 
        {
            
            while(cur!=NULL && cur->vLink != NULL)  /* while there is a son */
            {   
                cur = cur->vLink;      				/*the pointer points to its son */
            }
            printf("| %c |", cur->value);
            if (cur->hLink != NULL)                 /*if it has a brother */
            {
                cur = cur->hLink;					/* the pointer points to its brother */
                
            }
            else                                    /* if there isn't a brother we pull up the tree if it's possible */
            {   
				if (cur->pere!=NULL)                /* if he has a father */
                {
                    cur = cur->pere;                /* the pointer points to the father */
                    printf("| %c |", cur->value)
                    if (cur->hLink != NULL)         /* if the father has a brother */
                    {
                        cur = cur->hLink;
                    }
                    else                            /* the father doesn't have a brother */
                    {
                        if (cur->pere!=NULL)        /* Does it have a father? */
                        {
                           cur = cur->pere;    		/* the pointer points to the father */
                        }
                        else               			/* we actually have gone through the entire tree */
                        {
                            end = 0;				/* the path of the tree is finished */
                        }
                    }
                }
				else 								/* he don't have a father, we actually have gone through the entire tree */             
                {	
					
                    end = 0;						/* the path of the tree is finished */
                }
            }
        }
    }
    
}



int main(int argc, char **argv)
{
	
	return 0;
}

