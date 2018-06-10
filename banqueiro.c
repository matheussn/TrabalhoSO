#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<unistd.h> 

int max[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int n,r;
void showAll();
void requisicao_e_libera();
int randomico();








int main()
{
    int i,j;
    int a;
    
    n = 6;
    

    printf("Numero de Clientes\t %i \n", n);
    
    r = 3;
 
    printf("Numero de Recursos\t %i\n", r);

    printf("Quantidade de recursos que cada Cliente precisa para ser terminado\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {
            max[i][j] = randomico();
            printf("%d ",max[i][j]);
        }
        printf("\n");
    }
    printf("Quantidade de recursos que cada Cliente possui\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {

            int a = randomico();

            if(a <= max[i][j])
            {
                alloc[i][j] = a;    
                printf("%d ",alloc[i][j]);
            }
            else
                j--;
        }
        printf("\n");
    }
    printf("Quantidade de recursos disponíveis\n");
  
        avail[0] =  3;     
        avail[1] =  3;
        avail[2] =  2;
        printf("%i %i %i ", avail[0], avail[1], avail[2]);
    
    printf("\n");



    

    showAll();
    requisicao_e_libera();
    return 0;
}



int randomico()
{
   
     sleep(1);
    int i, x,s;
      for(i=1 ; i <= 11 ; i++)
      {  
         srand( (unsigned)time(NULL));
           
          x = 1 + ( rand() % 10 );
       }
       return x;
}


void input()
{
    int i,j;
    int a;
    
    n = 6;
    

    printf("Numero de Clientes\t %i \n", n);
    
    r = 3;
 
    printf("Numero de Recursos\t %i\n", r);

    printf("Quantidade de recursos que cada Cliente precisa para ser terminado\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {
            max[i][j] = randomico();
            printf("%d ",max[i][j]);
        }
        printf("\n");
    }
    printf("Quantidade de recursos que cada Cliente possui\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {

            int a = randomico();

            if(a <= max[i][j])
            {
                alloc[i][j] = a;    
                printf("%d ",alloc[i][j]);
            }
            else
                j--;
        }
        printf("\n");
    }
    printf("Quantidade de recursos disponíveis\n");
  
        avail[0] =  3;     
        avail[1] =  3;
        avail[2] =  2;
        printf("%i %i %i ", avail[0], avail[1], avail[2]);
    
    printf("\n");

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
void requisicao_e_libera()
{
    int finalizado[100],temp,flag=1,k,c1=0;
    int safe[100];
    int i,j;
    for(i=0; i<n; i++)
    {
        finalizado[i]=0;
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("\n");

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
        printf("\n Ocorreu um Dead lock");
        printf("\n Estado inseguro\n");
    }
}
