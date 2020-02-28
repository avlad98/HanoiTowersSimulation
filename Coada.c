/* VLAD Andrei-Alexandru - 311CB */
#include "header.h"


TCoada InitQ(size_t dime)
{
	/*Aloca sectiunea de gestiune a cozii*/
	TCoada q = (TCoada)malloc(sizeof(struct coada));
	if(!q)	{return NULL;}

	q->dime = dime;
	q->nrMut = 0;
	q->front = NULL;
	q->rear = NULL;

	return q;
}

void DistrQ(TCoada coada)
{
	if(coada->front == NULL && coada->rear == NULL)	{return;}

	TLista aux = NULL;
	while(coada->front)
	{
		aux = coada->front;
		coada->front = aux->urm;
		free(aux->info);
		free(aux);
	}
	coada->front = coada->rear = NULL;
	coada->nrMut = 0;
}

void ResetMutari(TCoada mutari)	{	DistrQ(mutari);}

int InsQ(TCoada mutari, TMutare sMuta)
{
	TLista celula = InitCelula(sMuta);
	if(mutari->front == NULL && mutari->rear == NULL)
	{
		mutari->front = mutari->rear = celula;
		(mutari->nrMut)++;
		return 0;
	}

	(mutari->rear)->urm = celula;
	mutari->rear = celula;
	(mutari->nrMut)++;

	return 0;
}

void ExtrQ(TCoada coada, TMutare *mutare)
{
	if(coada->front == NULL)	{*mutare = NULL; return;}
	/*Sau daca coada->nrMut == 0*/

	TLista aux = coada->front;
	coada->front = aux->urm;
	*mutare = (TMutare)(aux->info);
	free(aux);
	(coada->nrMut)--;
}
