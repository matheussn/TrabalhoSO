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
	for(i = 0; i < dados->nro_recurso; i++){
		if(dados->disponivel[i] >= recursos[i])
			flag2++;
	}

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

			int k=0;
			for(j = 0; j< dados->nro_recurso; j++)
			{
				if (flag[j] >= (dados->processo[i].quantTotal[j] - dados->processo[i].quantAlloc[j]))
					k++;
			}

			if(k == dados->nro_recurso){
				/* Alocar Recursos */
				printf("P%d: Recurso alocado! \n", pid);
				printf("\tQuantidade de recursos requeridos: \n\t");
				for(j = 0; j < dados->nro_recurso; j ++){
					printf("%d ", recursos[j]);
				}
				printf("\n\tQuantidade de recursos disponivel no sistema: \n\t");
				for(j = 0; j < dados->nro_recurso; j ++){
					printf("%d ", dados->disponivel[j]);
				}
				printf("\n\tQuantidade de recursos do sistema após a alocação: \n\t");
				for(j = 0; j < dados->nro_recurso; j ++){
					dados->disponivel[j] -= recursos[j];
					printf("%d ", dados->disponivel[j]);
				}
				printf("\n\tQuantidade de recursos do processo após a alocação: \n\t");
				for(j = 0; j < dados->nro_recurso; j ++){
					dados->processo[pid].quantAlloc[j] += recursos[j];
					printf("%d ", dados->processo[pid].quantAlloc[j]);
				}
				printf("\n");
				return 0;
			}
		}

		printf("P%d: Recurso Não alocado! 1\n", pid);
		printf("\tQuantidade de recursos requeridos: \n\t");
		for(j = 0; j < dados->nro_recurso; j ++){
			printf("%d ", recursos[j]);
		}
		printf("\n\tQuantidade de recursos disponivel no sistema: \n\t");
		for(j = 0; j < dados->nro_recurso; j ++){
			printf("%d ", dados->disponivel[j]);
		}
		printf("\n");

		return -1;
	}
	else
	{
		printf("P%d: Recurso Não alocado! \n", pid);
		printf("\tQuantidade de recursos requeridos: \n\t");
		for(j = 0; j < dados->nro_recurso; j ++){
			printf("%d ", recursos[j]);
		}
		printf("\tQuantidade de recursos disponivel no sistema: \n\t");
		for(j = 0; j < dados->nro_recurso; j ++){
			printf("%d ", dados->disponivel[j]);
		}
		printf("\n");
		return -1;
	}
}

int libera_recursos(int pid, int recursos[]){


	int flag = 0;
	int i;

	for(i = 0; i<dados->nro_recurso; i++){
		dados->disponivel[i] += recursos[i];
		dados->processo[pid].quantAlloc[i] -= recursos[i];
	}
	printf("P%d: Recursos Liberados com sucesso\n", pid);

	printf("\tQuantidade de recursos a liberar: \n\t");
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", recursos[i]);
	}
	printf("\n");

	return 0;

}
