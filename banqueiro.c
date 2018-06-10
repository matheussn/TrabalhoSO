#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<unistd.h>

struct processo
{
    char nome[3];
    int * quantTotal;
    int * quantAlloc;
};


int max[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int total [100][100];
int totalR [100];
int n,r;
void libera();
void requisicao();
void showAll();
int randomico();



int randomico(int a)
{

    sleep(1);
    int x;
    srand( (unsigned)time(NULL));

    x =  ( rand() % a );

    return x;
}



int main(int argc, char **argv)
{
    int i,j;
    int a;

    if(argc > 5)
    {


        n = atoi(argv[2]);


        printf("Numero de Clientes\t %i \n", n);

        r = argc - 4;

        printf("Quantidade de recurso INICIALMENTE disponível\t %i\n", r);

        printf("Capital disponível 1\n");

        for(i = 4, j = 0 ; i < argc; i++ , j++) {
            avail[j] = atoi(argv[i]);
            printf("%i ", avail[j]);
        }
        printf("\n");

        printf("Recursos TOTAL ainda necessários\n");
        for(i=0; i<n; i++)
        {
            for(j=0; j<r; j++)
            {
                max[i][j] = randomico(avail[j]);
                printf("%d ",max[i][j]);
            }
            printf("\n");
        }


        printf("Quantidade de recurso Alocado\n");
        for(i=0; i<n; i++)
        {
            for(j=0; j<r; j++)
            {

                int a = randomico(avail[j]);

                if(a <= max[i][j])
                {
                    alloc[i][j] = a;
                    printf("%d ",alloc[i][j]);
                    avail[j] = avail[j] - alloc[i][j];
                }
                else
                    j--;
            }
            printf("\n");
        }

        printf("Quantidade de recursos que cada Cliente precisa\n");
        for(i=0; i<n; i++)
        {
            for(j=0; j<r; j++)
            {

                printf("%d ",max[i][j] - alloc[i][j]);
            }
            printf("\n");
        }
        printf("Quantidade de recurso FINAL disponível\n");

        for(i = 0; i < r; i++)
            printf("%i ", avail[i]);
        printf("\n");



        showAll();
        requisicao();
        libera();
        return 0;
    }
}





void showAll()
{
    int i,j;
    printf("Proc.\t Alocado\t Maximo\t Disp.\t");
    for(i=0; i<n; i++)
    {
        printf("\nP%d\t   ",i);
        for(j=0; j<r; j++)
        {
            printf("%d ",alloc[i][j]);
        }
        printf("\t");
        for(j=0; j<r; j++)
        {
            printf("%d ",max[i][j]);
        }
        printf("\t");
        if(i==0)
        {
            for(j=0; j<r; j++)
                printf("%d ",avail[j]);
        }
    }
}




void requisicao()
{
    int i,j;


    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("\n");

}


void libera()
{
    int i,j;
    int finalizado[100],temp,flag=1,k,c1=0;

    for(i=0; i<n; i++)
    {
        finalizado[i]=0;
    }


    while(flag)
    {
        flag=0;
        for(i=0; i<n; i++)
        {
            int c=0;
            for(j=0; j<r; j++)
            {
                if((finalizado[i]==0)&&(need[i][j] <= avail[j]))
                {
                    c++;
                    if(c==r)
                    {
                        for(k=0; k<r; k++)
                        {
                            avail[k]+=alloc[i][j];
                            finalizado[i]=1;
                            flag=1;
                        }
                        printf("P%d->",i);
                        if(finalizado[i]==1)
                        {
                            i=n;
                        }
                    }
                }
            }
        }
    }
    for(i=0; i<n; i++)
    {
        if(finalizado[i]==1)
        {
            c1++;
        }
        else
        {
            printf("P%d->",i);
        }
    }




    if(c1==n)
    {
        printf("\n Estado seguro\n");
    }
    else
    {
        printf("\n Estado inseguro\n");
    }
}
