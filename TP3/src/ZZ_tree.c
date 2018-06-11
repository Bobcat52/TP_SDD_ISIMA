/* ########################################################## */
/* file's name : ZZ_tree.c				                      */
/*							                                  */
/* Author : Mathieu Boutin & Jeremy Morceaux                  */
/* Date : June 2018						                      */
/*							                                  */
/* This file contains source from the ZZ_tree.h		          */
/*							                                  */
/* Desc : this file create some function to work with         */
/*        tree							 		      		  */
/* ########################################################## */

#include "ZZ_tree.h"
#include "ZZ_queue.h"


/* ------------------------------------------------------------------------ */
/* createNode    create a node for the basic tree					   		*/
/*                        						    						*/
/*									   										*/
/* Input: 	- courant : the character we want to insert in the tree			*/
/*									     				    				*/
/* Output : the node freshly created										*/
/* ------------------------------------------------------------------------ */
noeud_t* createNode(char courant)
{
	/* Create a new node */
	noeud_t* node;

	node = (noeud_t*)malloc(sizeof(noeud_t));

	/* set its new value */
	node->value = courant;
	node->hLink = NULL;
	node->vLink = NULL;

	return(node);
}

/* ------------------------------------------------------------------------ */
/* incrementNbSon    create a node for the basic tree		   				*/
/*                        						    						*/
/*									   										*/
/* Input: 	- stack : the stack that has the node we want to increment its  */
/*					  number of son											*/
/*		    - elmt: will store the element that will be popped 				*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			1 : so far so good !	     				    				*/
/* 			0 : problem 							    					*/
/* ------------------------------------------------------------------------ */
void incrementNbSon(stack_t* stack, typeStack elmt, int*errorCode)
{
	/* get the node by popping it from the stack */
	pop(stack,&elmt, errorCode);
	
	/* change its number of son */
	elmt.nb_fils+=1;

	/* push it to its former place */
	push(stack,elmt, errorCode);
}

/* ------------------------------------------------------------------------ */
/* pushBis    push a new element to the stack	   							*/
/*                        						    						*/
/*									   										*/
/* Input: 	- stack : the stack that has the node we want to push			*/
/*		    - elmt: will store the element that will be pushed 				*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			1 : so far so good !	     				    				*/
/* 			0 : problem 							    					*/
/*			- cur : the actual element that will be pushed					*/
/* ------------------------------------------------------------------------ */
void pushBis(stack_t* stack, typeStack elmt, int* errorCode, noeud_t* cur)
{
	/* function to add a new element to a stack */
	elmt.adr = cur;
	elmt.nb_fils = 1;
	push(stack, elmt, errorCode);	
	
}

/* ------------------------------------------------------------------------ */
/* repPostFixe    display the postfix notation of a tree 					*/
/*                        						    						*/
/*									   										*/
/* Input: 	- tree : the pointer to the tree								*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			1 : so far so good !	     				    				*/
/* 			0 : problem 							    					*/
/*																			*/
/* ------------------------------------------------------------------------ */
void repPostFixe(noeud_t* tree, int* errorCode)
{
   
	noeud_t*  cur;
	stack_t*  stack;

	typeStack elmt;
	
	int       end;
	int	      wasInStack;
	int       errorCodeStack;

	*errorCode = 0;

	cur = tree;
	stack = initStack(SIZE_STACK, &errorCodeStack);

	end = 1;
	wasInStack = 0;

	/* the stack is well initialized */
	if(errorCodeStack == 1)
	{
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
							incrementNbSon(stack,elmt,&errorCodeStack);

							if(errorCodeStack != 1) /* stop the algorithm if we had a problem with the stack */
							{
								end = 1;
							}
						}
						wasInStack = 0; /* this element hasn't been processed yet */
					}
					else          /* we pull up the tree if it is possible */
					{
						if(!isStackEmpty(stack))
						{
							pop(stack,&elmt,&errorCodeStack);

							if(errorCodeStack != 1) /* stop the algorithm if we had a problem with the stack */
							{
								end = 1;
							}
							else /* otherwise, we can continue what we were doing */
							{
								cur = elmt.adr;
							}
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
						pushBis(stack,elmt,&errorCodeStack,cur);

						if(errorCodeStack != 1) /* stop the algorithm if we had a problem with the stack */
						{
							end = 1;
						}

						cur = cur->vLink; /* the pointer points to its son */
					}

					printf("(%c,0)", cur->value);
				
					if (cur->hLink != NULL) /*if it has a brother */
					{
						cur = cur->hLink; /* the pointer points to its brother */

						if (!isStackEmpty(stack)) /* if the stack is not empty */
						{	
							incrementNbSon(stack,elmt,&errorCodeStack);

							if(errorCodeStack != 1) /* stop the algorithm if we had a problem with the stack */
							{
								end = 1;
							}
						}
						
					}
					else /* if there isn't a brother we pull up the tree if it's possible */
					{   
						if (!isStackEmpty(stack)) /* if the stack is not empty we can pull up in the tree */
						{
							pop(stack,&elmt,&errorCodeStack);

							if(errorCodeStack != 1) /* stop the algorithm if we had a problem with the stack */
							{
								end = 1;
							}
							else
							{
								cur = elmt.adr; /* the pointer points to its father */
								wasInStack = 1;
							}
						}
						else
						{
							end = 0;
						}
					}
				}
			}
		}
		freeStack(stack); /* don't forget to dealloc the stack */
		printf("\n");

	}
	else
	{
		*errorCode = 1; /* failed to initialized stack */
	}
	
}

