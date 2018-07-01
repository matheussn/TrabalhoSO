#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Dados.h"

// Função para requisitar recursos
int requisicao_recursos(int pid, int recursos[]){

	int i, j;

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

			/* 
				Verificar se mesmo após a alocação o sistema consegue 
				terminar uma das outras n threads
			*/
			int k=0;
			for(j = 0; j< dados->nro_recurso; j++)
			{
				if (flag[j] >= dados->processo[i].quantNecess[j])
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

				printf("\n\tQuantidade de recursos necessarios para finalizar do processo: \n\t");
				for(j = 0; j < dados->nro_recurso; j ++){
					dados->processo[pid].quantNecess[j] -= recursos[j];
					printf("%d ", dados->processo[pid].quantNecess[j]);
				}
				printf("\n");

				return 0;
			}
		}
	}
	printf("P%d: Recurso Não alocado! \n", pid);
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

// Função para liberação de recursos
int libera_recursos(int pid, int recursos[]){
	int flag = 0;
	int i;
	printf("P%d: Recursos Liberados com sucesso\n", pid);

	printf("\tQuantidade de recursos alocados P%d: \n\t", pid);
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", dados->processo[pid].quantAlloc[i]);
	}
	printf("\n");

	printf("\tQuantidade de recursos para liberar: \n\t");
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", recursos[i]);
	}
	printf("\n");

	for(i = 0; i<dados->nro_recurso; i++){
		dados->disponivel[i] += recursos[i];
		dados->processo[pid].quantAlloc[i] -= recursos[i];
		dados->processo[pid].quantNecess[i] += recursos[i];
	}

	printf("\tQuantidade de recursos no sistema após liberar: \n\t");
	for(i = 0; i < dados->nro_recurso; i ++){
		printf("%d ", dados->disponivel[i]);
	}
	printf("\n");

	return 0;
}
