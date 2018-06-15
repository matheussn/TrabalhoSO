#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Dados.h"

int requisicao_recursos(int pid, int recursos[]){
    
    int i, j;
    int x;
 /*   
    int * flag = (int *) malloc (nro_processo * sizeof(int));
        for(i = 0; i < nro_processo; i++)
            flag[i] = 0;
    

    for(i = 0; i < dados->nro_processo; i++)
    {
        for(j = 0; j< dados->nro_recurso; j++)
        {
            if (dados->processos[i].quantNecess[j] < recursos[j])
                flag[i]++;        
        }       
    }

    for(i = 0; i<nro_processo; i++)
        if(flag[i] == nro_recurso)
        {
            // estado seguro, é possivel alocar.
            return -1;   
        }
    
    
    //Não foi possivel alocar.
*/

	srand( (unsigned)time(NULL));

	x =  ( rand() % 10 );

	if(x > 5){
		printf("Recurso alocado! \n");
		return 0;
	}else{
		printf("Recurso não alocado! \n");
		return -1;
	}
}

int libera_recursos(int pid, int recursos[]){


//    int flag = 0

/*    for (int i = 0 ; i< nro_recurso; i++)    
        if(dados->processo.quantNecess[i] == 0)
            flag++;
*/    
//    if(flag == nro_recurso - 1)
        printf("Recursos Liberados com sucesso\n");
//    else
//        printf("Processo não finalizado\n");









	
	return 0;

}
