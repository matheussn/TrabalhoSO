#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Dados.h"

int randomico(int a);

int pid = 0;

int init_Thread(){

	return dados->processo[pid++].pid;
}


