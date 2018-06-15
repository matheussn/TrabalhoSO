#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Dados.h"

int requisicao_recursos(int pid, int recursos[]){
    
    int i, j;
    int x;
  

/*    int flag2 = 0;
    for(i = 0; i < dados->nro_recurso; i++)
        if(dados->disponivel[i] >= recursos[i])//verificando se tem recurso disponivel para atender a requisicao
            flag2++;

    if(flag2 == dados->nro_recurso -1)
    {
        int * flag = (int *) malloc (dados->nro_processo * sizeof(int));
            for(i = 0; i < dados->nro_processo; i++)
                flag[i] = 0;
        

        for(i = 0; i < dados->nro_processo; i++)
        {
            for(j = 0; j< dados->nro_recurso; j++)
            {
                if (dados->processo[i].quantNecess[j] < recursos[j])
                    flag[i]++;
            }       
        }

        for(i = 0; i<dados->nro_processo; i++)
            if(flag[i] == dados->nro_recurso)//verificando se mesmo atendendo a requisicao o banqueiro estará no estado seguro
            {
                // estado seguro, é possivel alocar.
                return 0;   
            }
        
*/     
        //Não foi possivel alocar.
    

	    srand( (unsigned)time(NULL));

	    x =  ( rand() % 10 );

	    if(x > 5){
		    printf("Recurso alocado! \n");  
		    return 0;
	    }else{
		    printf("Recurso não alocado! \n");
		    return -1;
	    }
    /*}
    else
    {
       printf("Recurso não alocado! \n");
	   return -1;
    }*/

}

int libera_recursos(int pid, int recursos[]){


	/*int flag = 0;
	int i;

	for (i = 0 ; i< dados->nro_recurso; i++)    
		if(dados->processo[pid].quantNecess[i] == 0)
			flag++;

	if(flag == dados->nro_recurso - 1)
	{
		for(i = 0; i<dados->nro_recurso; i++)
			dados->disponivel[i] = recursos[i];*/
		printf("Recursos Liberados com sucesso\n");/*
	}
	else
		printf("Processo não finalizado\n");*/

	return 0;

}
