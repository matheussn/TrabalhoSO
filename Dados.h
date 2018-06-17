struct processo {
	int pid;
	int * quantTotal;
	int * quantAlloc;
	int * quantNecess;
};

typedef struct processo Processo;
struct dados {
	int * disponivel;
	int * total;
	int nro_processo;
	int nro_recurso;
	Processo * processo;
};
typedef struct dados Dados;

Dados * dados;

int init_Dados(int total[], int nroProcesso, int nroRecurso);
int randomico(int a);
