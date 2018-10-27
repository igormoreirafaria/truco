#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>
typedef struct{
    char valor;
    char naipe;
}carta;

int main(int argc , char *argv[]){

	int sock;
    struct sockaddr_in servidor;
    int id_jogador;
    char *buf;
    buf = malloc(4 * sizeof(char));

    printf("Qual seu id de jogador: ");
    scanf("%d", &id_jogador);
    //Cria um socket


    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("nao foi possivel criar o socket");
    }
    printf("Socket criado\n");



    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons( 8081 );

    //conectar a um servidor
    if (connect(sock , (struct sockaddr *)&servidor , sizeof(servidor)) < 0) {
        printf("Erro, nao foi possivel conectar ao servidor.");
        return 1;
    }

    for(;;){
        carta jogada;
        for(;id_jogador > 0; id_jogador --){
            recv(sock, buf, 4, 0);
            
            printf("%s\n", buf);
        }
        printf("Digite sua carta: ");
        fgets(buf, 4, stdin);
        buf[strlen(buf)] = '\0';
        fgets(buf, 4, stdin);
        buf[strlen(buf)] = '\0';

        send(sock, buf, 4, 0);

        recv(sock, buf, 4, 0);
   
        printf("Sua carta: %s\n", buf);

        id_jogador = 3;
    }

    //continuar comunicacao com o servidor


    return 0;
}
