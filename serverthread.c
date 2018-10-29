#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include "server.h"

void *nova_conexao(void *);

int check_recursivo(Carta *baralho);
Carta vetor_de_cartas[4]; //vetor de cartas recebidas dos clientes
int client_sock[4]; //vetor de sockets
Carta *baralho;
int cont = 0; //contagem de turno


int main(int argc , char *argv[]){
    //declaracao de variaveis
    int socket_desc , c , *new_sock;
    struct sockaddr_in server , client;
    
    //cria um socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
        printf("Nao foi possivel criar socket");
    }
    puts("Socket criado");

    //criacao do servidor
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );

    //ligando o socket ao servidor
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
        perror("Erro");
        return 1;
    }
    puts("ligacao feita");

    //seta o socket para aceitar conexoes
    listen(socket_desc , 3);

    puts("Esperando por conexoes...");
    c = sizeof(struct sockaddr_in);

    
    //gera o baralho a ser usado
    baralho = (Carta*)malloc(12 * sizeof(Carta));

    srand(time(NULL));

    for( int j = 0 ; j < 12 ; j++ ){
        baralho[j].valor =  48 + ( rand() % 9 );
    }

    for( int j = 0 ; j < 12 ; j++ ){
        //como no truco não tem cartas 1 e tem cartas k, j e q, 
        //há a mudança nos caracteres para identificao das cartas
        if( baralho[j].valor  == '1' ) baralho[j].valor = 'A';
        if( baralho[j].valor == '8' ) baralho[j].valor = 'J';
        if( baralho[j].valor == '9' ) baralho[j].valor = 'K';
        if( baralho[j].valor == '0' ) baralho[j].valor = 'Q';
    }

    for( int j = 0 ; j < 12 ; j++ ){
        baralho[j].naipe =  97 + ( rand() % 4 );
    }

    for( int j = 0 ; j < 12 ; j++ ){
        //mudanca para identificar os naipes das cartas
        //'c' já seria umas das letras no rand, portanto não foi
        //necessario mudar de 'c' pra 'c'
        if( baralho[j].naipe == 'a' ) baralho[j].naipe = 'p';
        if( baralho[j].naipe == 'b' ) baralho[j].naipe = 'e';
        if( baralho[j].naipe == 'd' ) baralho[j].naipe = 'o';
    }

    //loop para verificar se há cartas repetidas no baralho
    //e para remover e gerar cartas novas no lugar das repetidas
    int pode_seguir = 1;
    while(pode_seguir == 1){ //inicio do while
        for(int i = 0 ; i < 12 ; i++ ){

            for( int j = i+1 ; j < 12 ; j++ ){

                if( baralho[j].valor == baralho[i].valor ){
                    if( baralho[j].naipe == baralho[i].naipe ){

                        if( baralho[j].naipe == 'p' || baralho[j].naipe == 'c' || baralho[j].naipe == 'e') {
                            baralho[j].naipe = 'o';
                            printf("chegou 1\n");
                            break;
                        }
                        if( baralho[j].naipe == 'c' || baralho[j].naipe == 'e' || baralho[j].naipe == 'o'){
                            baralho[j].naipe = 'p';
                            printf("chegou 2\n");
                            break;
                        }
                        if( baralho[j].naipe == 'e' || baralho[j].naipe == 'o' || baralho[j].naipe == 'p'){
                            baralho[j].naipe = 'e';
                            printf("chegou 3\n");
                            break;
                        }
                        if( baralho[j].naipe == 'o' || baralho[j].naipe == 'p' || baralho[j].naipe == 'e'){
                            baralho[j].naipe = 'c';
                            printf("chegou 4\n");
                            break;
                        }

                    }
                }
            }
        }
        pode_seguir = check_recursivo(baralho);
    }// fim do while

    int i = 0;
    while(1){
        //aceita uma nova conexão e atribui ao client_sock[i] o endereço do socket onde ocorrerá a comunicação
        if( client_sock[i] = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c) ){
            puts("Conexao aceita");
        }

        pthread_t xablau; //declaração da thread
        new_sock = malloc(1);
        *new_sock = client_sock[i]; //atribuição para passar o socket como um
                                    //argumento na função a ser disparada pela thread
        if( pthread_create( &xablau , NULL ,  nova_conexao , (void*) new_sock) < 0){ //dispara a thread
            perror("Nao foi possivel criar thread");
            return 1;
        }
        puts("thread rodando");
        i++;
        if( i == 5 ) i = 0;
    }

    if (client_sock[i] < 0){
        perror("Falhou");
        return 1;
    }

    return 0;
}


int check_recursivo(Carta *baralho){ 
    for(int i = 0 ; i < 12 ; i++ ){ //verifica se há cartas repetidas no baralho

        Carta carta = baralho[i];

        for( int j = i+1 ; j < 12 ; j++ ){

            if( baralho[j].valor == carta.valor ){
                if( baralho[j].naipe == carta.naipe ){
                    return 1;
                }
            }
        }
    }
    return 0;
}


