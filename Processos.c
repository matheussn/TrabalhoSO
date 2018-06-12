#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Processos.h"

struct processo {
	int pid;
	int * quantTotal;
	int * quantAlloc;
	int * quantNecess;
};

int qnt;
int pid = 0;

Processo * init_Thread(int quant[], int cont){
	int j;
	qnt = cont;

	Processo * p = (Processo *) malloc(sizeof(Processo));
	p->quantTotal = (int *) malloc(sizeof(int) * cont);
	p->quantAlloc = (int *) malloc(sizeof(int) * cont);
	p->quantNecess = (int *) malloc(sizeof(int) * cont);
	p->pid = pid;

	for(j = 0; j < cont; j ++){
		p->quantNecess[j] = p->quantTotal[j] = randomico(quant[j]);
		p->quantAlloc[j] = 0;
	}
	pid ++;
	return p;
}

int randomico(int a){
	sleep(0.5);
	int x;
	srand( (unsigned) a - rand() + time(NULL));

	x =  ( rand() % a );

	return x;
}

void need(Processo * p){
	int i;
	for(i = 0; i < qnt; i ++){
		printf("%d ", p->quantTotal[i]);
	}
	printf("\n");
}