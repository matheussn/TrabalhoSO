#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Dados.h"

/* 
	Função para inicializar a variavel global dados
*/
int init_Dados(int total[], int nroProcesso, int nroRecurso, float aux){

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

	dados->porcentagem = aux; 

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
		dados->processo[pid].status = 0;
	}

	for( pid = 0; pid < nroProcesso; pid++){
		printf("P%d: ", pid);
		for(j = 0; j < nroRecurso; j ++)
		{
			dados->processo[pid].quantNecess[j] = dados->processo[pid].quantTotal[j] = randomico((int)total[j] * dados->porcentagem );
			dados->processo[pid].quantAlloc[j] = 0;
			printf("%d ", dados->processo[pid].quantTotal[j]);
		}
		printf("\n");
	}
	return 1;

}

//Função para gerar um valor randomico entre 0 e a
int randomico(int a){
	time_t t;
	int x;

	srand( (unsigned) (a *random()) +(random()* time(NULL)));
	x = (random() % a )  ;
	return x ;
}