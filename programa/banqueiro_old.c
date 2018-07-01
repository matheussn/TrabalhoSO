/*
	Integrantes: 
	Mateus Benedini de Oliveira Santiago Prates  Matricula:11621BSI200
	Matheus Santiago Neto  Matricula:11621BSI252

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct processo
{
    int * quantTotal;
    int * quantAlloc;
    int * quantNecess;
};

int *avail;
int nro_processos,nro_recursos;
struct processo * p;


void libera();
void requisicao();
int randomico(int a);

int main(int argc, char **argv)
{
    int i,j;
    int a;

    if(argc > 5)
    {


        nro_processos = atoi(argv[2]);

        printf("Numero de Clientes:\t %i \n", nro_processos);

        nro_recursos = argc - 4;

        printf("Numero de recursos:\t %i\n", nro_recursos);

        p = malloc(sizeof(struct processo) * nro_processos);

        if(p == NULL){
            printf("Ocorreu um erro ao na alocacao:\n");
            exit(-1);
        }
        
        avail = (int *)malloc(sizeof(int) * (argc - 4));            
        
        printf("Quantidade de recurso INICIALMENTE disponível:\n");

        for(i = 4, j = 0 ; i < argc; i++ , j++) {
            avail[j] = atoi(argv[i]);
            printf("%i ", avail[j]);
        }
        printf("\n");

        printf("TOTAL de Recursos para terminar os processos:\n");
        for(i=0; i<nro_processos; i++)
        {
            p[i].quantTotal = malloc(sizeof(int) * nro_recursos);
            p[i].quantAlloc = malloc(sizeof(int) * nro_recursos);
            printf("P%d: ",i);
            for(j=0; j<nro_recursos; j++)
            {
                p[i].quantTotal[j] = randomico(avail[j]);
                p[i].quantAlloc[j] = 0;
                printf("%d ",p[i].quantTotal[j]);
            }
            printf("\n");
        }


        printf("Quantidade de recurso Alocado:\n");
        for(i=0; i<nro_processos; i++)
        {
            printf("P%d: ",i);
            for(j=0; j<nro_recursos; j++)
            {

                int a = randomico(avail[j]);
                
                if(a <= p[i].quantTotal[j])
                {
                    p[i].quantAlloc[j] = a;
                    printf("%d ",p[i].quantAlloc[j]);
                    avail[j] = avail[j] - p[i].quantAlloc[j];
                }
                else
                    j--;
            }
            printf("\n");
        }

        printf("Recursos Disponiveis:\n"); 
        for(j=0; j<nro_recursos; j++)
            printf("%d ",avail[j]);
        printf("\n");

        requisicao();

        printf("Quantidade de recurso que cada processo precisa:\n");        
        for(i=0; i<nro_processos; i++)
            {   printf("P%d: ",i);     
        for(j=0; j<nro_recursos; j++)
        {
            printf("%d ",p[i].quantNecess[j]);
        }
        printf("\n");

    }        
    libera();
    return 0;
}
}


int randomico(int a)
{

    sleep(1);
    int x;
    srand( (unsigned)time(NULL));

    x =  ( rand() % a );

    return x;
}


void requisicao()
{
    int i,j;
    for(i=0; i<nro_processos; i++)
    {
        p[i].quantNecess = (int*) malloc (nro_recursos * sizeof(int));

        for(j=0; j<nro_recursos; j++)
        {

            p[i].quantNecess[j]=p[i].quantTotal[j]-p[i].quantAlloc[j];
        }
    }
}


void libera()
{
    int i,j;
    int *finalizado,flag=1,k,nro_processos_finalizados=0;

    finalizado = malloc(nro_processos * sizeof(int));

    for(i=0; i<nro_processos; i++)
    {
        finalizado[i]=0;
    }

    printf("\n\n");


    while(flag)
    {
        flag=0;

        for(i=0; i<nro_processos; i++)
        {
            int percorreu_todos_recursos=0;

            for(j=0; j<nro_recursos; j++)
            {
                if((finalizado[i]==0)&&(p[i].quantNecess[j] <= avail[j]))
                {
                    percorreu_todos_recursos++;
                    if(percorreu_todos_recursos == nro_recursos)
                    {
                        for(k=0; k<nro_recursos; k++)
                        {
                            avail[k] += p[i].quantAlloc[k];
                        }
                        finalizado[i] = 1;
                        flag = 1;

                        printf("P%d: ",i);
                        printf("Finalizado\n"); 
                        printf("Liberado: ");    
                        for(k=0; k<nro_recursos; k++){
                            printf("%d ",p[i].quantAlloc[k]);
                        }
                        printf("\n");
                        printf("total Disponivel: ");        
                        
                        for(k=0; k<nro_recursos; k++){
                            printf("%d ",avail[k]);
                        }
                        
                        printf("\n\n"); 

                        if(finalizado[i]==1)
                        {
                            i=nro_processos;
                        }
                    }
                }
            }
            
        }
    }

    for(i=0; i<nro_processos; i++)
    {
        if(finalizado[i]==1)
        {
            nro_processos_finalizados++;
        }
        else
        {
            printf("P%d: ",i);
            printf("NaoFinalizado\n");
        }
    }




    if(nro_processos_finalizados==nro_processos)
    {
        printf("\nEstado seguro\n");
    }
    else
    {
        printf("\nEstado inseguro\n");
    }
}
