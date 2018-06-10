/* ########################################################## */
/* file's name : main.c					                      */
/*							                                  */
/* Author : Mathieu Boutin & Jeremy Morceaux                  */
/* Date : March 2018					                      */
/*							                                  */
/* This file contains the main program of the TP, we use the  */
/* severals tools created to revert a stack.                  */
/* ########################################################## */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMAL  "\x1B[0m"
#define ROUGE  "\x1B[31m"
#define VERT  "\x1B[32m"
#define JAUNE  "\x1B[33m"
#define BLEU  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define BLANC  "\x1B[37m"

#include "ZZ_tree.h"

int main(int argc, char * argv[])
{
	noeud_t arbre;
	int errorCode;
	int o;
	/*char *formatage = "(a(b(k(h,u)z)f(m)x(p,v,w)))";*/
	char *formatage = "(a(b(k(u,w)))c(l(j,x)m(d,e)))";

	arbre = createTree(formatage);

	
	printf("Premiere representation Postfixee avant insertion: \n");
	repPostFixe(arbre.vLink,&errorCode);
	 
	 noeud_t* pere;
	 char p='k';
	 char i='s';

	pere = rechercher(arbre.vLink, p, &errorCode);
	
	insertNode(pere,i,&errorCode);

	printf("Deuxieme representation Postfixee apres insertion: \n");
	repPostFixe(arbre.vLink,&errorCode);

	newNode_t* newTree = copyTree(&arbre,&errorCode);

	repPostFixeBis(*newTree,&errorCode);
	return(EXIT_SUCCESS);
}
