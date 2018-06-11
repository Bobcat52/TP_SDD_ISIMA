/* ########################################################## */
/* file's name : main.c					      */
/*							      */
/* Author : Mathieu Boutin & Jeremy Morceaux                  */
/* Date : March 2018					      */
/*							      */
/* This file contains the main program of the TP, we use the  */
/* severals tools created to revert a stack.                  */
/* ########################################################## */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROUGE  "\x1B[31m"
#define VERT  "\x1B[32m"
#define BLANC  "\x1B[37m"

#include "ZZ_tree.h"

int main()
{
	noeud_t* arbre;
	int errorCode;
	char *treeString = "(a(b(k(h,u)z)f(m)x(p,v,w)))";

	printf("%sI/ Creation de l'arbre !\n%s",VERT,BLANC);
	arbre = createTree(treeString,&errorCode);

	if(errorCode == 0)
	{
		if(arbre->vLink != NULL)
		{
			noeud_t*   pere;
			newNode_t* newTree;
			char       p,i;

			printf("Creation réussie !\n");
			printf("%sII/ Premiere representation Postfixee avant insertion: \n%s",VERT,BLANC);

			/* display the postfix notation of this tree , startint at vLink because we don't want to display the head of the tree */
			repPostFixe(arbre->vLink,&errorCode);

			/* unable to display the tree */
			if(errorCode == 1)
			{
				printf("%sImpossible d'afficher la notation postfixee de cette arbre.\n%s",ROUGE,BLANC);
			}

			p = '!'; /* !  is equal to the head of the tree */
			i = 'm';

			printf("%sIII/ Recherche du noeud pour inserer le nouveau noeud: \n%s",VERT,BLANC);

			pere = rechercher(arbre, p, &errorCode);
			/* can't find the node */
			if(errorCode == 0)
			{
				printf("Le nouveau noeud %c sera inseré sur le noeud : %c\n",i,p);
				printf("%sIV/ Insertion du nouveau noeud: \n%s",VERT,BLANC);
				insertNode(pere,i,&errorCode);

				if(errorCode == 0)
				{
					printf("Insertion réussie !\n");
				}
				else
				{
					printf("%sCe noeud est déjà présent dans l'arbre.Insertion annulée. \n%s",ROUGE,BLANC);
				}
			}
			else
			{
				printf("%sImpossible de trouver ce noeud %c, êtes-vous sûr qu'il existe ?\n%s",ROUGE,p,BLANC);
			}

			printf("%sV/ Deuxieme representation Postfixee après insertion: \n%s",VERT,BLANC);

			/* display the postfix notation of this tree, startint at vLink because we don't want to display the head of the tree */
			repPostFixe(arbre->vLink,&errorCode);

			if(errorCode == 1)
			{
				printf("%sImpossible d'afficher la notation postfixee de cette arbre.\n%s",ROUGE,BLANC);
			}

			printf("%sVI/ Copie de l'arbre de base: \n%s",VERT,BLANC);
			newTree = copyTree(arbre,&errorCode);
			if(errorCode == 0)
			{
				printf("Copie réussie !\n");
				printf("%sVII/ troisieme representation postfixee avec la nouvelle structure de noeud: \n%s",VERT,BLANC);
				posFixNotationFather(*newTree);
			}
			else
			{
				printf("%sImpossible de copier cette arbre. Peut-être que votre pile est trop petite ?\n%s",ROUGE,BLANC);
			}

			printf("%sVIII/ Libération de l'arbre de base: \n%s",VERT,BLANC);
			freeTree(arbre->vLink,&errorCode);
			if(errorCode == 0)
			{
				printf("Libération réussie !\n");
			}
			else
			{
				printf("%sImpossible de libérer cette arbre. Problème de pile peut-être ?\n%s",ROUGE,BLANC);
			}

			/* Free the last tree */
			printf("%sIX/ Libération de l'arbre modifié.\n%s",VERT,BLANC);
			freeTreeFather(*newTree);
			printf("Libération réussie !\n");
		}
		else
		{
			printf("Votre arbre est vide ! Va falloir le remplir !\n");


		}

		
	}
	else
	{
		printf("%sImpossible de créer cette arbre. Peut-être que votre pile est trop petite ?\n%s",ROUGE,BLANC);
	}

	free(arbre); /* we finally free the head of the tree */

	return(EXIT_SUCCESS);
}
