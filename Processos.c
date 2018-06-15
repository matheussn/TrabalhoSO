#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Dados.h"

int randomico(int a);

int pid = 0;

int init_Thread(int quant[]){

	int j;

	dados->processo[pid].quantTotal = (int *) malloc(sizeof(int) * dados->nro_recurso);
    if(dados->processo[pid].quantTotal == NULL)
        return -2;

	dados->processo[pid].quantAlloc = (int *) malloc(sizeof(int) * dados->nro_recurso);
    if(dados->processo[pid].quantAlloc == NULL)
        return -2;

	dados->processo[pid].quantNecess = (int *) malloc(sizeof(int) * dados->nro_recurso);
    if(dados->processo[pid].quantNecess == NULL)
        return -2;

	dados->processo[pid].pid = pid;



	for(j = 0; j < dados->nro_recurso; j ++)
    {
		dados->processo[pid].quantNecess[j] = dados->processo[pid].quantTotal[j] = randomico(quant[j]);
		dados->processo[pid].quantAlloc[j] = 0;
	}

	return dados->processo[pid++].pid;
}

int randomico(int a){
	sleep(0.5);
	int x;
	srand( (unsigned) a - rand() + time(NULL));

	x =  ( rand() % a );

	return x;
}

void need(int p){
	int i;
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", dados->processo[p].quantTotal[i]);
	}
	printf("\n");
}
