#include "server.h"
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
int main(int argc , char *argv[]){
   
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    //cria um socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
        printf("nao foi possivel criar o socket");
    }
    puts("Socket criado");

    //prepara a struct sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );

    //liga o socket ao servidor
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
        //print the error message
        perror("Erro, nao foi possivel ligar o socket ao servidor.");
        return 1;
    }
    puts("Ligacao feita");

    //servidor fica escutando no socket
    listen(socket_desc , 3);

    //aceita conexões
    puts("Esperando conexões futuras");
    c = sizeof(struct sockaddr_in);

    //aceita conexão de um cliente futuro
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("conexao falhou");
        return 1;
    }
    puts("Conexao aceita");

    //recebe mensagem do cliente
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //retorna mensagem pro cliente
        write(client_sock , client_message , strlen(client_message));
        write(client_sock , client_message , 1);
    }
     
    if(read_size == 0)
    {
        puts("Cliente disconectou");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("falha ao receber");
    }

    return 0;
}