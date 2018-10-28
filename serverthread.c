#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include "server.h"

void *connection_handler(void *);

int check_recursivo(Carta *baralho);
Carta vetor_de_cartas[4];
int client_sock[4];
Carta *baralho;
int cont = 0;


int main(int argc , char *argv[]){
    int socket_desc , c , *new_sock;
    struct sockaddr_in server , client;

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_desc == -1){
        printf("Nao foi possivel criar socket");
    }
    puts("Socket criado");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8081 );

    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
        perror("Erro");
        return 1;
    }
    puts("bind feito");

    listen(socket_desc , 3);

    puts("Esperando por conexoes...");
    c = sizeof(struct sockaddr_in);


    puts("Esperando por conexoes...");
    c = sizeof(struct sockaddr_in);
    int i = 0;

    baralho = (Carta*)malloc(12 * sizeof(Carta));



    srand(time(NULL));

    for( int j = 0 ; j < 12 ; j++ ){
        baralho[j].valor =  48 + ( rand() % 9 );
    }

    for( int j = 0 ; j < 12 ; j++ ){

        if( baralho[j].valor  == '1' ) baralho[j].valor = 'A';
        if( baralho[j].valor == '8' ) baralho[j].valor = 'J';
        if( baralho[j].valor == '9' ) baralho[j].valor = 'K';
        if( baralho[j].valor == '0' ) baralho[j].valor = 'Q';
    }

    for( int j = 0 ; j < 12 ; j++ ){
        baralho[j].naipe =  97 + ( rand() % 4 );
    }

    for( int j = 0 ; j < 12 ; j++ ){
        if( baralho[j].naipe == 'a' ) baralho[j].naipe = 'p';
        if( baralho[j].naipe == 'b' ) baralho[j].naipe = 'e';
        if( baralho[j].naipe == 'd' ) baralho[j].naipe = 'o';
    }

    int pode_seguir = 1;

    while(pode_seguir == 1){
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

    }


    while(1){
        if( client_sock[i] = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c) ){
            puts("Connection accepted");
        }

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock[i];

        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0){
            perror("Nao foi possivel criar thread");
            return 1;
        }

        puts("Manipulador designado");
        i++;
        if( i == 5 ) i = 0;
    }

    if (client_sock < 0){
        perror("Falhou");
        return 1;
    }

    return 0;
}


int check_recursivo(Carta *baralho){
    for(int i = 0 ; i < 12 ; i++ ){

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


void *connection_handler(void *socket_desc){
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , *client_message, **client_cards;
    message = calloc(sizeof(char), 2000);
    client_message = calloc(sizeof(char), 2000);
    client_cards = malloc(4 * sizeof(char*));
    for(int i = 0 ; i < 4 ; i++){
        client_cards[i] =  malloc(2000 * sizeof(char));
    }


    sprintf(client_cards[0], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[0].valor, baralho[0].naipe,
                                                                              baralho[1].valor, baralho[1].naipe,
                                                                              baralho[2].valor, baralho[2].naipe);

    sprintf(client_cards[1], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[3].valor, baralho[3].naipe,
                                                                              baralho[4].valor, baralho[4].naipe,
                                                                              baralho[5].valor, baralho[5].naipe);

    sprintf(client_cards[2], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[6].valor, baralho[6].naipe,
                                                                              baralho[7].valor, baralho[7].naipe,
                                                                              baralho[8].valor, baralho[8].naipe);

    sprintf(client_cards[3], " |carta %c %c| |carta %c %c|| |carta %c %c|| ", baralho[9].valor, baralho[9].naipe,
                                                                              baralho[10].valor, baralho[10].naipe,
                                                                              baralho[11].valor, baralho[11].naipe);

    for( int i = 0 ; i < 4 ; i++ ){
        if( sock == client_sock[i]){
            write(sock , client_cards[i] , strlen(client_cards[i]));
        }
    }


    char *token;

    int dupla;
    int dupla1=0;
    int dupla2=0;


    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ){
        strcpy(message, client_message);
        token = strtok(message, " ");

        vetor_de_cartas[cont].valor = token[0];

        token = strtok(NULL, " ");
        vetor_de_cartas[cont].naipe = token[0];
        message = calloc(sizeof(char), 2000);

        for(int i = 0 ; i < 4 ; i++){

            write(client_sock[i] , client_message , strlen(client_message));

        }

        client_message = calloc(sizeof(char), 2000);
        cont++;
        printf("%d\n", cont);
        if(cont == 4){
            for(int i = 0 ; i < 4 ; i++){
                printf("valor %c naipe %c\n", vetor_de_cartas[i].valor, vetor_de_cartas[i].naipe);
            }
            regras(vetor_de_cartas);
            dupla = retorna_vencedor();
            if(dupla == 1){
                dupla1 = dupla1 + 2;
            }else if(dupla == 2){
                dupla2 = dupla2 + 2;
            }

            cont = 0;
        }
    }

    if(read_size == 0){
        puts("Cliente desconectado");
        fflush(stdout);
    }
    else if(read_size == -1){
        perror("Recebimento falhou");
    }

    free(socket_desc);

    return 0;
}
