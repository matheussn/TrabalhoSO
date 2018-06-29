#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "Dados.h"
#include "Processos.h"
#include "Banqueiro.h"

/* Semáforos */

sem_t mutex_init;
sem_t mutex_res;

int *avail;
int nro_processos,nro_recursos;
void * threads(void *);
void atribuiArgumentos( char **argv,int argc, int n);

int main(int argc, char **argv)
{	
	float aux = 1;

	/*Verifica se os parametros argc e argv estão corretos*/
	if(argc > 5  &&  ((strcmp(argv[3],"-a") == 0 && strcmp(argv[1],"-n") == 0 ) || strcmp(argv[3],"-p") == 0 ))
	{
		/*Se houver o argumento -p significa que existe uma porcentagem limitadora*/
		if(strcmp(argv[3],"-p") == 0 )
		{
			aux = atof(argv[4]);

			if(aux <= 1.0 && aux >= 0.1){
				atribuiArgumentos(argv, argc, 6);				
			}
			else{
				printf("O valor após -p deve ser um ponto flutuante entre 0.1 e 1.0\n");
				exit(-1);
			}
		}
		else
		{
			atribuiArgumentos(argv, argc, 4);			
		}

		nro_processos = atoi(argv[2]);

		printf("Numero de Clientes:\t %i \n", nro_processos);


		printf("Numero de recursos:\t %i\n", nro_recursos);

		printf("\n");

		int verifica = init_Dados(avail, nro_processos, nro_recursos, aux);
		if( verifica == 0){
			fprintf(stderr," falha na alocação");
		}

		sem_init(&mutex_init, 0, 1);
		sem_init(&mutex_res, 0, 1);

		pthread_t *tid;
		tid = (pthread_t *) malloc(sizeof(pthread_t) * nro_processos);
		
		int i,j;
		for(i = 0; i < nro_processos; i ++){
			pthread_create(&tid[i], NULL,threads, &i);
		}

		for(i = 0; i < nro_processos; i ++){
			pthread_join(tid[i], NULL);
		}
	}
	else
		fprintf(stderr,"Agumento invalido\n");
}


/*Funçao que verifica os argumentos que é passado no momento da execução*/
void atribuiArgumentos( char **argv,int argc, int n){

	int i,j;
	nro_recursos = argc - n;

	avail = (int *)malloc(sizeof(int) * nro_recursos);
	printf("Quantidade de recurso INICIALMENTE disponível:\n");
	for(i = n, j = 0 ; i < argc; i++ , j++) {
		avail[j] = atoi(argv[i]);
		printf("%i ", avail[j]);
	}  
	printf("\n");
}


void * threads(void * arg){
	int  i;
	int p;
	int * rec;

	sem_wait(&mutex_init);

	p = init_Thread();

	sem_post(&mutex_init);

	while(1){
		//Requisitar recurso
		sem_wait(&mutex_res);
		rec = rand_req(p);
		if(requisicao_recursos(p,rec) == -1){
			printf("P%d Morreu!\n", p);
			kill_thread(p);
			sem_post(&mutex_res);
			pthread_exit(NULL);
		}
		free(rec);
		sem_post(&mutex_res);
		verifica_recursos(p);
		//Dormir por um tempo randomico;
		sleep(random() % 8);

		//Liberar um subconjunto de recursos alocados
		sem_wait(&mutex_res);

		rec = rand_lib(p);
		libera_recursos(p,rec);
		free(rec);
		sem_post(&mutex_res);

		//Dormir por um tempo randomico;
		sleep(random() % 8);
	}
}