/* ------------------------------------------------------------------------ */
/* createTree    create a basic tree from a string	   						*/
/*                        						    						*/
/*									   										*/
/* Input: 	- treeString : the string that is used to build the tree		*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			1 : so far so good !	     				    				*/
/* 			0 : problem 							    					*/
/*																			*/
/* ------------------------------------------------------------------------ */
noeud_t* createTree(char *treeString,int* errorCode)
{
	/* Init our Stack */
	stack_t* stack;
	int 	 errorCodeStack;
	int 	 size;
	
 	noeud_t*  head = malloc(sizeof(noeud_t)); /* create the head of the tree */ 
	noeud_t* prec;

	char     courant;
	int      index; /* index will go throught all the char* format */
	int      parentOpen; /*indicate if the previous character was a parenthesis */
	int 	 fini;

 	size = strlen(treeString);

	head->value = '!';
	head->vLink = NULL;
	head->hLink = NULL;
	prec = head;
	index = 0;
	parentOpen = 0;
	stack = initStack(SIZE_STACK,&errorCodeStack); 
	fini = 0;
	*errorCode = 0;
	
	if(errorCodeStack == 1)
	{
		while(index < size && fini == 0)
		{
			courant = treeString[index]; /* get the new character to process */
			
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

						pop(stack,&elmtPile,&errorCodeStack);
						if(errorCodeStack == 0)
						{
							fini = 1;
							*errorCode = 1;
						}
						else
						{
							prec = elmtPile.adr;
						}
					}
					else
					{
						fini = 1;
					}

					break;
				}
				case 44: /* "," */
				{
					parentOpen = 0;
					break;
				}
				default:
				{
					/* Creation of the node */
					noeud_t*   node;
					T_elmtPile elmtPile;

					node = createNode(courant);

					if(parentOpen == 1)
					{
						prec->vLink = node;

						elmtPile.adr = prec;
						elmtPile.nb_fils = 0;

						push(stack, elmtPile , &errorCodeStack);
						if(errorCodeStack == 0) /* problem during push, we need to stop right here */
						{
							fini = 1;
							*errorCode = 1;
						}

					}
					else /* We have a comma or a closed parenthesis */
					{
						/* Create the vertical link */
						prec->hLink = node;
					}

					/* move the pointer to the next node */	
					prec = node;
		
					parentOpen = 0;
					break;
				}
				
				
			}
			index++;
		}
		freeStack(stack);
	}
	else
	{
		*errorCode = 1;
	}

	/* if the creation went wrong, we need to free the partial tree here */
	if(*errorCode == 1)
	{
		freeTree(head->vLink,&errorCodeStack);
	}

	return(head);
}

