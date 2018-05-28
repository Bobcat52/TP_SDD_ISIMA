#include "../include/ZZ_queue.h"
#include "../include/insertion.h"


int isQueueEmpty(queue_t* p0)
{
	return(p0->number == 0); /* simply return either the queue is full or not */
}

queue_t* initQueue(int size,int* errorCode)
{
	queue_t * p0;

	*errorCode = -1;
	
	/* We create the queue */
	p0 = (queue_t*)malloc(sizeof(queue_t));

	if(p0 != NULL)
	{
		/* Init the queue data */
		p0->size = size;
		p0->number = 0;
	
		/* allocate an array to store the data */
		p0->base = (queueType*)malloc(size * sizeof(queueType));
		*errorCode = 0;

		/* If the allocation went well */
		if(p0->base != NULL)
		{		
			*errorCode = 1;
			p0->start = 0;
			p0->end = size-1;
		}	
	}

	return(p0); /* return the pointer of the queue */
}

void enterQueue(queue_t* p0,queueType element,int* errorCode)
{
	*errorCode = 0;
	/* if the queue is not full */
	if(p0->number <= p0->size)
	{
		*errorCode = 1;
		/* we actualize the index end, and the number of value in the queue*/
		p0->end = (p0->end + 1) % p0->size;
		p0->base[p0->end] = element;
		p0->number += 1;
		
	}
	else /* the queue is full */
	{
		fprintf(stderr,"[WARNING] This queue is full \n");
	}
}



queueType leaveQueue(queue_t* p0,int* errorCode)
{
	queueType res;
	*errorCode = 0;

	/* Make sure the queue is not empty */
	if(!isQueueEmpty(p0))
	{
		*errorCode = 1;
		/* retrieve the value which will be returned */
		res = p0->base[p0->start];

		/* actualiaze the index start, and the number of value in the queue */
		p0->start = (p0->start + 1 ) % p0->size;
		p0->number -= 1;
	}

	return(res); /* return the value */
}


noeud_t *  rechercher(noeud_t * a, char v, int * errorCode)
{
    queue_t* file=NULL;
    int      end = 0;
    noeud_t* cur = a;
	queueType elmt;


    *errorCode = 0;
    file = initQueue(100,errorCode);

    if (cur != NULL)
    {
        while (cur !=NULL && end && cur->value != v)   //Tant qu'on a pas trouve v ou qu'on est pas a la fin de l'arbre
        {
            if (cur->vLink != NULL)                   // Si l'element a un fils
            {
                elmt.adr = cur;						 // on stock l'element courrant et on l'enfile
                enterQueue(file,elmt,errorCode);
            }
            if (cur->hLink != NULL)                // Si l'element courant a un frere alors on va sur celui-ci
            {
                cur = cur->hLink;
            }
            else                                   // S'il n'a pas de freres 
            {
                if(!isQueueEmpty(file))
                {
                    cur = file->base->adr;             // on retourne sur le premier element enfiler
                    elmt = leaveQueue(file,errorCode); // on defile le premier element de la file
                    //val= leaveQueue(file,errorCode);
					cur = cur->vLink ;                // on va sur son fils
                }
                else                           // la file est vide, ie aucun element a de fils
                {
                    end = 1;
                }
            }
        }
    }
    return cur ;
}

void insert(noeud_t* v,char w, int* errorCode)  // v correspond à l'adresse du pere et w au fils a inserer
{
	noeud_t* cur=v;
	noeud_t* prec=NULL;
	*errorCode=0;
	if (cur!=NULL)      
	{
		if (cur->vLink == NULL)  //alors il n'a pas de fils
		{
			cur->vLink=(noeud_t *)malloc(sizeof(noeud_t));
			cur = cur->vLink;
			cur->value= w;
			cur->hLink=NULL;
			cur->vLink=NULL;
			*errorCode=1;
		}
		else                     // alors il a au moins un fils
		{
			prec = cur;
			cur = cur->vLink;
			if (cur->value < w)   //le premier fils n'est pas avant l'element dans l'alphabet
			{
				while(cur != NULL && cur->value <w) // On cherche ou inserer le fils
				{
					prec = cur;
					cur = cur->hLink;
				}
				if(cur == NULL) //on est arrive a la fin des fils, on l'insere donc a la fin
				{
					prec->hLink = (noeud_t *)malloc(sizeof(noeud_t)); //on cree le fils
					prec->hLink->value = w;
					prec->hLink->vLink = NULL;
					prec->hLink->hLink = NULL;
					*errorCode=1;

				}
				else                 //on insere le fils au milieu de ses freres;
				{
					if (cur->value != w)  //le fils w n'existe pas deja
					{
						prec->hLink = (noeud_t *)malloc(sizeof(noeud_t)); // on insere le fils w entre 2 freres
						prec->hLink->value = w;
						prec->hLink->vLink = NULL;
						prec->hLink->hLink = cur;    //on relie au frere suivant  
						*errorCode=1; 
					}
					else    // Sinon le fils w existe deja donc pas besoin de l'inserer
					{
						*errorCode=-1;
					}
				
				}
			}
			else
			{
				if (cur->value > w) // alors on insere le fils en tete
				{
					prec->vLink = (noeud_t *)malloc(sizeof(noeud_t)); // on insere le fils w entre 2 freres
					prec->vLink->value = w;
					prec->vLink->vLink = NULL;
					prec->vLink->hLink = cur;    //on relie au frere suivant  
					*errorCode=1; 
				}
				else   //le premier fils est deja w donc pas besoin de l'inserer
				{
					*errorCode=-1;
				}
			}

		}
	}
}

int main()
{
	int errorCode;
	noeud_t* arbre;
	noeud_t* pere;
	char p='c';
	char i='a';
	arbre->value = 'a';
    arbre->vLink = (noeud_t *)malloc(sizeof(noeud_t));
    arbre->hLink = (noeud_t *)malloc(sizeof(noeud_t));
    arbre->vLink->value = 'b';
    arbre->vLink->vLink = NULL;
    arbre->vLink->hLink = NULL;
    arbre->hLink->value = 'c';
    arbre->hLink->vLink = NULL;
    arbre->hLink->hLink = NULL;
	pere=rechercher(arbre, p, &errorCode);
	printf("%c\n",pere->value);
	//insert(pere,i,&errorCode);
	//printf("Le pere:%c \nLes fils inseres: %c %c \n",pere->value, pere->vLink->value, pere->vLink->hLink->value);
	
    return 0;
}