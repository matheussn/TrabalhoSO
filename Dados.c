#include <stdlib.h>
#include <stdio.h>
#include "Dados.h"

void init_Dados(int total[], int nroProcesso, int nroRecurso){
	int i;
	
	dados = (Dados *) malloc(sizeof(Dados));
	dados->disponivel = (int *) malloc(sizeof(int) * nroRecurso);
	dados->total = (int *) malloc(sizeof(int) * nroRecurso);
	dados->processo = (Processo *) malloc(sizeof(Processo) * nroProcesso);
	dados->nro_recurso = nroRecurso;
	dados->nro_processo = nroProcesso;

	for(int i = 0; i < nroRecurso; i ++){
		dados->total[i] = total[i];
		dados->disponivel[i] = 0;
	}
	
}
