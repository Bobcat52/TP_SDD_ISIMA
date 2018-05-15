#include "ZZ_tree.h"

tree_t* createTree(char *formatage,int size)
{
	/* Init our Stack */
	stack_t* stack;
	int errorCode;
	printf("hh\n");
	printf("teste : %s \n",formatage);

	stack = initStack(100,&errorCode); 

 	tree_t* head;
	tree_t* curr = head;
	char courant;
	int index;
	index = 0;
	
	int fini = 0;
	int parentOpen = 0; /* Indique si le caractère précèdent était une parenthèse ouverte */
	int comma = 0;
	int numberOfNode = 0;


	while( index != size && fini == 0)
	{
		printf("dghdfg\n");
		printf("%s \n",formatage[index]);
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
				if(isStackEmpty(stack)) /* If the stack is not empty */
				{
					pop(stack,curr,&errorCode);
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
				break;
			}
			default:
			{
				numberOfNode++;

				if(parentOpen == 1)
				{
					/* Creation of the node */
					tree_t node;
	
					node.value = courant;
					
					node.hLink = NULL;
					node.vLink = NULL;
					
					if(curr != NULL) /* If we already deal with a node */
					{
						
						/* Create the vertical link */
						curr->vLink = &node;
						/* Stack the current node to come back for it */
						push(stack, curr , &errorCode);
						/* Change the current node */
						curr = &node;
					}

				}
				else /* We have a comma or a closed parenthesis */
				{
					/* Creation of the node */
					tree_t node;
		
					node.value = courant;

					node.hLink = NULL;
					node.vLink = NULL;
					
					if(curr != NULL)
					{
						/* Create the vertical link */
						curr->hLink = &node;
						/* Change the current node */
						curr = &node;
					}
				}
				comma = 0;
				parentOpen = 0;
				break;
			}
			
			
		}
		index++;
	}
	printf("Il y a %d noeuds dans cette arbre \n",numberOfNode);

	return(head);
}
