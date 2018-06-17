#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Dados.h"

int requisicao_recursos(int pid, int recursos[]){

	int i, j;
	int x;


	/*
		Verificar se temos recursos para atender a requisição (disp >= rec)
		se sim
			Fazer simulação! 
				criar um vetor simulando que a alocação dos recursos foi realizada, e verificar,
				se caso, mesmo ainda alocando tais recursos, conseguimos "finalizar" pelo menos um processo?
				se sim
					return 0;
				se não
					return -1;

		return -1;
	*/


	/* Verificar se temos recursos para atender a requisição (disp >= rec) */
	int flag2 = 0;
	for(i = 0; i < dados->nro_recurso; i++)
		if(dados->disponivel[i] >= recursos[i])
			flag2++;

	if(flag2 == dados->nro_recurso )
	{
		/* Simular alocação dos recursos requeridos! */
		int * flag = (int *) malloc (dados->nro_recurso * sizeof(int));
		
		for(i = 0; i < dados->nro_recurso; i++)
			flag[i] = dados->disponivel[i] - recursos[i];

		for(i = 0; i < dados->nro_processo; i++)
		{
			if(dados->processo[i].status == -1)
				continue;

			int k;
			for(j = 0; j< dados->nro_recurso; j++)
			{
				if (flag[j] >= dados->processo[i].quantTotal[j])
					k++;
			}

			if(k == dados->nro_recurso){
				/* Alocar Recursos */
				printf("ALOCA DANADA!\n");
				return 0;
			}
		}
		return -1;
	}
	else
	{
		printf("P%d: Recurso não alocado! \n", pid);
		return -1;
	}
}

int libera_recursos(int pid, int recursos[]){


	int flag = 0;
	int i;

	for (i = 0 ; i< dados->nro_recurso; i++)    
		if(dados->processo[pid].quantNecess[i] == 0)
			flag++;

		if(flag == dados->nro_recurso - 1)
		{
			for(i = 0; i<dados->nro_recurso; i++)
				dados->disponivel[i] += recursos[i];
			printf("P%d: Recursos Liberados com sucesso\n", pid);
		}
		else
			printf("P%d: Processo não finalizado\n", pid);

		return 0;

	}
