noeudModified_t copyTree(noeud_t arbre, int* errorCode)
{

    noeud_t*  cur = arbre.vLink;
	noeud_t* pere = NULL;
	/* head of the new tree */
	noeudModified_t treeCopy;
	noeudModified_t curTreeCopy = treeCopy;
	typeStack elmt;
	stack_t* stack=NULL;
	
    int end = 1;
    *errorCode = 0;
    stack = initStack(100,errorCode);
    
    if(cur != NULL) /* if the tree is not empty */               										
    {
		/* while we don't have gone throught the entire tree */ 
        while(cur != NULL && end != 0)   										
        {	

            /* while there is a son */
            while(cur != NULL && cur->vLink != NULL)  						
            {   
				/* we create a new block from the current block with a slight change : we add the parent's adress to it */
				noeudModified_t *newBlock = createModifiedNode(cur,pere); 

				pere = cur;
                cur = cur->vLink; /* the pointer points to its son */
				

				curTreeCopy.vLink = newBlock;
				curTreeCopy = newBlock;
            }

            if (cur->hLink != NULL) /*if it has a brother */
            {
				/* we create a new block from the current block with a slight change : we add the parent's adress to it */
				noeudModified_t *newBlock = createModifiedNode(cur,pere); 

                cur = cur->hLink; /* the pointer points to its brother */

				curTreeCopy.hLink = newBlock;
				curTreeCopy = newBlock;
            }
            else /* if there isn't a brother we pull up the tree if it's possible */
            {   
				cur = curTreeCopy.papa; /* we come back to the father */

                if (cur->hLink != NULL) /* if it has a brother */
                {

                    cur = cur->hLink; /* the pointer points to its brother */
                }
                else /* it doesn't have a brother */
                {
                    if (!isStackEmpty(stack) && stack->numSummit != 1) /* Does it have a father? */
                    {void repPostFixe(noeud_t* a, int* errorCode)
{
   
    noeud_t*  cur = a;
    stack_t*  stack = NULL;
    typeStack elmt;
	noeud_t*  racineUltime = derniereRacine(a); 
    int       end = 1;
    
    *errorCode = 0;
    stack = initStack(100, errorCode);
    
    if(cur != NULL) /* if the tree is not empty */               										
    {
		/* while we don't have gone throught the entire tree */ 
        while(cur != NULL && end != 0)   										
        {	

            /* while there is a son */
            while(cur != NULL && cur->vLink != NULL)  						
            {   
                elmt.adr = cur;
                elmt.nb_fils = 1;
                push(stack, elmt, errorCode);	
		
                cur = cur->vLink; /* the pointer points to its son */
            }

           /* printf("(%c,0) ", cur->value);*/
			
            if (cur->hLink != NULL) /*if it has a brother */
            {
                cur = cur->hLink; /* the pointer points to its brother */

                if (!isStackEmpty(stack)) /* if the stack is not empty */
                {	
                    pop(stack,&elmt, errorCode);

                    elmt.nb_fils+=1; /* the father has one more son */

                    push(stack,elmt,errorCode);
                }
            }
            else /* if there isn't a brother we pull up the tree if it's possible */
            {   
				if (!isStackEmpty(stack)) /* if the stack is not empty we can pull up in the tree */
                {
                    pop(stack,&elmt,errorCode);

                    cur = elmt.adr; /* the pointer points to its father */

               /*     printf("(%c,%d) ", cur->value, elmt.nb_fils);*/ /* we display the father and its number of son */


                    if (cur->hLink != NULL) /* if it has a brother */
                    {
                        if (!isStackEmpty(stack))  /* Has it a father?*/
                        {
							/* TODO : faire une fonction générique pour le pop/push */
                            pop(stack,&elmt,errorCode);
                            elmt.nb_fils += 1; /* the father has one more son */
                            push(stack,elmt,errorCode);
                        }

                        cur = cur->hLink; /* the pointer points to its brother */
                    }
                    else /* it doesn't have a brother */
                    {
                        if (!isStackEmpty(stack)) /* Does it have a father? */
                        {
                            pop(stack,&elmt,errorCode);
                            cur = elmt.adr; /* the pointer  points to its father */
							if(cur == racineUltime)
							{
								end = 0;
								/*printf("(%c,%d) ", cur->value, elmt.nb_fils); *//* we display the father and its number of son */
	                    	 }
						}
                        else /* we actually have gone through the entire tree */		
                        {
                            end = 0;	/* the path of the tree is finished */
                        }
                    }
                }
				else /* he doesn't have a father, we actually have gone through the entire tree */  
                {	
					
                    end = 0; /* the path of the tree is finished */
                }
            }
        }
    }
    
	printf("\n");
}
                        pop(stack,&elmt,errorCode);
                        cur = elmt.adr; /* the pointer  points to its father */
                    }
                    else /* we actually have gone through the entire tree */		
                    {
                        end = 0;	/* the path of the tree is finished */
                    }
                }
       

            }
        }
    }
    
}

noeudModified_t* createModifiedNode(noeud_t* cur,noeud_t* pere)
{
    noeudModified_t* newBlock = malloc(sizeof(noeudModified_t));
	newBlock->value = cur->value;
	newBlock->vLink = cur->vLink;
	newBlock->hLink = cur->hLink;
	newBlock->papa = pere;

	return(newBlock);
}



