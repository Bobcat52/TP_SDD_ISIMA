#ifndef ZZ_Pile_h
#define ZZ_Pile_h

typedef int typePile;

typedef struct pile
{
		int           tailleMax;
		int           numSommet;
		typePile  *   deb;
}pile_t;


pile_t * initPile(int taille); 

void libererPile(pile_t * p);

int estVide(pile_t * p);

void empiler(pile_t * p, typePile v);

void depiler(pile_t * p, typePile * v);








#endif
