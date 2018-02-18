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
tableau_t * rechElt(float v, tableau_t * tableau);
void afficherListeChaine(struct tableau *pTete);
void insertKSorted(tableau_t ** tableau, tableau_t *adresse,tableau_t *element,int K);
void insertBlock(tableau_t **pTete,float valeur,int ligne,int colonne,int K);



#endif
