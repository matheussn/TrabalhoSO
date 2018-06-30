
Integrantes:
Mateus Benedini de Oliveira Santiago Prates - 11621BSI200
Matheus Santiago Neto - 11621BSI252

O objetivo desse trabalho é implementar de forma simples o algoritmo do banqueiro em C, simulando multiplos processos realizando requisições e liberação de recursos.
O programa permite a criação de cenários dinâmicos de quantidade de recursos, numero de recursos, numero de processos, quantidade de recurso que cada processo precisa e também permite limitar a quantidade de recurso de cada processo dado uma porcentagem em relação a quantidade de recursos.
O programa pode ser executado das seguintes maneiras:

$ ./banqueiro -n <num_processos> -a <vet_alocação>
$ ./banqueiro -n <num_processos> -p <porcentagem> -a <vet_alocação>

Em que num_processos é o número de processos a serem simulados por meio de threads, vet_alocação é o vetor disponivel com o numero de recursos de cada tipo que são disponiveis para simulação dos processos e porcentagem é a porcentagem limite para que ao gerar os recursos que cada thread precisa para concluir, seja limitado a essa porcentagem dos recursos passados no vet_alocação.
Caso a porcentagem não seja enviada, consideramos uma porcentagem default de 100%.
Veja alguns exemplos de execução:

$ ./banqueiro -n 5 -a 25 20 30
Isso significa simular 5 processos (threads) e um sistema que, inicialmente, tem 25 cópias do recurso 1 disponível, 25 cópias do recurso 2 e 30 cópias do recurso 3.
(Veja uma saída para essa execução no arquivo execucao1.txt)

$ ./banqueiro -n 5 -p 0.7 -a 25 20 30
Isso significa simular 5 processos (threads) e um sistema que, inicialmente, tem 25 cópias do recurso 1 disponível, 25 cópias do recurso 2 e 30 cópias do recurso 3, porém cada uma das 5 threads só poderá ter seu total de recursos limitados a 0.7 (ou 70%) dos recursos totais disponíveis no sistema.
(Veja uma saída para essa execução no arquivo execucao2.txt)
Perceba que mesmo colocando uma porcentagem alta, o sistema entra em harmonia em determinado ponto, pois nunca entrará no estado inseguro.