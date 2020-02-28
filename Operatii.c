/* VLAD Andrei-Alexandru - 311CB */
#include "header.h"

int add(TLista *LHanoi, char culoare[MAX], size_t dimDisc)
{
	/*VALORI RETURN: 0 -> succes ; !=0 -> esuare alocari*/

	TSistem sistemH = NULL;

	if(!(*LHanoi))
	{	/*Lista de sisteme Hanoi e vida*/
		/*Se creeaza celula pentru primul sistem Hanoi*/
		TLista celulaSist = InitCelula(NULL);
		if(!celulaSist)	{return 1;}
		*LHanoi = celulaSist;								/*Leaga celula in lista*/
		sistemH = InitSistem(culoare);			/*Creeaza structura*/
		if(!sistemH)	{free(celulaSist); return 2;}
		celulaSist->info = sistemH;					/*Leaga structura in celula creata*/
		Push(sistemH->stivaA, &dimDisc);		/*Insereaza discul in stiva A ordonat*/
		(sistemH->card)++;									/*Creste numarul discurilor din sistem*/


		/*Reseteaza mutarile la fiecare adaugare a unui element*/
		ResetMutari(sistemH->mutari);
		size_t ndisk = sistemH->card;
		char src = 'A', temp = 'B', dest = 'C';
		toh(ndisk, src, temp, dest, sistemH->mutari);

		return 0;
	}

	TLista L = *LHanoi;
	TLista ant = L;
	while(L)															/*Cauta culoarea*/
	{
		sistemH = (TSistem)L->info;
		if(!strcmp(sistemH->culoare, culoare))
			break;													/*S-a gasit sistemul de culoare dorita*/

		ant = L;
		L = L->urm;
	}

	if(L == NULL)
	{	/*S-a parcurs lista si nu s-a gasit culoarea*/
		/*Se va introduce o noua structura pentru acest sistem Hanoi*/
		TLista celulaSist = InitCelula(NULL);
		if(!celulaSist)	{return 1;}
		ant->urm = celulaSist;							/*Adauga celula la finalul listei*/
		sistemH = InitSistem(culoare);			/*Creeaza structura*/
		if(!sistemH)	{free(celulaSist); return 2;}
		celulaSist->info = sistemH;					/*Leaga structura in celula creata*/
		Push(sistemH->stivaA, &dimDisc);		/*Insereaza discul in stiva A*/
		(sistemH->card)++;									/*Creste numarul discurilor din sistem*/

		/*Reseteaza mutarile la fiecare adaugare a unui element*/
		ResetMutari(sistemH->mutari);
		size_t ndisk = sistemH->card;
		char src = 'A', temp = 'B', dest = 'C';
		toh(ndisk, src, temp, dest, sistemH->mutari);

		return 0;
	}

	/*Se va introduce discul in stiva A*/
	sistemH = (TSistem)L->info;
	TStiva sA = sistemH->stivaA;

	TStiva saux = InitS(sA->dime);
	// if(!saux)	{Distruge...; return -1;}
	while(sA->vf && *(size_t*)((sA->vf)->info) < dimDisc)
	{
		size_t *data = Pop(sA);
		Push(saux, data);
		free(data);
	}
	Push(sA, &dimDisc);
	while(saux->vf)
	{
		size_t *data = Pop(saux);
		Push(sA, data);
		free(data);
	}
	DistrS(saux);
	free(saux);

	(sistemH->card)++;									/*Creste numarul discurilor din sistem*/
	/*Reseteaza mutarile la fiecare adaugare a unui element*/
	ResetMutari(sistemH->mutari);
	size_t ndisk = sistemH->card;
	char src = 'A', temp = 'B', dest = 'C';
	toh(ndisk, src, temp, dest, sistemH->mutari);

	return 0;
}

int AfiStivaBV(FILE *out_file, TStiva stiva)
{
	TStiva saux = InitS(sizeof(size_t));
	if(!saux)	{return -1;}
	size_t *data = NULL;

	if(!stiva->vf)	fprintf(out_file, "\n");
	else						fprintf(out_file, " ");

	while(stiva->vf)
	{	/*Se rastoarna stiva A in stiva auxiliara
			pentru a citi de la baza la varf*/
		data = Pop(stiva);
		Push(saux, data);
		free(data);
	}
	/*Se citeste fiecare element din saux in timp ce se rastoarna
		inapoi in stiva initiala*/
	while(saux->vf)
	{	/*Se rastoarna stiva A in stiva auxiliara
			pentru a citi de la baza la varf*/
		data = Pop(saux);
		fprintf(out_file, "%zu", *data);
		if(saux->vf)	fprintf(out_file, " ");
		else					fprintf(out_file, "\n");
		Push(stiva, data);
		free(data);
	}

	DistrS(saux);
	free(saux);

	return 1;
}

void show(TLista L, char* culoare, FILE *out_file)
{
	/*Cauta sistemul de culoarea dorita*/
	TSistem sistemH;
	while(L)
	{
		sistemH = (TSistem)(L->info);
		if(!strcmp((char*)sistemH->culoare, culoare))
			break;
		L = L->urm;
	}
	if(!L)
	{
		fprintf(out_file, "A_%s:\n", culoare);
		fprintf(out_file, "B_%s:\n", culoare);
		fprintf(out_file, "C_%s:\n", culoare);
		return;
	}

	fprintf(out_file, "A_%s:", culoare);
	if(L)
		AfiStivaBV(out_file, sistemH->stivaA);	//Verif + +
	else
		fprintf(out_file, "\n");

	fprintf(out_file, "B_%s:", culoare);
	if(L)
		AfiStivaBV(out_file, sistemH->stivaB);
	else
		fprintf(out_file, "\n");

	fprintf(out_file, "C_%s:", culoare);
	if(L)
		AfiStivaBV(out_file, sistemH->stivaC);
	else
		fprintf(out_file, "\n");
}

void show_moves(TLista L, char* culoare, size_t nrMutari, FILE *out_file)
{
	/*Cauta sistemul de culoarea dorita*/
	TSistem sistemH = NULL;
	while(L)
	{
		sistemH = (TSistem)(L->info);
		if(!strcmp((char*)sistemH->culoare, culoare))
			break;
		L = L->urm;
	}
	if(!L)	{fprintf(out_file, "M_%s:\n", culoare);	return;}

	TCoada coada = sistemH->mutari;
	TCoada c1 = InitQ(sizeof(struct mutare));
	if(!c1)	{ printf("Nu s-a alocat coada auxiliara 1\n"); return;}
	TCoada c2 = InitQ(sizeof(struct mutare));
	if(!c2)	{ printf("Nu s-a alocat coada auxiliara 2\n"); return;}

	fprintf(out_file, "M_%s:", culoare);
	if(coada->front)							fprintf(out_file, " ");
	else													fprintf(out_file, "\n");

	int i;
	TMutare mutare = NULL;
	for(i = 0; i < (int)nrMutari; ++i)
	{	/*Se muta primele nrMutari in prima coada auxiliara si se afiseaza*/
		ExtrQ(coada, &mutare);
		fprintf(out_file, "%c->%c", mutare->src, mutare->dest);
		if(i == (int)nrMutari - 1)	fprintf(out_file, "\n");
		else												fprintf(out_file, " ");
		InsQ(c1, mutare);
		mutare = NULL;
	}

	ExtrQ(coada, &mutare);
	if(!mutare)	printf("Mutare nu e valida\n");
	else
	{
		InsQ(c2, mutare);
		mutare = NULL;
	}

	DistrQ(c1);
	free(c1);
	DistrQ(c2);
	free(c2);
}