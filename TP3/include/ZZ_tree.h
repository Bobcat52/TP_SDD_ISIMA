#ifndef ZZ_TREE_H
#define ZZ_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ZZ_stack.h"

typedef struct tree{

	char value;
	struct tree* vLink;
	struct tree* hLink;

} tree_t;
	
tree_t* createTree(char* formatage,int size);



#endif
