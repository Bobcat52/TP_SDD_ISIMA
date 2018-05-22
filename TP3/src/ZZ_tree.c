#include "ZZ_tree.h"
#include "ZZ_stack.h"

noeud_t* createTree(char *formatage,int size)
{
	/* Init our Stack */
	stack_t* stack;
	int errorCode;

	printf("hh\n");
	printf("teste : %s \n",formatage);

	stack = initStack(100,&errorCode); 

 	noeud_t* head = NULL;
	noeud_t** prec = &head;
	noeud_t* curr;

	char courant;
	int index;
	index = 0;
	
	int fini = 0;
	int parentOpen = 0; /* Indique si le caractère précèdent était une parenthèse ouverte */
	int comma = 0;
	int numberOfNode = 0;

	int i=0;
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

					curr = elmtPile.adr;
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
					
					if(head != NULL) /* If we have already dealt with a node */
					{
						noeud_t* node = malloc(sizeof(noeud_t));
	
						node->value = courant;
					
						node->hLink = NULL;
						node->vLink = NULL;

						printf("1 \n");
						/* Create the vertical link */
	
						curr->vLink = node;

						printf("2 \n");
						/* Stack the current node to come back for it */

						T_elmtPile elmtPile;
						elmtPile.adr = curr;
						elmtPile.nb_fils = 0;


						push(stack, elmtPile , &errorCode);
						printf("3 \n");


						/* Change the current node */
						curr = node;
						printf("4 \n");
					}
					else
					{
						/* Creation of the node */
						noeud_t* node = malloc(sizeof(noeud_t));
	
						node->value = courant;
					
						node->hLink = NULL;
						node->vLink = NULL;

						printf("Création de la tete \n");
						*(prec) = node;
						curr = node;
						printf("valeur de la tête : %c \n",head->value);
					}

				}
				else /* We have a comma or a closed parenthesis */
				{
					/* Creation of the node */
					noeud_t* node = malloc(sizeof(noeud_t));
		
					node->value = courant;

					node->hLink = NULL;
					node->vLink = NULL;
					
					if(curr != NULL)
					{
						/* Create the vertical link */
						curr->hLink = node;
						/* Change the current node */
						curr = node;
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
