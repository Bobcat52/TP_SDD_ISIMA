#ifndef ZZ_Liste_chainee_h
#define ZZ_Liste_chainee_h

#define I 3
#define J 3 



typedef struct tableau
{	float valeur;
	int ligne;
	int colonne;
	struct tableau * suivant;
}tableau_t;



tableau_t * addNewElement( tableau_t **ptete);
void insererListe(struct tableau **pTete, struct tableau *element);
float* rechElt(int v, tableau_t * tableau);





#endif
