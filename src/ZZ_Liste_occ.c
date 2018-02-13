#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ZZ_Liste_occ.h"
#include "ZZ_Liste_chainee.h"



tableau_t supprlist_occ(int i, tableau_t * tableau)
{
		tableau_t *pprec=tableau;
		tableau_t *cour= tableau->valeur;
		while(cour!=NULL)
			{
				if((cour->ligne) ==i)
				{
						supprimerbloc(&pprec, cour->suivant);
				}
				pprec=&(pprec->suivant);
				cour=cour->suivant;
			}
		
		
}

tableau_t supprimerbloc( 
