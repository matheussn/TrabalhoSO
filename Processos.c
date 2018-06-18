#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Dados.h"
#include "Banqueiro.h"

int pid = 0;

int init_Thread(){
	return dados->processo[pid++].pid;
}

void kill_thread(int p){

	int i;
	printf("\tQuantidade de recursos alocados: KILL THREAD\n\t");
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", dados->processo[p].quantAlloc[i]);
	}
	printf("\n");

	i = libera_recursos(p, dados->processo[p].quantAlloc);
	dados->processo[p].status = -1;
}

int * rand_req(int p){
	/* 0 <= req <= quantTotal - quantAlloc*/
	int i, k;

	int *rec = (int *) malloc(sizeof(int) * dados->nro_recurso);

	for(i = 0; i < dados->nro_recurso; i ++){
		k = dados->processo[p].quantTotal[i] - dados->processo[p].quantAlloc[i];
		if(k != 0)
			rec[i] = randomico(k);
		else
			rec[i] = k;

		//printf("0 <= %d <= %d - %d\n",rec[i], dados->processo[p].quantTotal[i] , dados->processo[p].quantAlloc[i]);
	}

	return rec;
}

int * rand_lib(int p){
	/* 0 <= req <= quantAlloc*/
	int i, k;

	int *rec = (int *) malloc(sizeof(int) * dados->nro_recurso);

	for(i = 0; i < dados->nro_recurso; i ++){
		if(dados->processo[p].quantAlloc[i] != 0)
			rec[i] = randomico(dados->processo[p].quantAlloc[i]);
		else
			rec[i] = 0;
	}

	return rec;
}