/* ------------------------------------------------------------------------ */
/* rechercher    find the node with need to insert the new node	   			*/
/*                        						    						*/
/*									   										*/
/* Input: 	- tree : the pointer to the tree								*/
/*		    - v: the character of the node we search						*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			1 : so far so good !	     				    				*/
/* 			0 : problem 							    					*/
/*																			*/
/* ------------------------------------------------------------------------ */
noeud_t *  rechercher(noeud_t * tree, char v, int * errorCode)
{
	int       errorCodeQueue; /* indicates if we had a problem with the queue */
	queue_t*  file;
	noeud_t*  cur;
	queueType elmt;
	int 	  end;

	*errorCode = 0;

	/* init a queue */
	file = initQueue(SIZE_STACK,&errorCodeQueue);
	cur = tree;
	end = 0;

	/* if the initialization of the queue went good */
	if(errorCodeQueue == 1) 
	{
		/* if the three is not empty */
		if (cur != NULL)
		{
			while ( cur != NULL && cur->value != v && end == 0) /* while we don't have found the value v or we don't have gone through the entire tree */
			{

				if (cur->vLink != NULL) /* if it has a son */
				{
					
					elmt.adr = cur; /* we stock the current element then we pull it on the queue */
					enterQueue(file,elmt,&errorCodeQueue);

					/* we had a problem with the queue -> exit */
					if(errorCodeQueue != 1)
					{
						*errorCode = 1;
						end = 1;
					}
				}
				if (cur->hLink != NULL && end == 0) /* if it has a brother */
				{
					cur = cur->hLink; /* the pointer points to its brother */
				}
				else /* if it doesn't have a brother */
				{
					
					if(!isQueueEmpty(file))				
					{
						
						cur = file->base->adr; /* we go back on the first element threaded */
						elmt = leaveQueue(file,&errorCodeQueue); 

						/* we had a problem with the queue -> exit */
						if(errorCodeQueue != 1)
						{
							*errorCode = 1;
							end = 1;
						}
						else
						{
							cur = cur->vLink; /* the pointer points to its son */
						}
					}
					else
					{
						end = 1;
						*errorCode = 1;
					}
					
				}
			}
		}

		freeQueue(file);
	}
	else
	{
		*errorCode = 1;
	}

	return cur;
}

/* ------------------------------------------------------------------------ */
/* createNodeForInsertion    create a node for the basic tree		   		*/
/*                        						    						*/
/*									   										*/
/* Input: 	- w : the character we want to insert in the tree				*/
/*	     	- horizontal: horizontal node									*/
/*									     				    				*/
/* Output : the node freshly created										*/
/* ------------------------------------------------------------------------ */
noeud_t* createNodeForInsertion(char w,noeud_t *horizontal)
{
	/* Create a node for the insertNode function */
	noeud_t* temp;
	temp =  (noeud_t *)malloc(sizeof(noeud_t));

	temp->value = w;
	temp->hLink = horizontal;
	temp->vLink = NULL;

	return(temp);
}

/* ------------------------------------------------------------------------ */
/* insertNode    insert a node in the basic tree					   		*/
/*                        						    						*/
/*									   										*/
/* Input :  - v : pointer to the tree              							*/
/*	     	- w : the character we want to insert in the tree				*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			0 : so far so good !	     				    				*/
/* 			1 : problem 							    					*/
/*																			*/
/* ------------------------------------------------------------------------ */
void insertNode(noeud_t* tree,char w, int* errorCode)  
{
	/* declares some variable to go through the tree */
	noeud_t* cur; 
	noeud_t* prec; 

	cur = tree;
	*errorCode = 0;
	prec = NULL;

	/*if the subtree exists */
	if (cur != NULL) 
	{
		if (cur->vLink == NULL)  /* so there isn't son */
		{
			cur->vLink= createNodeForInsertion(w,NULL);
			cur = cur->vLink;

		}
		else /* then he has at least one son */
		{
			prec = cur;
			cur = cur->vLink;
			if (cur->value < w)   /* Insert the son in the alphabetical order */
			{
				while(cur != NULL && cur->value <w) /* We search where to insert the son */
				{
					prec = cur;
					cur = cur->hLink;
				}
				if(cur == NULL) /*went through all the sons, we can insert it at the end */
				{
					prec->hLink = createNodeForInsertion(w,NULL);

				}
				else     /*we insert the element in the middle of its brothers*/
				{
					if (cur->value != w)  /*the element hasn't created yet*/
					{
						prec->hLink = createNodeForInsertion(w,cur); /* link it to the next brother */
					}
					else /* the element is already created so no need to insert it*/
					{
						*errorCode = 1;
					}
				
				}
			}
			else  /*if the element is before the first son in the alphabet */
			{
				if (cur->value > w) /* so we insert the element into the head */
				{
					prec->vLink = createNodeForInsertion(w,cur); /* link it to the next brother */
				}
				else   /* the first son is already the element, no need to insert it */
				{
					*errorCode = 1;
				}
			}

		}
	}

}

