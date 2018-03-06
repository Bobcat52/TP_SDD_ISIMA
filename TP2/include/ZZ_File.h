#include <stdio.h>
#include <stdlib.h>

typedef int typeFile;

typedef struct file{
	int size;
	int number;
	typeFile* start;
	typeFile* end;
	typeFile* base;
} file_t;

void initFile(file_t** p0,int size);
void entreeFile(file_t* p0,typeFile element,int* errorCode);
typeFile sortieFile(file_t* p0,int* errorCode);
int estVide(file_t* p0);
void libererFile(file_t* p0);
