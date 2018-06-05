#include "ZZ_tree.h"
#include "ZZ_stack.h"
#include "ZZ_queue.h"

noeud_t* createNode(char courant)
{

	noeud_t* node = malloc(sizeof(noeud_t));

	node->value = courant;

	node->hLink = NULL;
	node->vLink = NULL;

	return(node);
}
void repPostFixe(noeud_t* a, int* errorCode)
{
   
    noeud_t*  cur = a;
    stack_t*  stack = NULL;
    typeStack elmt;
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

            printf("(%c,0) ", cur->value);

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

                    printf("(%c,%d) ", cur->value, elmt.nb_fils); /* we display the father and its number of son */


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
                        if (!isStackEmpty(stack) && stack->numSummit != 1) /* Does it have a father? */
                        {
                            pop(stack,&elmt,errorCode);
                            cur = elmt.adr; /* the pointer  points to its father */
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
noeud_t createTree(char *formatage)
{
	/* Init our Stack */
	stack_t* stack;
	int errorCode;
	stack = initStack(100,&errorCode); 

	int size = strlen(formatage);


	/* create the head of the tree */ 
 	noeud_t head;
	noeud_t* prec = &head;

	char courant;
	int index;
	index = 0;
	
	int fini = 0;
	int parentOpen = 0; /* Indique si le caractère précèdent était une parenthèse ouverte */
	int comma = 0;
	int numberOfNode = 0;

	int i = 0;

	for(i = 0; i < size;i++)
	{
		courant = formatage[index]; /* On récupère le premier caractère */
		
		switch(courant)
		{
			case 40: /* "(" */
			{
				parentOpen = 1;
				break;
			}
			case 41: /* ")" */
			{
				if(!isStackEmpty(stack)) /* If the stack is not empty */
				{
					T_elmtPile elmtPile;

					pop(stack,&elmtPile,&errorCode);

					prec = elmtPile.adr;
					printf("noeud dépilé : %c \n", prec->value);
				}
				else
				{
					fini = 1;
				}

				break;
			}
			case 44: /* "," */
			{
				comma = 1;
				parentOpen = 0;
				break;
			}
			default:
			{
				numberOfNode++;

				/* Creation of the node */
				noeud_t* node = createNode(courant);

				if(parentOpen == 1)
				{
					prec->vLink = node;

					T_elmtPile elmtPile;
					elmtPile.adr = prec;
					elmtPile.nb_fils = 0;

					push(stack, elmtPile , &errorCode);
					printf("%d taille de la pile \n",stack->numSummit);
				}
				else /* We have a comma or a closed parenthesis */
				{
					/* Create the vertical link */
					prec->hLink = node;
				}
				/* move the pointer to the next node */	
				prec = node;
				comma = 0;
				parentOpen = 0;
				break;
			}
			
			
		}
		index++;
	}

	return(head);
}
noeud_t *  rechercher(noeud_t * a, char v, int * errorCode)
{
    queue_t* file = NULL;
    int      end = 1;
    noeud_t* cur = a;
	queueType elmt;


    *errorCode = 0;
    file = initQueue(100,errorCode);

	printf("1 \n");
    if (cur != NULL)
    {
        while ( (cur != NULL && (!end) ) || cur->value != v) /* while we don't have found the value v or we don't have gone through the entire tree */
        {
			printf("2 \n");
            if (cur->vLink != NULL) /* if it has a son */
            {
				printf("3 \n");
                elmt.adr = cur; /* we stock the current element then we pull it on the queue */
                enterQueue(file,elmt,errorCode);
            }
            if (cur->hLink != NULL) /* if it has a brother */
            {
				printf("4 \n");
				if(cur == NULL)
				{
					printf("null\n");
				}	
                cur = cur->hLink; /* the pointer points to its brother */
            }
            else /* if it doesn't have a brother */
            {
				printf("5 \n");
                if(!isQueueEmpty(file))				
                {
					printf("6 \n");
                    cur = file->base->adr; /* we go back on the first element threaded */
                    elmt = leaveQueue(file,errorCode); 
					printf("7 \n");
					cur = cur->vLink; /* the pointer points to its son */
                }
                else /* the queue is empty, there isn't son */
                {
                    end = 0; /* the path of the tree is finished */
                }
            }
        }
    }
    return cur ;
}

void insertNode(noeud_t* v,char w, int* errorCode)  
{
	noeud_t* cur=v;
	noeud_t* prec=NULL;

	*errorCode=0;
	if (cur!=NULL)       /*if the tree is not empty */
	{
		if (cur->vLink == NULL)  /* so there isn't son */
		{
			cur->vLink=(noeud_t *)malloc(sizeof(noeud_t));
			cur = cur->vLink;
			cur->value= w;
			cur->hLink=NULL;
			cur->vLink=NULL;
			*errorCode=1;
			
		}
		else                     /* alors il a au moins un fils */
		{
			prec = cur;
			cur = cur->vLink;
			if (cur->value < w)   /* le premier fils n'est pas avant l'element dans l'alphabet */
			{
				while(cur != NULL && cur->value <w) /* On cherche ou inserer le fils */
				{
					prec = cur;
					cur = cur->hLink;
				}
				if(cur == NULL) /* on est arrive a la fin des fils, on l'insere donc a la fin*/
				{
					prec->hLink = (noeud_t *)malloc(sizeof(noeud_t)); /* on cree le fils*/
					prec->hLink->value = w;
					prec->hLink->vLink = NULL;
					prec->hLink->hLink = NULL;
					*errorCode=1;

				}
				else                 /*on insere le fils au milieu de ses freres;*/
				{
					if (cur->value != w)  /*le fils w n'existe pas deja */
					{
						prec->hLink = (noeud_t *)malloc(sizeof(noeud_t)); /* on insere le fils w entre 2 freres*/
						prec->hLink->value = w;
						prec->hLink->vLink = NULL;
						prec->hLink->hLink = cur;    /*on relie au frere suivant  */
						*errorCode=1; 
					}
					else /* Sinon le fils w existe deja donc pas besoin de l'inserer*/
					{
						*errorCode=-1;
					}
				
				}
			}
			else
			{
				if (cur->value > w) /* alors on insere le fils en tete */
				{
					prec->vLink = (noeud_t *)malloc(sizeof(noeud_t)); /* on insere le fils w entre 2 freres*/
					prec->vLink->value = w;
					prec->vLink->vLink = NULL;
					prec->vLink->hLink = cur;    /* on relie au frere suivant  */
					*errorCode=1; 
				}
				else   /* le premier fils est deja w donc pas besoin de l'inserer */
				{
					*errorCode=-1;
				}
			}

		}
	}
}
noeudModified_t copyTree(noeud_t arbre)
{

    noeud_t*  cur = arbre.vLink;
	noeud_t* pere = NULL;
	/* head of the new tree */
	noeudModified_t treeCopy;
	noeudModified_t curTreeCopy = treeCopy;


    int end = 1;
    
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
                    {
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
