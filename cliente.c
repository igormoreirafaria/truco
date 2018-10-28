#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

int main(int argc , char *argv[]){

	int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Cria um socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("nao foi possivel criar o socket");
    }
    puts("Socket criado");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8080 );

    //Conecta a um servidor
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
        perror("Erro, nao foi possivel conectar ao servidor.");
        return 1;
    }

    puts("Connected\n");

    //Persiste comunicacao com o servidor
    while(1){
        printf("Enter message : ");
        scanf("%s" , message);

        if(send(sock , message , strlen(message)+1 , 0) < 0){
            puts("Falha ao enviar");
            return 1;
        }

        if(recv(sock , server_reply , 2000 , 0) < 0){
            puts("Falha ao receber");
            break;
        }

        puts("Resposta do servidor :");
        puts(server_reply);
    }

    close(sock);

    return 0;
}
