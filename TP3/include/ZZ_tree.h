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
	
noeud_t* createTree(char* formatage);

noeud_t* createNode(char courant);



#endif