/* ------------------------------------------------------------------------ */
/* createModifiedNode    create a node which points to its father    		*/
/*                        						    						*/
/*									   										*/
/* Input :  - cur : we create the node based on the cur node                */
/*	     	- father: points to its father									*/
/*									     				    				*/
/* Output : the node freshly created 										*/
/* ------------------------------------------------------------------------ */
newNode_t* createModifiedNode(noeud_t* cur,newNode_t* pere)
{
	newNode_t* node = malloc(sizeof(newNode_t));

	node->value = cur->value;
	node->vLink = NULL;
	node->hLink = NULL;

	node->papa = pere;

	return(node);
}

/* ------------------------------------------------------------------------ */
/* copyTree    create a new instance of a tree which is a copy of a tree    */
/*                        						    						*/
/*									   										*/
/* Input :  - tree: is the tree we want to display                	    	*/
/*	     	- errorCode indicates whether the algorithm went wrong or not 	*/
/*			0 : so far so good !	     				    				*/
/* 			1 : problem during the copy				    					*/
/* ------------------------------------------------------------------------ */
newNode_t* copyTree(noeud_t* tree,int *errorCode)
{
	newNode_t*  newTree;
	int 		end;
	int         wasInStack; /* is the previous node was popped from the stack */
	noeud_t*    cur;
	stack_t*    stack;
	newNode_t*  currNewTree;
	newNode_t*  father; /* keep track of the father of the current node */
	typeStack   elmt;
	int 	    errorCodeStack;

	cur = tree;
	end = 1;
	wasInStack = 0;

	newTree = malloc(sizeof(newNode_t));
	newTree->papa = NULL;
	newTree->hLink = NULL;
	newTree->vLink = NULL;

	currNewTree = newTree;
	father = currNewTree;

	*errorCode = 0;

	/* init a stack */
	stack = initStack(SIZE_STACK, &errorCodeStack);
	if(errorCodeStack == 1)
	{
		
		if(cur->vLink != NULL) /* if the tree is not empty */               										
		{
			/* while we don't have gone throught the entire tree */ 
			while(cur != NULL && end == 1)   										
			{	
				/* make sure the next node has a vertical link and the curr was not pop from the stack */
				if(cur->vLink != NULL && wasInStack == 0)
				{
					/* while there is a son */
					do					
					{   
						cur = cur->vLink;

						currNewTree->vLink = createModifiedNode(cur,father);
						currNewTree = currNewTree->vLink;

						/* if the node hasn't vLink, then no need to push it ! */
						if(cur->vLink != NULL)
						{
							pushBis(stack,elmt,&errorCodeStack,cur);
							if(errorCodeStack != 1)
							{
								*errorCode = 1;
								end = 0; /* end the algorithm */
							} 
							else
							{
								father = currNewTree;
							}
						}
					}
					while(cur != NULL && cur->vLink != NULL && wasInStack == 0);
				}
				wasInStack = 0;


				if (cur->hLink != NULL && end == 1) /*if it has a brother */
				{
					cur = cur->hLink;
					currNewTree->hLink = createModifiedNode(cur,father);
					currNewTree = currNewTree->hLink;

					/* if the node hasn't vLink, then no need to push it ! */
					if(cur->vLink != NULL)
					{
						pushBis(stack,elmt,&errorCodeStack,cur);

						if(errorCodeStack != 1)
						{
							*errorCode = 1;
							end = 0; /* end the algorithm */
						} 
						else
						{
							father = currNewTree;
						}
					}
				}
				else /* if there isn't a brother we pull up the tree if it's possible */
				{   
					/* If the stack is not empty */
					if(!isStackEmpty(stack))
					{
						pop(stack,&elmt,&errorCodeStack);

						if(errorCodeStack != 1)
						{
							*errorCode = 1;
							end = 0; /* end the algorithm */
						}
						else
						{
							cur = (elmt.adr); 
							wasInStack = 1;

							currNewTree = currNewTree->papa; /* came back to the father */
							father = currNewTree->papa;
						}
					}

					if(isStackEmpty(stack) && cur->hLink == NULL && end == 1)
					{
						end = 0;
					}
				}
			}
		}
		freeStack(stack);
	}
	else
	{
		*errorCode = 1;
	}

	return(newTree);
}

