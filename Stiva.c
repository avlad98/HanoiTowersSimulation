/* VLAD Andrei-Alexandru - 311CB */
#include "header.h"

TStiva InitS(size_t dime)
{
	/*Aloca sectiunea de gestiune a stivei (dim elem + vf)*/
	TStiva s = (TStiva)malloc(sizeof(struct stiva));
	if(!s)	{return NULL;}

	s->dime = dime;
	s->vf = NULL;

	return s;
}

void DistrS(TStiva stiva)
{
	while(stiva->vf)
	{
		TLista aux = stiva->vf;
		stiva->vf = aux->urm;
		free(aux->info);
		free(aux);
	}
}

int Push(TStiva stiva, void *data)
{	/*Functia intoarce:	1 -> inserare cu succes;	0 -> esuat*/

	size_t d = stiva->dime;
	/*Creeaza celula noua cu informatia primita*/
	void *info = (void*)malloc(d);
	if(!info)	{return 0;}
	memcpy(info, data, d);	/*Aloca dinamic informatia primita*/
	TLista celula = InitCelula(info);

	/*Insereaza celula la inceputul listei generice*/
	celula->urm = stiva->vf;
	stiva->vf = celula;

	return 1;
}

size_t* Pop(TStiva stiva)
{
	TLista aux = stiva->vf;
	stiva->vf = aux->urm;
	size_t *data = aux->info;
	free(aux);

	return data;
}