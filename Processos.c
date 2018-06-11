#include <stdlib.h>
#include <stdio.h>
#include "Processos.h"

struct processo {
	int * quantTotal;
    int * quantAlloc;
    int * quantNecess;
};

/*Processo init_Thread(){

}*/

Processo * teste(int n){
	return (Processo *) malloc(sizeof(Processo) * n);
}