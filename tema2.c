/* VLAD Andrei-Alexandru - 311CB */
#include "header.h"

int main(int argc, char const *argv[])
{
	if(argc < 2)
	{
		printf("Nu sunt suficienti parametri: (%s ", argv[0]);
		printf("in_file out_file)\n");
		return 1;
	}

	/*Deschidere fisiere date ca argumente*/
	FILE *in_file = fopen(argv[1], "r");
	if(!in_file)
		return 2;

	FILE *out_file = fopen(argv[2], "w");
	if(!out_file)
		return 3;

	/*Initializare lista generica de sisteme hanoi de culori diferite*/
	TLista LHanoi = NULL;


	/*Citeste numarul de operatii din fisierul de input*/
	size_t nOper;
	fscanf(in_file, "%zu", &nOper);
	
	/*Citeste nOper operatii*/
	int i;	
	for(i = 0; i < (int)nOper; ++i)
	{
		char operatie[MAX];
		fscanf(in_file, "%s", operatie);
		if(!strcmp(operatie, "add"))												//ADD
		{
			char culoare[MAX] = {0};
			size_t dimDisc;
			fscanf(in_file, "%s %zu", culoare, &dimDisc);
			add(&LHanoi, culoare, dimDisc);
		}else if (!strcmp(operatie, "play"))								//PLAY
		{
			char culoare[MAX] = {0};
			size_t nrMutari;
			fscanf(in_file, "%s %zu", culoare, &nrMutari);
		}else if (!strcmp(operatie, "show"))								//SHOW
		{
			char culoare[MAX] = {0};
			fscanf(in_file, "%s", culoare);
			show(LHanoi, culoare, out_file);
		}else	if (!strcmp(operatie, "show_moves"))					//SHOW_MOVES
		{
			char culoare[MAX] = {0};
			size_t nrMutari;
			fscanf(in_file, "%s %zu", culoare, &nrMutari);
			// show_moves(LHanoi, culoare, nrMutari, out_file);
		}
	}

	DistrugeTot(&LHanoi);										/*Elibereaza toata memoria alocata*/
	/*Inchidere fisiere*/
	fclose(in_file);
	fclose(out_file);
	return 0;
}