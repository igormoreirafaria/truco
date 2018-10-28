#include "server.h"

int round_dupla1 = 0;
int round_dupla2 = 0;
int baralho_tranformado[4];
int vencedor_turno1;
int empate;
int turno = 0; // global
int pontuacao_dupla1 = 0;
int pontuacao_dupla2 = 0;
int flag_vitoria_segundo_turno = 0;


typedef struct{
  int id_jogador;
  int carta_tranformada;
}Jogada;

Jogada rodada[4];

void selection_sort (int *a, int n) {
  int i, j, m, t;
  for (i = 0; i < n; i++) {
    for (j = i, m = i; j < n; j++) {
      if (a[j] < a[m]) {
        m = j;
      }
    }
    t = a[i];
    a[i] = a[m];
    a[m] = t;
  }
}

void tranforma_carta(Carta vetor_cartas[4]){

  for (int i = 0; i < 4; i++) {
    if (vetor_cartas[i].valor == '4' && vetor_cartas[i].naipe == 'p') {
      baralho_tranformado[i]=14;
      rodada[i].id_jogador = i;
      rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '7' && vetor_cartas[i].naipe == 'c') {
        baralho_tranformado[i]=13;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == 'A' && vetor_cartas[i].naipe == 'e') {
        baralho_tranformado[i]=12;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '7' && vetor_cartas[i].naipe == 'o') {
        baralho_tranformado[i]=11;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '3') {
        baralho_tranformado[i]=10;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '2') {
        baralho_tranformado[i]=9;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == 'A') {
        baralho_tranformado[i]=8;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == 'K') {
        baralho_tranformado[i]=7;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == 'J') {
        baralho_tranformado[i]=6;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == 'Q') {
        baralho_tranformado[i]=5;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '7') {
        baralho_tranformado[i]=4;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '6') {
        baralho_tranformado[i]=3;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '5') {
        baralho_tranformado[i]=2;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }else if (vetor_cartas[i].valor == '4') {
        baralho_tranformado[i]=1;
        rodada[i].id_jogador = i;
        rodada[i].carta_tranformada = baralho_tranformado[i];
    }
  }
}

int retorna_vencedor(){
  if (round_dupla1 == 2) {
    return 1;
  }else if (round_dupla2 == 2) {
    return 2;
  }
}

void regras(Carta vetor_cartas[4]){

  int id_jogador;
  tranforma_carta(vetor_cartas);
  selection_sort(baralho_tranformado, 4);
  if (baralho_tranformado[3] == baralho_tranformado[2]) {
    empate = 1;
  }else{
    for (int i = 0; i < 4; i++) {
      if (baralho_tranformado[3] == rodada[i].carta_tranformada) {
        id_jogador = rodada[i].id_jogador;
      }
    }
    for (int i = 0; i < 4; i++) {
      baralho_tranformado[i] == 0;
      rodada[i].id_jogador = 0;
      rodada[i].carta_tranformada = 0;
    }
  }
  if (id_jogador == 0 || id_jogador == 2) {
    round_dupla1++;
    if (turno == 0) {
      vencedor_turno1 = 0;
    }
    turno++;

  }
  if (id_jogador == 1 || id_jogador == 3) {
    round_dupla2++;
    if (turno == 0) {
      vencedor_turno1 = 1;
    }
    turno++;
  }
  if (empate == 1) {
    if (turno == 1 || turno == 2) {
      if (vencedor_turno1 == 0) {
        round_dupla1++;
      }
      if (vencedor_turno1 == 1) {
        round_dupla2++;
      }
    }else{
      round_dupla2=1;
      round_dupla1=1;
    }
  }
}
