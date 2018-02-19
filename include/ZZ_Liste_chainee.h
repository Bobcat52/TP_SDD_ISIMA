#ifndef ZZ_Liste_chainee_h
#define ZZ_Liste_chainee_h


typedef struct production
{	float 				value;
	int 				factory;
	int 				period;
	struct production * 	next;
} production_t;



production_t * rechElt(float v, production_t * pHead);
void printLinkedList(struct production *pHead);
void insertKSorted(production_t ** pHead, production_t *adresse,production_t *element,int K);
void insertProductionBlock(production_t **pHead,float value,int factory,int period,int K);
void freeLinkedList(production_t *pHead);


#endif
