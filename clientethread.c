#include<stdio.h> 
#include<string.h>    
#include<sys/socket.h>    
#include<arpa/inet.h> 
#include<unistd.h>
#include<stdlib.h>

typedef struct {
    char valor[2];
    char naipe[2];
}Carta;

Carta *cartas;

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char *message , *server_reply;
    server_reply = calloc(sizeof(char), 2000);
    message = malloc(1000 * sizeof(char));
    char *id = malloc(3 * sizeof(char));
    printf("Digite id de jogador: \n");
    fgets(id, 3, stdin);

    int id_jogador = atoi(id);
    cartas = (Carta*)malloc(3 * sizeof(Carta));
   
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Nao foi possivel criar o socket");
    }
    puts("Socket criado");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8080 );
 
   
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Erro, falha na conexao");
        return 1;
    }
     
    puts("Conectado\n");
     
    int primeiro_turno = 1;
    
    while(1)
    {
        if( (recv(sock , server_reply , 2000 , 0) < 0) && primeiro_turno == 1){
            puts("falha ao receber msg");
            break;
        }
        puts("Cartas: ");
        puts(server_reply);
        server_reply = calloc(sizeof(char), 2000);


        
        for(;id_jogador > 0; id_jogador --) {
            
            if( recv(sock , server_reply , 2000 , 0) < 0){
                puts("falha ao receber msg");
                break;
            }
            puts("Carta jogada:");
            puts(server_reply);
            server_reply = calloc(sizeof(char), 2000);
        }


        printf("Escolha uma carta: ");
        fgets(message, 1000, stdin );
        
      
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("falha ao enviar");
            return 1;
        }
         
        id_jogador = 3;
        primeiro_turno = 0;
    }
     
    close(sock);
    return 0;
}