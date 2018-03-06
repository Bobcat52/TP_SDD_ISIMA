#include <stdio.h>
#include <stdlib.h>
#include "ZZ_Pile.h"

pile_t * initPile(int taille)	
{	
	pile_t * p;
	int      codeE;
	
	codeE=-1;
	p = malloc(sizeof(pile_t));

	if (p !=NULL)
	{
			p->deb = malloc(taille*sizeof(typePile));
			if ((p->deb)!= NULL)
			{
					p->tailleMax = taille;
					p->numSommet = -1;
					codeE = 1;
			}
			else 
			{
				free(p);
				p=NULL;
			}
	}
	
	return p; 
}

void libererPile( pile_t * p)
{
	if (p->deb != NULL)
	{
		free(p->deb);
		
	}
	else 
	{
		free(p);
	}
	p = NULL;
	
}


int estVide(pile_t * p)
{
		return (p->numSommet == -1);
}


void empiler (pile_t * p, typePile v)
{		
		int codeE;
		
		codeE = -1;
		if (p->numSommet < (p->tailleMax) )
		{
				*((p->deb) + (p->numSommet +1)*sizeof(typePile)) = v;
				p->numSommet += 1;
				codeE = 1;
		}
		
}

void depiler ( pile_t * p, typePile * v)
{
		/*codeE = -1;*/
		if (!estVide(p))
		{
				*v = *((p->deb) + (p->numSommet)*sizeof(typePile));
				p->numSommet -= 1;
				/*codeE = 1;*/
		}
}

int main()
{
	pile_t * p;
	int      i, v=2;
	p = NULL;
	p = initPile(3);
	printf(" la pile est initialisée \n ");
	i = estVide(p);
	printf ( "%d\n", i);
	empiler(p , v);
	i = estVide(p);
	printf ( "%d\n", i);
	int val;
	depiler(p, &val);
	printf("%d \n",val);
	
	return 0;
}
