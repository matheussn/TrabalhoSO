#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Dados.h"

int requisicao_recursos(int pid, int recursos[]){
    int x;
	srand( (unsigned)time(NULL));

	x =  ( rand() % 10 );

	if(x > 5){
		printf("Recurso alocado! \n");
		return 0;
	}else{
		printf("Recurso não alocado! \n");
		return -1;
	}
}

int libera_recursos(int pid, int recursos[]){

	printf("Recursos Liberados com sucesso\n");
	return 0;

}
