#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

typedef struct{
    char valor;
    char naipe;
}carta;

int main(int argc , char *argv[]){

	int sock;
    struct sockaddr_in servidor;
    int id_jogador;
    char buf[2];

    printf("Qual seu id de jogador");
    scanf("%d", &id_jogador);
    //Cria um socket


    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("nao foi possivel criar o socket");
    }
    printf("Socket criado");



    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons( atoi(argv[1]));

    //conectar a um servidor
    if (connect(sock , (struct sockaddr *)&servidor , sizeof(servidor)) < 0) {
        printf("Erro, nao foi possivel conectar ao servidor.");
        return 1;
    }

    for(;;){
        carta jogada;
        for(;id_jogador > 0; id_jogador --){
            recv(sock, buf, 2, 0);
            jogada.valor = buf[0];
            jogada.naipe = buf[1];
            printf("%c %c \n", jogada.valor, jogada.naipe);
        }
        printf("Digite sua carta\n");
        scanf("%c %c\n", &jogada.valor, &jogada.naipe);
        buf[0] = jogada.valor;
        buf[1] = jogada.naipe;

        send(sock, buf, 2, 0);

        recv(sock, buf, 2, 0);
        jogada.valor = buf[0];
        jogada.naipe = buf[1];
        printf("Sua carta: %c %c \n", jogada.valor, jogada.naipe);

        id_jogador = 3;
    }

    //continuar comunicacao com o servidor


    return 0;
}
