/* VLAD Andrei-Alexandru - 311CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 64

typedef struct celula
{
	void *info;
	struct celula *urm;
} Celula, *TLista, **ALista;

typedef struct stiva
{
	size_t dime;
	TLista vf;
}*TStiva;

typedef struct coada
{
	size_t nrMut;
	size_t dime;
	TLista front;
	TLista rear;
}Coada, *TCoada;

typedef struct mutare
{
	char src;
	char dest;
}Mutare, *TMutare;

typedef struct sistHanoi
{
	size_t card;
	char *culoare;
	TStiva stivaA;
	TStiva stivaB;
	TStiva stivaC;
	TCoada mutari;
}*TSistem;

/*Headere functii*/

/*aux.c*/
void toh(size_t ndisk, char src, char temp, char dest, TCoada mutari);
TLista InitCelula(void *data);
void DistrugeTot(TLista *LHanoi);
TSistem InitSistem(char culoare[MAX]);
int InsMutari(TCoada mutari, char src, char dest);

/*Operatii.c*/
int add(TLista *LHanoi, char culoare[MAX], size_t dimDisc);
int AfiStivaBV(FILE *out_file, TStiva stiva); //functie auxiliara pentru show
void show(TLista L, char* culoare, FILE *out_file);
void show_moves(TLista L, char* culoare, size_t nrMutari, FILE *out_file);

/*Coada.c*/
TCoada InitQ(size_t dime);
void DistrQ(TCoada coada);
void ResetMutari(TCoada mutari);
int InsQ(TCoada mutari, TMutare sMuta);
void ExtrQ(TCoada coada, TMutare *mutare);

/*Stiva.c*/
TStiva InitS(size_t dime);
void DistrS(TStiva stiva);
int Push(TStiva stiva, void *data);
size_t* Pop(TStiva stiva);

