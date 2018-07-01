# Trabalho de SO - 2018/1

O objetivo desse trabalho é implementar de forma simples o algoritmo do banqueiro em C, simulando multiplos processos realizando requisições e liberação de recursos.<br>

O programa permite a criação de cenários dinâmicos de quantidade de recursos, numero de recursos, numero de processos, quantidade de recurso que cada processo precisa e também permite limitar a quantidade de recurso de cada processo dado uma porcentagem em relação a quantidade de recursos.<br>

Para compilar o programa é usado o makeFile, segue o comando:<br>
make -f banqueiro.1

O programa pode ser executado das seguintes maneiras:
<br><br>
$ ./banqueiro -n <-num_processos-> -a <-vet_alocação-> <br>
$ ./banqueiro -n <-num_processos-> -p <-porcentagem-> -a <-vet_alocação-> <br>

Em que num_processos é o número de processos a serem simulados por meio de threads, vet_alocação é o vetor disponivel com o numero de recursos de cada tipo que são disponiveis para simulação dos processos e porcentagem é a porcentagem limite para que ao gerar os recursos que cada thread precisa para concluir, seja limitado a essa porcentagem dos recursos passados no vet_alocação. <br>
Caso a porcentagem não seja enviada, consideramos uma porcentagem default de 100%. <br>
Veja alguns exemplos de execução:
<br><br>
$ ./banqueiro -n 5 -a 25 20 30<br>
Isso significa simular 5 processos (threads) e um sistema que, inicialmente, tem 25 cópias do recurso 1 disponível, 25 cópias do recurso 2 e 30 cópias do recurso 3.<br>
(Veja uma saída para essa execução no arquivo execucao1.txt)
<br><br>
$ ./banqueiro -n 5 -p 0.7 -a 25 20 30<br>
Isso significa simular 5 processos (threads) e um sistema que, inicialmente, tem 25 cópias do recurso 1 disponível, 25 cópias do recurso 2 e 30 cópias do recurso 3, porém cada uma das 5 threads só poderá ter seu total de recursos limitados a 0.7 (ou 70%) dos recursos totais disponíveis no sistema.<br>
(Veja uma saída para essa execução no arquivo execucao2.txt)<br>
Perceba que mesmo colocando uma porcentagem alta, o sistema entra em harmonia em determinado ponto, pois nunca entrará no estado inseguro.<br>

A estrutura de pastas atual do trabalho é: <br>
/TrabalhoSO<br>
 ├ ┬ exemplos<br>
 │ ├── execucao1.txt<br>
 │ └── execucao2.txt<br>
 ├ ┬ programa<br>
 │ ├── Banqueiro.c<br>
 │ ├── Banqueiro.h<br>
 │ ├── Dados.c<br>
 │ ├── Dados.h<br>
 │ ├── Processos.c<br>
 │ ├── Processos.h<br>
 │ ├── banqueiro.1<br>
 │ └── sistema.c<br>
 └── README.md<br>

Segue uma breve explicação de cada arquivo do diretório "programa":<br>

O arquivo banqueiro.1 é um arquivo make que é utilizado para compilar os arquivos .c, para gerar o arquivo executável do programa. Para executá-lo basta digitar o comando "make -f banqueiro.1", assim será gerado um arquivo chamado "banqueiro". Para executar o programa, re-leia as instruções no inicio deste arquivo.<br>

O arquivo Banqueiro.c contém a implementação das funções requisicao_recursos e liberaçao_recursos( ), que empregados pelo algoritmo do banqueiro, permite determinar se o resultado da requisição é segura ou insegura. Possui o arquivo .h para definição das funções que serão empregadas no arquivo .c<br>

O arquivo Processos.c contém funções que serão usadas pelas threads simuladas, como a função que retorna o pid simbólico de cada thread (init_Thread()), a função que verifica se existe somente uma thread ativa (kill_thread()), seu nome é simbólico pois ela matará o processo inteiro caso exista somente uma thread ativa, temos as funções de tratam a randomização da liberação e a requisição de recursos (rand_lib() e rand_req()) e por ultimo temos a função que verifica se a thread tem todos os recursos que ela precisa alocados, caso ela tenha essa função faz a thread dormir por um tempo randomico de 0 à 10 segundos, quando acaba esse tempo ela volta para execução. Possui o arquivo .h para definição das funções que serão empregadas no arquivo .c<br>

O arquivo sistemas.c contém a funcao main() que controla todo o processo inicialmente. A função threads() que é o corpo das threads simuladas. A função atribuiArgumentos() que como nosso programa possui duas possibilidades de entrada foi preciso criar uma função para controlar quais atribtos seriam atribuidos em tempo de execução. <br>

O arquivo Dados.h define duas estruturas (struct) uma para armazenar o que cada thread precisa, como o vetor de alocação, seu status, etc, e outra pra armazenar os dados do programa (dados), como a quantidade de processos, de recursos, etc. Nesse arquivo definimos o escopo de funções que serão implementadas no arquivo Dados.c, funções estas para inicializar, ou seja Alocar memória, para salvar os dados do programa e de cada thread, e uma função para gerar valores randomicos (randomico()), esse função é utilizada pelos outros arquivos. E a parte mais importante do arquivo, que é a definição de uma variavel do tipo struct dados com escopo global, essa variável é acessada pelo arquivo Banqueiro.c, pois com ela, você possui todos os dados do processo, bem como os dados de cada uma das threads, permitindo assim ao banqueiro saber se está estrando no estado inseguro ou não. <br>

Esse trabalho foi realizado pelos alunos: <br>
	<strong>Mateus Benedini de Oliveira Santiago Prates </strong> - 11621BSI200<br>
	<strong>Matheus Santiago Neto  </strong>- 11621BSI252<br>

Segue abaixo o link do projeto do trabalho no github: <br>
https://github.com/matheussn/TrabalhoSO <br>