/* -------------------------------------------------------------------- */
/* posFixNotationFather    display the postfix notation for a tree 		*/
/*                         where each node has a pointer to its father  */
/*																		*/
/* Input :    - tree: is the tree we want to display                	*/
/*																		*/
/*			     				          								*/
/* -------------------------------------------------------------------- */
void posFixNotationFather(newNode_t tree)
{
	newNode_t*  cur = tree.vLink; 

	/* some variable to stop and control the algorithm */
	int       end;

	/* backFromFather prevent the algorithm to process node that it has already processed */
	int 	  backFromFather;

	end = 0;
	backFromFather = 0;

	if(cur != NULL) /* if the tree is not empty */
	{

		while(cur  != NULL && end == 0)/* while we don't have gone throught the entire tree */ 
		{

			/* while there is a son, we process it */
			while(cur != NULL && cur->vLink != NULL && backFromFather == 0)  
			{   
				cur = cur->vLink; /* we go down throught the vertical link */
			}
			
			/* if this node had already been processed, we don't display it again */
			if(backFromFather == 0)
			{
				printf("| %c | ", cur->value);
			}
			backFromFather = 0;
				
			/*if it has a brother */
			if (cur->hLink != NULL) 
			{
				cur = cur->hLink; /* then we use the horizontal link */
			}
			else /* if there isn't a brother we come back to the father of the nodes */
			{   
				while (cur->papa != NULL && cur->hLink == NULL) /* wait for a father with a horizontal link */
				{
					backFromFather = 1; /* indicates that we will not process this node later */
					cur = cur->papa;

					if(cur->papa != NULL) /* if we reached the head of the tree, we don't display it */
					{
						printf("| %c | ", cur->value);
					}
				}

				if(cur->papa == NULL) /* end the algorithm if we hit the head */       
				{	
					end = 1;
				}
			}
		}
	}
	printf("\n");
}

/* -------------------------------------------------------------------- */
/* freeTreeFather    free the tree where each node has a pointer to its */
/*                   father												*/
/*																		*/
/* Input :    - tree: is the tree we want to free                		*/
/*																		*/
/*			     				          								*/
/* -------------------------------------------------------------------- */
void freeTreeFather(newNode_t tree)
{
	newNode_t*  cur;

	/* some variable to stop and control the algorithm */
	int        end;

	/* backFromFather prevent the algorithm to process node that it has already processed */
	int 	   backFromFather;
	newNode_t* temp;

	end = 0;
	backFromFather = 0;
	cur = tree.vLink; 

	if(cur != NULL) /* if the tree is not empty */
	{
		while(cur  != NULL && end == 0)/* while we don't have gone throught the entire tree */ 
		{
			/* while there is a son, we process it */
			while(cur != NULL && cur->vLink != NULL && backFromFather == 0)  
			{   
				cur = cur->vLink; /* we go down throught the vertical link */
			}
			
			/* save the current node that will be delete */
			if(backFromFather == 0)
			{
				temp = cur;
			}
			
			/*if it has a brother */
			if (cur->hLink != NULL) 
			{
				/* now we can delete this node, because we already went through its sons */
				if(backFromFather == 1)
				{
					temp = cur;
					backFromFather = 0;
				}

				cur = cur->hLink; /* then we use the horizontal link */

				free(temp);

			}
			else /* if there isn't a brother we come back to the father of the nodes */
			{   
				while (cur->papa != NULL && cur->hLink == NULL) /* wait for a father with a horizontal link */
				{
					/* each time we go up, we have to delete node */
					if(backFromFather == 1)
					{
						temp = cur;
					}
					cur = cur->papa;

					free(temp);
					backFromFather = 1; /* indicates that we will delete this node in the next loop */
				}

				if(cur->papa == NULL) /* end the algorithm if we hit the head */       
				{	
					end = 1;
				}
			}

		
		}
	}

	free(cur);
}

