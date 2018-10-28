/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include<stdlib.h>
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char *message , server_reply[2000];
    message = malloc(1000 * sizeof(char));
    char *id = malloc(3 * sizeof(char));
    printf("digite id de jogador: \n");
    fgets(id, 3, stdin);

    int id_jogador = atoi(id);

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8080 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
        
        for(;id_jogador > 0; id_jogador --) {
            //Receive a reply from the server
            if( recv(sock , server_reply , 2000 , 0) < 0){
                puts("recv failed");
                break;
            }
            puts("Server reply :");
            puts(server_reply);

        }


        printf("Enter message : ");
        fgets(message, 1000, stdin );
        
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        // //Receive a reply from the server
        // if( recv(sock , server_reply , 2000 , 0) < 0)
        // {
        //     puts("recv failed");
        //     break;
        // }
         
        id_jogador = 4;
    }
     
    close(sock);
    return 0;
}