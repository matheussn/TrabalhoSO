#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Dados.h"

void need(int p);




int init_Dados(int total[], int nroProcesso, int nroRecurso){

	int i, j;
	int pid; 
	
	dados = (Dados *) malloc(sizeof(Dados));
    	if(dados == NULL)
        	return 0;
	
	dados->disponivel = (int *) malloc(sizeof(int) * nroRecurso);
    	if(dados->disponivel == NULL)
        	return 0;
	
    	dados->total = (int *) malloc(sizeof(int) * nroRecurso);
    	if(dados->total == NULL)
       		return 0;

	dados->processo = (Processo *) malloc(sizeof(Processo) * nroProcesso);
   	if(dados->processo == NULL)
        	return 0;

	dados->nro_recurso = nroRecurso;

	dados->nro_processo = nroProcesso;

	for(i = 0; i < nroRecurso; i ++){
		dados->total[i] = dados->disponivel[i] = total[i];
	}

	for( pid = 0; pid < nroProcesso; pid++)
	{
		dados->processo[pid].quantTotal = (int *) malloc(sizeof(int) * dados->nro_recurso);
		if(dados->processo[pid].quantTotal == NULL)
			return 0;

		dados->processo[pid].quantAlloc = (int *) malloc(sizeof(int) * dados->nro_recurso);
		if(dados->processo[pid].quantAlloc == NULL)
			return 0;

		dados->processo[pid].quantNecess = (int *) malloc(sizeof(int) * dados->nro_recurso);
		if(dados->processo[pid].quantNecess == NULL)
			return 0;

		dados->processo[pid].pid = pid;
	}

	for( pid = 0; pid < nroProcesso; pid++)
		for(j = 0; j < nroRecurso; j ++)
	    	{
			dados->processo[pid].quantNecess[j] = dados->processo[pid].quantTotal[j] = randomico(total[j]);
			dados->processo[pid].quantAlloc[j] = 0;
		}
    return 1;
	
}

int randomico(int a){

	time_t t;
	int x;
	
	srand( (unsigned) a - rand() + time(NULL));
	x = (rand() % a ) ;
	return x;
}

void need(int p){
	int i;
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", dados->processo[p].quantTotal[i]);
	}
	printf("\n");
}
