#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h> //inet_addr


typedef struct{
    char valor;
    char naipe;
}carta;

carta atual[4]; //carta a ser recebida
carta ultima_enviada[4]; //ultima carta recebida
intptr_t conexao[4]; //jogador

void * thread_enviada(void * arg) {
  int jogador = *((int *) arg);
  char buf[2];
  for (;;) {
    if(ultima_enviada[jogador].valor != '-'){
      printf("(%d) regindo: %d %c\n", jogador, ultima_enviada[jogador].valor, ultima_enviada[jogador].valor);

      buf[0] = ultima_enviada[jogador].valor;
      buf[1] = ultima_enviada[jogador].naipe;

      int enviado = send(conexao[jogador], buf, 2, 0);
      printf("(%d) enviado: %d %c\n", jogador, buf[0], buf[1]);
      if(enviado != 2){
        printf("ERRO\n");
        exit(1);
      }

      ultima_enviada[jogador].valor = '-';
      ultima_enviada[jogador].naipe = '-';
    }
  }

  close(conexao[jogador]);
  return NULL;
}

void * thread_recebida(void * arg){
  int jogador = *((int *) arg);
  char buf[2];
  for (;;){
    int recebido = recv(conexao[jogador], buf, 2, 0);
    printf("(%d) recebido: %d %c\n", jogador, buf[0], buf[1]);
    if(recebido < 0){
      printf("ERRO\n");
      exit(1);
    }

    atual[jogador].valor = buf[0];
    atual[jogador].naipe = buf[1];
  }
  close(conexao[jogador]);
  return NULL;
}


int main(void) {
  int jogadores[4] = {0, 1, 2, 3};

  int escuta = socket(AF_INET, SOCK_STREAM, 0);
  if(escuta < 0) return 1;


  struct sockaddr_in endereco;
  socklen_t tamanho_endereco = sizeof(endereco);

  endereco.sin_addr.s_addr = inet_addr("127.0.0.1");
  endereco.sin_family = AF_INET;
  endereco.sin_port = htons(8080);




  if (bind(escuta, (struct sockaddr *) &endereco, (socklen_t)tamanho_endereco) < 0) return 1;
  printf("Escutando na porta: %d\n", htons(endereco.sin_port));

  if(listen(escuta, 100) < 0) return 1;
  for (int i = 0; i < 4; i++) {
    conexao[i] = accept(escuta, NULL, NULL);
    pthread_t thread_envia, thread_recebe;

    ultima_enviada[i].naipe = atual[i].naipe = '-';
    ultima_enviada[i].valor = atual[i].valor = '-';

    if(pthread_create(&thread_envia, NULL, thread_enviada, (void*) &(jogadores[i])) != 0) return 1;
    if(pthread_create(&thread_recebe, NULL, thread_recebida, (void*) &(jogadores[i])) != 0) return 1;
  }
  

  int turno_atual = 0;
  for(;;){

    if(atual[turno_atual].valor != '-'){
      printf("mudou: %d %c\n", atual[turno_atual].valor, atual[turno_atual].naipe);

      for(int i = 0; i < 4; i++){
        ultima_enviada[i].valor = atual[turno_atual].valor;
        ultima_enviada[i].naipe = atual[turno_atual].naipe;
        printf("(%d) setei: %d %c\n", i, ultima_enviada[i].valor, ultima_enviada[i].naipe);
      }

      atual[turno_atual].naipe = atual[turno_atual].valor = '-';
      printf("resetei: %d %c\n", atual[turno_atual].valor, atual[turno_atual].naipe);

      for(int i = 0; i < 4; i++){
        while(ultima_enviada[i].valor != '-');
      }

      turno_atual = (turno_atual + 1) % 4;
    }
  }

  return 0;
}
