/* ########################################################## */
/* file's name : ZZ_tree.h				                      */
/*							                                  */
/* Author : Mathieu Boutin & Jérémy Morceaux                  */
/* Date : June 2018					               		      */
/*							                                  */
/* This file contains headers for the file ZZ_tree.c          */
/*							                                  */
/* ########################################################## */


#ifndef ZZ_TREE_H
#define ZZ_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ZZ_base.h"
#include "ZZ_stack.h"

#define SIZE_STACK 50


/* basic tree */
typedef struct noeud{

	char value;
	struct noeud* vLink;
	struct noeud* hLink;

} noeud_t;

/* Tree with father/node */
typedef struct newNode{

	char value;
	struct newNode* vLink;
	struct newNode* hLink;
	struct newNode* papa;

} newNode_t;


/* Creation */
noeud_t* createNode(char courant);
newNode_t* createModifiedNode(noeud_t* cur,newNode_t* pere);
noeud_t* createTree(char* treeString,int *errorCode);

/* Insertion */
void insertNode(noeud_t* tree,char w, int* errorCode);
noeud_t* createNodeForInsertion(char w,noeud_t *horizontal);

/* Search */
noeud_t* rechercher(noeud_t * tree, char v, int * errorCode);

/* Copy */
newNode_t* copyTree(noeud_t* tree,int *errorCode);

void repPostFixe(noeud_t* tree, int* errorCode);
void posFixNotationFather(newNode_t tree);

/* Liberation */
void freeTreeFather(newNode_t tree);
void freeTree(noeud_t* a,int * errorCode);

/* utils */
void incrementNbSon(stack_t* stack, typeStack elmt, int*errorCode);
void pushBis(stack_t* stack, typeStack elmt, int* errorCode, noeud_t* cur);

#endif
