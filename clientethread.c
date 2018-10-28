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
    int id_jogador = atoi(argv[2]);
    char buf[2];

    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) return 1;

    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(atoi(argv[1]));

    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) return 1;

    for(;;){
        carta jogada;
        for(;id_jogador > 0; id_jogador --) {
            recv(sock, buf, 2, 0);
            jogada.valor = buf[0];
            jogada.naipe = buf[1];
            printf("%c %c \n", jogada.valor, jogada.naipe);
        }

        printf("Digite sua carta\n");
        scanf("%c %c", &jogada.valor, &jogada.naipe);
        buf[0] = jogada.valor;
        buf[1] = jogada.naipe;

        printf("enviando: %c %c\n", jogada.valor, jogada.naipe);

        send(sock, buf, 2, 0);

        recv(sock, buf, 2, 0);
        jogada.valor = buf[0];
        jogada.naipe = buf[1];
        printf("Sua carta: %c %c \n", jogada.valor, jogada.naipe);

        id_jogador = 3;
    }
    return 0;
}
