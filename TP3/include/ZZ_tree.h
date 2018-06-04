#ifndef ZZ_TREE_H
#define ZZ_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ZZ_base.h"

typedef struct noeud{

	char value;
	struct noeud* vLink;
	struct noeud* hLink;

} noeud_t;

noeud_t* createNode(char courant);	
noeud_t createTree(char* formatage);
void repPostFixe(noeud_t* a, int* errorCode);
noeud_t* rechercher(noeud_t * a, char v, int * errorCode);
void insertNode(noeud_t* v,char w, int* errorCode);


#endif
