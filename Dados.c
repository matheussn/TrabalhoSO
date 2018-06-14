#include <stdlib.h>
#include <stdio.h>
#include "Dados.h"

struct processo {
	int pid;
	int * quantTotal;
	int * quantAlloc;
	int * quantNecess;
};

int * disponivel;
int * total;
Processos * p;
