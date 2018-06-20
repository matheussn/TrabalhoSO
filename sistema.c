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
void * threadsTest(void *);

int main(int argc, char **argv)
{
	int i,j;
	float aux = 1;

	pthread_t *tid;

	if(argc > 5  &&  ((strcmp(argv[3],"-a") == 0 && strcmp(argv[1],"-n") == 0 ) || strcmp(argv[3],"-p") == 0 ))
	{

		if(strcmp(argv[3],"-p") == 0 )
		{
			aux = atof(argv[4]);

			if(aux <= 1.0 && aux >= 0.1){

				nro_recursos = argc - 6;

				avail = (int *)malloc(sizeof(int) * (argc - 6));  
				printf("Quantidade de recurso INICIALMENTE disponível:\n");
				for(i = 6, j = 0 ; i < argc; i++ , j++) {
					avail[j] = atoi(argv[i]);
					printf("%i ", avail[j]);
				}  
				printf("\n");
			}
			else{
				printf("O valor após -p deve ser um ponto flutuante entre 0.1 e 1.0\n");
				exit(-1);
			}
		}
		else
		{
			nro_recursos = argc - 4;

			avail = (int *)malloc(sizeof(int) * (argc - 4));
			printf("Quantidade de recurso INICIALMENTE disponível:\n");
			for(i = 4, j = 0 ; i < argc; i++ , j++) {
				avail[j] = atoi(argv[i]);
				printf("%i ", avail[j]);
			}  
			printf("\n");
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

		tid = (pthread_t *) malloc(sizeof(pthread_t) * nro_processos);

		for(i = 0; i < nro_processos; i ++){
			pthread_create(&tid[i], NULL,threadsTest, &i);
		}

		for(i = 0; i < nro_processos; i ++){
			pthread_join(tid[i], NULL);
		}
	}
	else
		fprintf(stderr,"Agumento invalido\n");
}

void * threadsTest(void * arg){
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
		//Dormir sleep(random() % 3);
		sleep(random() % 8);

		//Liberar um subconjunto de recursos alocados
		sem_wait(&mutex_res);

		rec = rand_lib(p);
		libera_recursos(p,rec);
		free(rec);
		sem_post(&mutex_res);

		//Dormir sleep(random() % 3);
		sleep(random() % 8);
	}
}
