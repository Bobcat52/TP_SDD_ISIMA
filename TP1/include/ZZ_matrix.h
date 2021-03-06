/* ################################################# */
/* file's name : ZZ_Matrix.h						 */
/*												     */
/* Author : Mathieu Boutin & Jérémy Morceaux		 */
/* Date : March 2018								 */
/*													 */
/* This file contains headers for ZZ_Matrix.c		 */
/* Desc : It allows the user to manipulate a matrix  */ 
/* (loading, printing, etc ...)						 */
/* ################################################# */

#ifndef ZZ_MATRIX_H
#define ZZ_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

/* Struct */
typedef struct matrix
{
	float ** value;
	int 	 line;
	int 	 column;

} matrix_t;

/* Function */
matrix_t loadMatrixFromFile(char* fileName,int *errorCode);
void printMatrix(matrix_t matrix);
matrix_t multiply(matrix_t A, matrix_t B,int *errorCode);
matrix_t zeroMatrix(int line,int column,int *errorCode);
void freeMatrix(matrix_t matrix);

#endif
