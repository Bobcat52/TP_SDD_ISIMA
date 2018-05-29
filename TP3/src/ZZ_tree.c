#include "ZZ_tree.h"
#include "ZZ_stack.h"


noeud_t* createNode(char courant)
{

	noeud_t* node = malloc(sizeof(noeud_t));

	node->value = courant;

	node->hLink = NULL;
	node->vLink = NULL;

	return(node);
}
noeud_t* createTree(char *formatage)
{
	/* Init our Stack */
	stack_t* stack;
	int size = strlen(formatage);
	int errorCode;
	stack = initStack(100,&errorCode); 

 	noeud_t* head = NULL;
	noeud_t** prec = &head;

	char courant;
	int index;
	index = 0;
	
	int fini = 0;
	int parentOpen = 0; /* Indique si le caractère précèdent était une parenthèse ouverte */
	int comma = 0;
	int numberOfNode = 0;

	int i = 0;

	for(i = 0; i < 19;i++)
	{
		printf("%c \n",formatage[index]);
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

					*prec = elmtPile.adr;
				}
				else
				{
					fini = 1;
					printf("fini \n");
				}
				/*comma = 0;*/
				/*parentOpen = 0;*/
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

				if(parentOpen == 1)
				{
					/* Creation of the node */
					noeud_t* node = createNode(courant);

					if(*prec != NULL)
					{
						(*prec)->vLink = node;

						T_elmtPile elmtPile;
						elmtPile.adr = *prec;
						elmtPile.nb_fils = 0;

						push(stack, elmtPile , &errorCode);
					}
					else
					{
						*(prec) = node;
					}
					
					prec = &node;

				}
				else /* We have a comma or a closed parenthesis */
				{
					/* Creation of the node */
					noeud_t* node = createNode(courant);
					
					if(*prec != NULL)
					{
						/* Create the vertical link */
						(*prec)->hLink = node;
						/* Change the current node */
						prec = &node;
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
