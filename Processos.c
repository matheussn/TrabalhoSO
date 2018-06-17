#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Dados.h"

int pid = 0;

int init_Thread(){

	return dados->processo[pid++].pid;
}

void kill_thread(int p){
	dados->processo[p].status = -1;
}