// Função para retornar o pid da thread
int init_Thread();

/*
	Função para matar a thread
	Essa função efetivamente não mata a thread,
	somente libera os recursos da mesma
	e caso haja somente uma thread ativa, a função finaliza o processo
*/
void kill_thread(int p);

/*
	Função auxiliar para chamar a função randomico(int a)
	Essa função é chamada para a criação de um vetor de inteiros,
	que servirá para a requisição de recursos da thread.
	A função já limita o randomico entre 0 e a quantidade necessária (total - alocada);
	Tenta sempre evitar os casos em que o randomico retornaria o valor zero (0),
	para que o vetor não fique com todas as posições com 0
*/
int * rand_req(int p);

/*
	Função auxiliar para chamar a função randomico(int a)
	Essa função é chamada para a criação de um vetor de inteiros,
	que servirá para a liberação de recursos da thread.
	A função já limita o randomico entre 0 e a quantidade alocada;
*/
int * rand_lib(int p);

/*
	Função que verifica a quantidade de recursos alocados para a thread,
	caso a quantidade necessária (total - alocada), foi igual a 0 para todos os reursos,
	significa que a thread já alocou todos os recursos que precisava, 
	então a mesma é posta para dormir por um tempo maior,
	para que quando ela acordar ela libere uma parte desses recursos alocados
*/
void verifica_recursos(int p);
