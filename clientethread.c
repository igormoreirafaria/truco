#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct {    //estrutura utilizada para verificacao
    char valor[2];  //de valor e naipe das cartas
    char naipe[2];
}Carta;

Carta *cartas;

int main(int argc , char *argv[]){
    //declaração e alocação de variaveis
    int sock;                                       
    struct sockaddr_in server;
    char *message , *server_reply;
    server_reply = calloc(sizeof(char), 2000);
    message = malloc(1000 * sizeof(char));
    char *id = malloc(3 * sizeof(char));
    
    printf("Digite id de jogador: \n"); //pega o id do usuario
    fgets(id, 3, stdin);

    int id_jogador = atoi(id); //transforma o id em inteiro
    cartas = (Carta*)malloc(3 * sizeof(Carta)); //aloca espaço para variavel cartas

    sock = socket(AF_INET , SOCK_STREAM , 0); // cria o socket
    if (sock == -1){
        printf("Nao foi possivel criar o socket");
    }
    puts("Socket criado");

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //configura qual servidor
    server.sin_family = AF_INET;                     //havera a conexao
    server.sin_port = htons( 8081 );


    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){ //tenta conectar 
        perror("Erro, falha na conexao");                                 //ao servidor
        return 1;
    }

    puts("Conectado\n");

    int primeiro_turno = 1;
   
    while(1){
        //se for o primeiro turno, espera o servidor enviar as cartas
        if( (recv(sock , server_reply , 2000 , 0) < 0) && primeiro_turno == 1){
            puts("Falha ao receber mensagem");
            break;
        }
        puts(server_reply);
        server_reply = calloc(sizeof(char), 2000);//zera a variavel para ser usada depois



        for(;id_jogador > 0; id_jogador --) { //laço for que fica escutando o broadcas
                                              // do servidor enquanto não for a vez de jogar
            if( recv(sock , server_reply , 2000 , 0) < 0){ //recebe o broadcast
                puts("Falha ao receber mensagem");
                break;
            }
            puts("Carta jogada:");
            puts(server_reply);//imprime a carta recebida do broadcast
            server_reply = calloc(sizeof(char), 2000);//zera a variavel para ser usada depois
        }

        printf("Escolha uma carta: ");//pega a carta escolhida pelo 
        fgets(message, 1000, stdin ); //usuario para ser jogada

        if(send(sock , message , strlen(message) , 0) < 0){//envia a carta escolhida pelo usuario
            puts("Falha ao enviar");
            return 1;
        }
        id_jogador = 3;
        primeiro_turno = 0;
    }

    close(sock);
    return 0;
}