/* --------------------------------------------------------------------- */
/* freeTree    free the basic tree							 			 */
/*                														 */
/*																		 */
/* Input :    - tree: is the tree we want to free                		 */
/*			  - errorCode : indicates if the algorithm went wrong or not */
/*			  1 : problem - 0 : all good				          		 */
/* --------------------------------------------------------------------- */
void freeTree(noeud_t* a,int *errorCode)
{
	noeud_t*  cur;
	stack_t*  stack;
	typeStack elmt;
	int       end;
	int		  wasInStack;
	int 	  errorCodeStack;

	*errorCode = 0;
	stack = initStack(1000, &errorCodeStack);
	cur = a;
	end = 1;
	wasInStack = 0;

	/* if we had a problem during the initialization of the stack */
	if(errorCodeStack == 1)
	{
		if(cur != NULL) /* if the tree is not empty */               										
		{
			/* while we don't have gone throught the entire tree */ 
			while(cur != NULL && end != 0)   										
			{	
				if(wasInStack == 1) /* we have already processed this element */
				{
					noeud_t* temp;
					temp = cur;

					if(cur->hLink!=NULL) /* Has it a brother ? */
					{
						cur = cur->hLink ;

						if (!isStackEmpty(stack)) /* if the stack is not empty */
						{	
							incrementNbSon(stack,elmt,&errorCodeStack);

							/* if we had a problem with the stack */
							if(errorCodeStack != 1)
							{
								*errorCode = 1;
								end = 0; /* end the algortihm */
							}

						}
						wasInStack = 0; /* this element hasn't been processed yet */
					}
					else /* we pull up the tree if it is possible */
					{
						if(!isStackEmpty(stack))
						{
							pop(stack,&elmt,&errorCodeStack);

							/* if we had a problem with the stack */	
							if(errorCodeStack != 1)
							{
								*errorCode = 1;
								end = 0; /* end the algortihm */
							}
							else
							{
								cur = elmt.adr;
							}
						}
						else
						{
							end = 0;
						}
					}
					
					free(temp);

				}
				else
				{
					noeud_t* temp;

					/* while there is a son */
					while(cur != NULL && cur->vLink != NULL && end == 1)  						
					{   
						pushBis(stack,elmt,&errorCodeStack,cur);

						/* if we had a problem with the stack */
						if(errorCodeStack != 1)
						{
							*errorCode = 1;
							end = 0; /* end the algortihm */
						}
						else
						{
							cur = cur->vLink; /* the pointer points to its son */
						}
					}

					temp = cur;
				
					if (cur->hLink != NULL) /*if it has a brother */
					{
						cur = cur->hLink; /* the pointer points to its brother */

						if (!isStackEmpty(stack)) /* if the stack is not empty */
						{	
							incrementNbSon(stack,elmt,&errorCodeStack);
							
							/* if we had a problem with the stack */
							if(errorCodeStack != 1)
							{
								*errorCode = 1;
								end = 0; /* end the algortihm */
							}
						}
						
					}
					else /* if there isn't a brother we pull up the tree if it's possible */
					{   
						if (!isStackEmpty(stack)) /* if the stack is not empty we can pull up in the tree */
						{
							pop(stack,&elmt,&errorCodeStack);

							/* if we had a problem with the stack */
							if(errorCodeStack != 1)
							{
								*errorCode = 1;
								end = 0; /* end the algortihm */
							}
							else
							{
								cur = elmt.adr; /* the pointer points to its father */
							
								wasInStack = 1;
							}
						}
						else
						{
							end = 0;
						}
					}
			
					free(temp);

				}
			}
		}

		freeStack(stack); /* don't forget to free the stack even if we had a problem */
	}
	else
	{
		*errorCode = 1;
	}
}