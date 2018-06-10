#include "ZZ_tree.h"

#include "ZZ_queue.h"

noeud_t* createNode(char courant)
{

	noeud_t* node = malloc(sizeof(noeud_t));

	node->value = courant;

	node->hLink = NULL;
	node->vLink = NULL;

	return(node);
}


void incrementNbSon(stack_t* stack, typeStack elmt, int*errorCode)
{
	
	pop(stack,&elmt, errorCode);
	
	elmt.nb_fils+=1; /* the father has one more son */

	push(stack,elmt,errorCode);
}

void pushBis(stack_t* stack, typeStack elmt, int* errorCode, noeud_t* cur)
{
	elmt.adr = cur;
	elmt.nb_fils = 1;
	push(stack, elmt, errorCode);	
	
}



void repPostFixe(noeud_t* a, int* errorCode)
{
   
    noeud_t*  cur = a;
    stack_t*  stack = NULL;
    typeStack elmt;
	
    int       end = 1;
    int wasInStack = 0;
    *errorCode = 0;
    stack = initStack(100, errorCode);
    
    if(cur != NULL) /* if the tree is not empty */               										
    {
		/* while we don't have gone throught the entire tree */ 
        while(cur != NULL && end != 0)   										
        {	
			if(wasInStack==1) /* we have already processed this element */
			{
				printf("(%c,%d)",cur->value,elmt.nb_fils); /* we display the element */
				if(cur->hLink!=NULL) /* Has it a brother ? */
				{
					cur = cur->hLink ;
					if (!isStackEmpty(stack)) /* if the stack is not empty */
					{	
						incrementNbSon(stack,elmt,errorCode);
					}
					wasInStack = 0; /* this element hasn't been processed yet */
				}
				else          /* we pull up the tree if it is possible */
				{
					if(!isStackEmpty(stack))
					{
						pop(stack,&elmt,errorCode);
						cur = elmt.adr;
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
					pushBis(stack,elmt,errorCode,cur);
		
					cur = cur->vLink; /* the pointer points to its son */
				}

				printf("(%c,0)", cur->value);
			
			
				if (cur->hLink != NULL) /*if it has a brother */
				{
					cur = cur->hLink; /* the pointer points to its brother */

					if (!isStackEmpty(stack)) /* if the stack is not empty */
					{	
						incrementNbSon(stack,elmt,errorCode);
					}
					
				}
				else /* if there isn't a brother we pull up the tree if it's possible */
				{   
					if (!isStackEmpty(stack)) /* if the stack is not empty we can pull up in the tree */
					{
						pop(stack,&elmt,errorCode);

						cur = elmt.adr; /* the pointer points to its father */
						
						wasInStack = 1;
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
    
    noeud_t* cur = a;
	queueType elmt;


    *errorCode = 0;
    file = initQueue(100,errorCode);

    if (cur != NULL)
    {
        while ( cur != NULL && cur->value != v) /* while we don't have found the value v or we don't have gone through the entire tree */
        {

            if (cur->vLink != NULL) /* if it has a son */
            {
				
                elmt.adr = cur; /* we stock the current element then we pull it on the queue */
                enterQueue(file,elmt,errorCode);
            }
            if (cur->hLink != NULL) /* if it has a brother */
            {
                cur = cur->hLink; /* the pointer points to its brother */
            }
            else /* if it doesn't have a brother */
            {
				
                if(!isQueueEmpty(file))				
                {
					
                    cur = file->base->adr; /* we go back on the first element threaded */
                    elmt = leaveQueue(file,errorCode); 
					
					cur = cur->vLink; /* the pointer points to its son */
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
	if (cur!=NULL)       /*if the subtree exists */
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
			if (cur->value < w)   /* le premier fils est  avant l'element dans l'alphabet */
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
				else     /*we insert the element in the middle of its brothers*/
				{
					if (cur->value != w)  /*the element hasn't created yet*/
					{
						prec->hLink = (noeud_t *)malloc(sizeof(noeud_t)); /* we insert the element between 2 brothers*/
						prec->hLink->value = w;
						prec->hLink->vLink = NULL;
						prec->hLink->hLink = cur;    /*we link the element to the next brother  */
						*errorCode=1; 
					}
					else /* the element is already created so no need to insert it*/
					{
						*errorCode=-1;
					}
				
				}
			}
			else  /*if the element is before the first son in the alphabet */
			{
				if (cur->value > w) /* so we insert the element into the head */
				{
					prec->vLink = (noeud_t *)malloc(sizeof(noeud_t)); /* we insert the element between its 2 brothers*/
					prec->vLink->value = w;
					prec->vLink->vLink = NULL;
					prec->vLink->hLink = cur;    /* we link the element to the next brother  */
					*errorCode=1; 
				}
				else   /* the first son is already the element, no need to insert it */
				{
					*errorCode=-1;
				}
			}

		}
	}
}
newNode_t* createModifiedNode(noeud_t* cur,newNode_t* pere)
{
	newNode_t* node = malloc(sizeof(newNode_t));

	node->value = cur->value;
	node->vLink = NULL;
	node->hLink = NULL;

	node->papa = pere;

	return(node);
}

newNode_t* copyTree(noeud_t* arbre,int* errorCode)
{
	newNode_t* newTree = malloc(sizeof(newNode_t));

	newTree->papa = NULL;
	newTree->hLink = NULL;
	newTree->vLink = NULL;
	
	newNode_t* currNewTree = newTree;
	newNode_t* father = currNewTree;

    noeud_t*  cur = arbre;
    stack_t*  stack = NULL;
    typeStack elmt;
	
    int end = 1;
    int wasInStack = 0;

    *errorCode = 0;
    stack = initStack(100, errorCode);
    
    if(cur->vLink != NULL) /* if the tree is not empty */               										
    {
		/* while we don't have gone throught the entire tree */ 
        while(cur != NULL && end != 0)   										
        {	
			if(cur->vLink != NULL && wasInStack == 0)
			{
				/* while there is a son */
				do					
				{   
					cur = cur->vLink;

					currNewTree->vLink = createModifiedNode(cur,father);
					currNewTree = currNewTree->vLink;

					if(cur->vLink != NULL)
					{
						pushBis(stack,elmt,errorCode,cur);
						father = currNewTree;
					}
				

				}
				while(cur != NULL && cur->vLink != NULL && wasInStack == 0);
			}
			wasInStack = 0;


			if (cur->hLink != NULL) /*if it has a brother */
			{
				cur = cur->hLink;
				currNewTree->hLink = createModifiedNode(cur,father);
				currNewTree = currNewTree->hLink;

				if(cur->vLink != NULL)
				{
					pushBis(stack,elmt,errorCode,cur);
					father = currNewTree;
				}
			}
			else /* if there isn't a brother we pull up the tree if it's possible */
			{   

				if(!isStackEmpty(stack))
				{
					pop(stack,&elmt,errorCode);
					cur = (elmt.adr); 
					wasInStack = 1;

					currNewTree = currNewTree->papa; /* came back to the father */
					father = currNewTree->papa;
				}

				if(isStackEmpty(stack) && cur->hLink == NULL)
				{
					end = 0;
				}
			}
		}
	}
	
	return(newTree);
}
void repPostFixeBis(newNode_t a, int* errorCode)
{

    newNode_t*  cur = a.vLink; /*we don't initialize on the first element but on the second, because the first element don't have value */
    int       end = 0;
    int 	  backFromFather = 0;

    *errorCode=0;
    
    if(cur != NULL) /* if the tree is not empty */
    {
        while(cur  != NULL && end == 0)/* while we don't have gone throught the entire tree */ 
        {
			while(cur != NULL && cur->vLink != NULL && backFromFather == 0)  /* while there is a son */
			{   
				cur = cur->vLink; /*the pointer points to its son */
			}
			
			if(backFromFather == 0)
			{
           		printf("| %c | ", cur->value);
			}

            backFromFather = 0;
			
			
			if (cur->hLink != NULL) /*if it has a brother */
            {
                cur = cur->hLink; /* the pointer points to its brother */
            }
            else /* if there isn't a brother we pull up the tree if it's possible */
            {   
				while (cur->papa != NULL && cur->hLink == NULL) /* if he has a father */
                {
					backFromFather = 1;
                    cur = cur->papa; /* the pointer points to the father */

					if(cur->papa != NULL)
					{
                    	printf("| %c | ", cur->value);
					}
				}

				if(cur->papa == NULL)        
                {	
                    end = 1;
                }
            }
        }
    }
    printf("\n");
}
