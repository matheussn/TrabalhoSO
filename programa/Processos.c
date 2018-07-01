#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "Dados.h"
#include "Banqueiro.h"
#include "Processos.h"

int pid = 0;

// Função para retornar o pid da thread
int init_Thread(){
	return dados->processo[pid++].pid;
}

/*
	Função para matar a thread
	Essa função efetivamente não mata a thread,
	somente libera os recursos da mesma
	e caso haja somente uma thread ativa, a função finaliza o processo
*/
void kill_thread(int p){
	int flag = 0, flag2 = 0;
	int i = libera_recursos(p, dados->processo[p].quantAlloc);
	dados->processo[p].status = -1;
	for(i = 0; i < dados->nro_processo; i ++){
		if(dados->processo[i].status == 0) 
		{
			flag2 = i;
			flag ++;
		}	
	}

	printf("=======================\n= Threads Ativas: %d  =\n=======================\n", flag);

	if(flag <= 1){
		printf("Finalizando processo...\n");		
		i = libera_recursos(dados->processo[flag2].pid, dados->processo[flag2].quantAlloc);
		exit(-1);
	}
}

/*
	Função auxiliar para chamar a função randomico(int a)
	Essa função é chamada para a criação de um vetor de inteiros,
	que servirá para a requisição de recursos da thread.
	A função já limita o randomico entre 0 e a quantidade necessária (total - alocada);
	Tenta sempre evitar os casos em que o randomico retornaria o valor zero (0),
	para que o vetor não fique com todas as posições com 0
*/
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
	}

	return rec;
}

/*
	Função auxiliar para chamar a função randomico(int a)
	Essa função é chamada para a criação de um vetor de inteiros,
	que servirá para a liberação de recursos da thread.
	A função já limita o randomico entre 0 e a quantidade alocada;
*/
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

/*
	Função que verifica a quantidade de recursos alocados para a thread,
	caso a quantidade necessária (total - alocada), foi igual a 0 para todos os reursos,
	significa que a thread já alocou todos os recursos que precisava, 
	então a mesma é posta para dormir por um tempo maior,
	para que quando ela acordar ela libere uma parte desses recursos alocados
*/
void verifica_recursos(int p){
	
	int flag = 0;


	for(int i = 0; i < dados->nro_recurso ; i++ ){
		if(dados->processo[p].quantNecess[i] ==	0)
			flag++;
	}

	if(flag == dados->nro_recurso)
	{	
		printf("----------------------------------\n- P%d Conseguiu todos os recursos -\n----------------------------------\n", p);
		sleep(random() % 10);
		printf("---------------------\n- P%d Voltou a vida -\n---------------------\n", p);

	}
}
