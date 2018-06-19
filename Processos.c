#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "Dados.h"
#include "Banqueiro.h"

int pid = 0;
void verifica_recursos(int p);


int init_Thread(){
	return dados->processo[pid++].pid;
}

void kill_thread(int p){
	int flag = 0, flag2 = 0;
	int i = libera_recursos(p, dados->processo[p].quantAlloc);
	dados->processo[p].status = -1;
	for(i = 0; i < dados->nro_processo; i ++){
		if(dados->processo[i].status == 0 || dados->processo[i].status == 1) 
		{
			flag2 = i;
			flag ++;
		}
			
	}

	printf("Threads Ativas: %d\n", flag);
	if(flag <= 1){
		printf("Finalizando processo...\n");		
		i = libera_recursos(dados->processo[flag2].pid, dados->processo[flag2].quantAlloc);
		exit(-1);
	}
}

int * rand_req(int p){

	
	/* 0 <= req <= quantTotal - quantAlloc*/
	int i, k, flag = 0;

	int *rec = (int *) malloc(sizeof(int) * dados->nro_recurso);

	for(i = 0; i < dados->nro_recurso; i ++){
		k = dados->processo[p].quantNecess[i];
		if(k > 1)
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

void verifica_recursos(int p){
	
	int flag = 0;


	for(int i = 0; i < dados->nro_recurso ; i++ )
		if(dados->processo[p].quantNecess[i] ==	0)
		{
			flag++;
		}	
		
	if(flag == dados->nro_recurso)
	{	
		printf("---------------------------------\n- P%d está pronto para terminar -\n---------------------------------\n", p);
		dados->processo[p].status = 1;
		sleep(random() % 20);
		printf("----------------\n- P%d terminou -\n----------------\n", p);
		sleep(random() % 10);
		dados->processo[p].status = 0;
		printf("---------------------\n- P%d Voltou a vida -\n---------------------\n", p);

	}
}
