#include <stdlib.h>
#include <stdio.h>

struct processo {
	int pid;
	int * quantTotal;
	int * quantAlloc;
	int * quantNecess;
};