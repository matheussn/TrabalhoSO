#include <stdlib.h>
#include <stdio.h>
#include "Dados.h"

int init_Dados(int total[], int nroProcesso, int nroRecurso){
	int i;
	
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
		dados->total[i] = total[i];
		dados->disponivel[i] = 0;
	}
    
    return 1;
	
}