void *nova_conexao(void *socket_desc){
    int sock = *(int*)socket_desc; //atrinui o socket para comunicar com o cliente à variavel sock
    int read_size;
    
    char *messagem , *menssagem_cliente, **cartas_cliente; //variaveis que serao utilizadas na troca de mensagens
    
    messagem = calloc(sizeof(char), 2000);
    menssagem_cliente = calloc(sizeof(char), 2000);
    cartas_cliente = malloc(4 * sizeof(char*));
   
    for(int i = 0 ; i < 4 ; i++){
        cartas_cliente[i] =  malloc(2000 * sizeof(char));
    }

    //atribui as cartas geradas a uma variavel que será enviada para o cliente 0
    sprintf(cartas_cliente[0], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[0].valor, baralho[0].naipe,
                                                                              baralho[1].valor, baralho[1].naipe,
                                                                              baralho[2].valor, baralho[2].naipe);
    //atribui as cartas geradas a uma variavel que será enviada para o cliente 1
    sprintf(cartas_cliente[1], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[3].valor, baralho[3].naipe,
                                                                              baralho[4].valor, baralho[4].naipe,
                                                                              baralho[5].valor, baralho[5].naipe);
    //atribui as cartas geradas a uma variavel que será enviada para o cliente 2
    sprintf(cartas_cliente[2], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[6].valor, baralho[6].naipe,
                                                                              baralho[7].valor, baralho[7].naipe,
                                                                              baralho[8].valor, baralho[8].naipe);
    //atribui as cartas geradas a uma variavel que será enviada para o cliente 3
    sprintf(cartas_cliente[3], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[9].valor, baralho[9].naipe,
                                                                              baralho[10].valor, baralho[10].naipe,
                                                                              baralho[11].valor, baralho[11].naipe);

    //laço for que envia as cartas geradas aos clientes
    for( int i = 0 ; i < 4 ; i++ ){
        if( sock == client_sock[i]){ //para não enviar para todos os clientes, ha a verificacao dentro da thread
            write(sock , cartas_cliente[i] , strlen(cartas_cliente[i])); //escreve no socket, enviando
        }
    }

    char *token; //token a ser utilizado na strtok

    int dupla;    //variaveis que
    int dupla1=0; //fazem parte da
    int dupla2=0; //pontuação do jogo


    while( (read_size = recv(sock , menssagem_cliente , 2000 , 0)) > 0 ){ //escuta no sock para receber msg do cliente
        strcpy(messagem, menssagem_cliente); //strcpy para fazer uma copia e manipular a variavel da copia
        token = strtok(messagem, " "); //quebra a mensagem recebida do cliente

        vetor_de_cartas[cont].valor = token[0]; // atribui o valor da carta para um vetor de cartas que será
                                                //usado para contabilizar os ponos
        
        token = strtok(NULL, " ");              //atribui o naipe da carta para um vetor de cartas que será
        vetor_de_cartas[cont].naipe = token[0];//usado para contabilizar os ponos
        
        messagem = calloc(sizeof(char), 2000); // zera a variavel para ser reutilizada

        for(int i = 0 ; i < 4 ; i++){ //laço for que realiza o broadcast para todos os clientes conectados

            write(client_sock[i] , menssagem_cliente , strlen(menssagem_cliente));

        }

        menssagem_cliente = calloc(sizeof(char), 2000); // zera a variavel para ser reutilizada
        cont++;  //variavel que determina de quem é a vez na rodada
        if(cont == 4){
            for(int i = 0 ; i < 4 ; i++){
                printf("valor %c naipe %c\n", vetor_de_cartas[i].valor, //imprime as cartas jogadas na rodada no servidor
                vetor_de_cartas[i].naipe);
            }
            
            regras(vetor_de_cartas); //funcao que verifica quem venceu a rodada
            dupla = retorna_vencedor(); //funcao que busca o resultado de quem venceu a rodada
            
            if(dupla == 1){             //atribução de pontos se a dupla 1 vencer
                dupla1 = dupla1 + 2;    
            }else if(dupla == 2){       //atribução de pontos se a dupla 2 vencer
                dupla2 = dupla2 + 2;
            }
            printf("Dupla 1: %d pontos\n", dupla1 );
            printf("Dupla 2: %d pontos\n", dupla2 );
            cont = 0; //zera o conador para uma nova rodada
        }
    }

    if(read_size == 0){  //identifica se o cliente ainda está conectado
        puts("Cliente desconectado");
        fflush(stdout);
    }
    else if(read_size == -1){ //identifica se houve erro ao receber a mensagem do cliente
        perror("Recebimento falhou");
    }

    free(socket_desc);

    return 0;
}
