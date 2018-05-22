/* ########################################################## */
/* file's name : main.c					                      */
/*							                                  */
/* Author : Mathieu Boutin & Jérémy Morceaux                  */
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
	noeud_t* arbre;
	char *formatage = "(a(b(k(h,u)z)f(m)x)";

	int size = strlen(formatage); 

	arbre = createTree(formatage,size);
	return(EXIT_SUCCESS);
}
