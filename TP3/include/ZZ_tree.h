#ifndef ZZ_TREE_H
#define ZZ_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ZZ_base.h"
#include "ZZ_stack.h"
typedef struct noeud{

	char value;
	struct noeud* vLink;
	struct noeud* hLink;

} noeud_t;

typedef struct noeudModified{

	char value;
	struct noeudModified* vLink;
	struct noeudModified* hLink;
	struct noeud* papa;

} noeudModified_t;


noeud_t* createNode(char courant);
noeudModified_t* createModifiedNode(noeud_t* cur,noeud_t* pere);
	
noeud_t createTree(char* formatage);
void repPostFixe(noeud_t* a, int* errorCode);
noeud_t* rechercher(noeud_t * a, char v, int * errorCode);
void insertNode(noeud_t* v,char w, int* errorCode);
noeudModified_t copyTree(noeud_t arbre,int* errorCode);
void incrementNbSon(stack_t* stack, typeStack elmt, int*errorCode);
void pushBis(stack_t* stack, typeStack elmt, int* errorCode, noeud_t* cur);

#endif
