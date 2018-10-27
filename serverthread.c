#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h> //inet_addr
typedef struct{
    char buf[4];
    char valor;
    char naipe;
}carta;

carta atual[4]; //carta a ser recebida
carta ultima_enviada[4]; //ultima carta recebida
carta ultima_recebida[4]; //ultima carta recebida
intptr_t conexao[4]; //jogador

void * thread_enviada(void * arg) {
	int jogador = *((int *) arg);
	char buf[4];
	for (;;) {
		if(ultima_enviada[jogador].valor != '-'){
            strcpy(buf, ultima_enviada[jogador].buf);
            // buf[0] = ultima_enviada[jogador].valor;
            // buf[2] = ultima_enviada[jogador].naipe;

            int enviado = send(conexao[jogador], buf, 4, 0);
            if(enviado != 2){
                printf("ERRO\n");
                exit(1);
            }
            strcpy(ultima_enviada[jogador].buf, " ");
            ultima_enviada[jogador].valor = '-';
            ultima_enviada[jogador].naipe = '-';        }
	}
    close(conexao[jogador]);
	return NULL;
}

void * thread_recebida(void * arg){
	int jogador = *((int *) arg);
	char buf[4];
	for (;;){
        int recebido = recv(conexao[jogador], buf, 4, 0);
        if(recebido < 0){
            printf("ERRO\n");
            exit(1);
        }
        strcpy(atual[jogador].buf, buf);
        atual[jogador].valor = buf[0];
        atual[jogador].naipe = buf[2];
    }
	close(conexao[jogador]);
	return NULL;
}

/*int maior(carta carta1, carta carta2){
    if(carta1.valor = 4 && carta1.naipe = p) return 1;
    if(carta2.valor = 4 && carta2.naipe = p) return 2;

    if(carta1.valor = 4 && carta1.naipe = p) return 1;
    if(carta2.valor = 4 && carta2.naipe = p) return 2;

}*/


int main(){

    int jogadores[4] = {0, 1, 2, 3};



	int escuta = socket(AF_INET, SOCK_STREAM, 0);
    if(escuta < 0) return 1;

    int c;
    struct sockaddr_in endereco, cliente[4];

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons( 8081 );

    socklen_t tamanho_endereco = sizeof(endereco);

   if( bind(escuta,(struct sockaddr *)&endereco , sizeof(endereco)) < 0){
        //print the error message
        perror("Erro, nao foi possivel ligar o socket ao servidor.");
        return 1;
    }
    printf("Escutando na porta %d\n", htons(endereco.sin_port));

    if(listen(escuta, 100) < 0) return 1;


	for (int i = 0; i < 4; i++) {
        
        c = sizeof(struct sockaddr_in);
        conexao[i] = accept(escuta, (struct sockaddr *)&cliente[i], (socklen_t*)&c);
        if (conexao[i] < 0){
            perror("conexao falhou");
            return 1;
        }
        printf("Conexao aceita cliente %d\n", i);
		pthread_t thread_envia, thread_recebe;

        ultima_enviada[i].naipe = ultima_enviada[i].valor = atual[i].naipe = atual[i].valor = '-';

		if(pthread_create(&thread_envia, NULL, thread_enviada, (void*) &(jogadores[i])) != 0) return 1;
        if(pthread_create(&thread_recebe, NULL, thread_recebida, (void*) &(jogadores[i])) != 0) return 1;
	}



    int turno_atual = 0;
    int pontuacao1 = 0, pontuacao2 = 0;
    //jogo
    while(pontuacao1 < 12 || pontuacao2 < 12){
        if(atual[turno_atual].valor != '-'){
            for(int i = 0; i < 4; i++){
                strcpy(ultima_enviada[i].buf, atual[turno_atual].buf);
                ultima_enviada[i].valor = atual[turno_atual].valor;
                ultima_enviada[i].naipe = atual[turno_atual].naipe;
            }
            atual[turno_atual].naipe = atual[turno_atual].valor = '-';
            
            while(ultima_enviada[0].valor != '-');
            while(ultima_enviada[1].valor != '-');
            while(ultima_enviada[2].valor != '-');
            while(ultima_enviada[3].valor != '-');

            turno_atual = (turno_atual + 1) % 4;
        }
    }

    printf("%ld ", sizeof(carta));
	return 0;
}
