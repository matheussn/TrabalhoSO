/*
	Integrantes: 
	Mateus Benedini de Oliveira Santiago Prates.  Matrícula:11621BSI200
	Matheus Santiago Neto.  Matrícula:11621BSI252

*/


struct processo {
	int pid;
	int status; /*-1=> Morto  0=> Vivo*/
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
	float porcentagem;
	Processo * processo;
};
typedef struct dados Dados;

Dados * dados; // Variavel global que irá guardar os dados do sistema

/* 
	Função para inicializar a variavel global dados
*/
int init_Dados(int total[], int nroProcesso, int nroRecurso, float aux);

//Função para gerar um valor randomico entre 0 e a
int randomico(int a);
