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
    queue_t* file = NULL;
    int      end = 1;
    noeud_t* cur = a;
	queueType elmt;


    *errorCode = 0;
    file = initQueue(100,errorCode);

    if (cur != NULL)
    {
        while (cur != NULL && !end || cur->value != v) /* while we don't have found the value v or we don't have gone through the entire tree */
        {
            if (cur->vLink != NULL) /* if it has a son */
            {
                elmt.adr = cur; /* we stock the current element then we pull it on the queue */
                enterQueue(file,elmt,errorCode);
            }
            if (cur->hLink != NULL) /* if it has a brother */
            {
                cur = cur->hLink; /* the pointer points to its brother */
            }
            else /* if it doesn't have a brother */
            {
                if(!isQueueEmpty(file))				
                {
                    cur = file->base->adr; /* we go back on the first element threaded */
                    elmt = leaveQueue(file,errorCode); 
					cur = cur->vLink; /* the pointer points to its son */
                }
                else /* the queue is empty, there isn't son */
                {
                    end = 0; /* the path of the tree is finished */
                }
            }
        }
    }
    return cur ;
}

void insert(noeud_t* v,char w, int* errorCode)  
{
	noeud_t* cur=v;
	noeud_t* prec=NULL;
	*errorCode=0;
	if (cur!=NULL)       /*if the tree is not empty */
	{
		if (cur->vLink == NULL)  /* so there isn't son */
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
	char p='a';
	char i='a';
	arbre = (noeud_t *)malloc(sizeof(noeud_t));
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
	insert(pere,i,&errorCode);
	printf("Le pere:%c \nLes fils inseres: %c %c  \n",pere->value, pere->vLink->value,pere->vLink->hLink->value);
	
    return 0;
}
