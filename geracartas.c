#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
    int valor;
    int naipe;
}carta;

carta baralho[12]; //cartas da rodada

int main() {
    srand (time(NULL));

    baralho[0].valor = rand() % 10;
    baralho[0].naipe = rand() % 4;
    printf("%c\n", baralho[0].valor);
    baralho[1].valor = rand() % 10;
    baralho[1].naipe = rand() % 4;
    while(baralho[0].valor == baralho[1].valor && baralho[0].naipe == baralho[1].naipe){
        baralho[1].valor = rand() % 10;
        baralho[1].naipe = rand() % 4;
    }
    printf("%c\n", baralho[1].valor);
    baralho[2].valor = rand() % 10;
    baralho[2].naipe = rand() % 4;
    while((baralho[0].valor == baralho[2].valor || baralho[2].valor == baralho[1].valor)
    && (baralho[0].naipe == baralho[2].naipe || baralho[2].naipe == baralho[1].naipe)){
        baralho[1].valor = rand() % 10;
        baralho[1].naipe = rand() % 4;
    }
    printf("%c\n", baralho[2].valor);
    baralho[3].valor = rand() % 10;
    baralho[3].naipe = rand() % 4;
    while((baralho[3].valor == baralho[0].valor || baralho[3].valor == baralho[1].valor || baralho[3].valor == baralho[2].valor)
    && (baralho[3].naipe == baralho[0].naipe || baralho[3].naipe == baralho[1].naipe || baralho[3].naipe == baralho[2].naipe)){
        baralho[3].valor = rand() % 10;
        baralho[3].naipe = rand() % 4;
    }
    baralho[4].valor = rand() % 10;
    baralho[4].naipe = rand() % 4;
    while((baralho[4].valor == baralho[0].valor || (baralho[4].valor == baralho[1].valor) || (baralho[4].valor == baralho[2].valor)
            || baralho[4].valor == baralho[3].valor)
    && (baralho[4].naipe == baralho[0].naipe || (baralho[4].naipe == baralho[1].naipe) || (baralho[4].naipe == baralho[2].naipe
            || baralho[4].naipe == baralho[3].naipe))){
        baralho[4].valor = rand() % 10;
        baralho[4].naipe = rand() % 4;
    }
    baralho[5].valor = rand() % 10;
    baralho[5].naipe = rand() % 4;
    while((baralho[5].valor == baralho[0].valor || baralho[5].valor == baralho[1].valor || baralho[5].valor == baralho[2].valor
            || baralho[5].valor == baralho[3].valor || baralho[5].valor == baralho[4].valor)
    && (baralho[5].naipe == baralho[0].naipe || baralho[5].naipe == baralho[1].naipe || baralho[5].naipe == baralho[2].naipe
            || baralho[5].naipe == baralho[3].naipe || baralho[5].naipe == baralho[4].naipe)){
        baralho[5].valor = rand() % 10;
        baralho[5].naipe = rand() % 4;
    }
    baralho[6].valor = rand() % 10;
    baralho[6].naipe = rand() % 4;
    while((baralho[6].valor == baralho[0].valor || baralho[6].valor == baralho[1].valor || baralho[6].valor == baralho[2].valor
        || baralho[6].valor == baralho[3].valor || baralho[6].valor == baralho[4].valor || baralho[6].valor == baralho[5].valor )
    && (baralho[6].naipe == baralho[0].naipe || baralho[6].naipe == baralho[1].naipe || baralho[6].naipe == baralho[2].naipe
     || baralho[6].naipe == baralho[3].naipe || baralho[6].naipe == baralho[4].naipe || baralho[6].naipe == baralho[5].naipe)){
        baralho[6].valor = rand() % 10;
        baralho[6].naipe = rand() % 4;
    }
    printf("%c\n", baralho[6].valor);
    baralho[7].valor = rand() % 10;
    baralho[7].naipe = rand() % 4;
    while((baralho[7].valor == baralho[0].valor || baralho[7].valor == baralho[1].valor || baralho[7].valor == baralho[2].valor
        || baralho[7].valor == baralho[3].valor || baralho[7].valor == baralho[4].valor || baralho[7].valor == baralho[5].valor
        || baralho[7].valor == baralho[6].valor )
    && (baralho[7].naipe == baralho[0].naipe || baralho[7].naipe == baralho[1].naipe || baralho[7].naipe == baralho[2].naipe
     || baralho[7].naipe == baralho[3].naipe || baralho[7].naipe == baralho[4].naipe || baralho[7].naipe == baralho[5].naipe
     || baralho[7].naipe == baralho[6].naipe)){
        baralho[7].valor = rand() % 10;
        baralho[7].naipe = rand() % 4;
    }
    baralho[8].valor = rand() % 10;
    baralho[8].naipe = rand() % 4;
    while((baralho[8].valor == baralho[0].valor || baralho[8].valor == baralho[1].valor || baralho[8].valor == baralho[2].valor
        || baralho[8].valor == baralho[3].valor || baralho[8].valor == baralho[4].valor || baralho[8].valor == baralho[5].valor
        || baralho[8].valor == baralho[6].valor || baralho[8].valor == baralho[7].valor )
    && (baralho[8].naipe == baralho[0].naipe || baralho[8].naipe == baralho[1].naipe || baralho[8].naipe == baralho[2].naipe
     || baralho[8].naipe == baralho[3].naipe || baralho[8].naipe == baralho[4].naipe || baralho[8].naipe == baralho[5].naipe
     || baralho[8].naipe == baralho[6].naipe || baralho[8].naipe == baralho[7].naipe)){
        baralho[8].valor = rand() % 10;
        baralho[8].naipe = rand() % 4;
    }
    baralho[9].valor = rand() % 10;
    baralho[9].naipe = rand() % 4;
    while((baralho[9].valor == baralho[0].valor || baralho[9].valor == baralho[1].valor || baralho[9].valor == baralho[2].valor
        || baralho[9].valor == baralho[3].valor || baralho[9].valor == baralho[4].valor || baralho[9].valor == baralho[5].valor
        || baralho[9].valor == baralho[6].valor || baralho[9].valor == baralho[7].valor || baralho[9].valor == baralho[8].valor)
    && (baralho[9].naipe == baralho[0].naipe || baralho[9].naipe == baralho[1].naipe || baralho[9].naipe == baralho[2].naipe
     || baralho[9].naipe == baralho[3].naipe || baralho[9].naipe == baralho[4].naipe || baralho[9].naipe == baralho[5].naipe
     || baralho[9].naipe == baralho[6].naipe || baralho[9].naipe == baralho[7].naipe || baralho[9].naipe == baralho[8].naipe)){
        baralho[9].valor = rand() % 10;
        baralho[9].naipe = rand() % 4;
    }
    baralho[10].valor = rand() % 10;
    baralho[10].naipe = rand() % 4;
    while((baralho[10].valor == baralho[0].valor || baralho[10].valor == baralho[1].valor || baralho[10].valor == baralho[2].valor
        || baralho[10].valor == baralho[3].valor || baralho[10].valor == baralho[4].valor || baralho[10].valor == baralho[5].valor
        || baralho[10].valor == baralho[6].valor || baralho[10].valor == baralho[7].valor || baralho[10].valor == baralho[8].valor
        || baralho[10].valor == baralho[9].valor)
    && (baralho[10].naipe == baralho[0].naipe || baralho[10].naipe == baralho[1].naipe || baralho[10].naipe == baralho[2].naipe
     || baralho[10].naipe == baralho[3].naipe || baralho[10].naipe == baralho[4].naipe || baralho[10].naipe == baralho[5].naipe
     || baralho[10].naipe == baralho[6].naipe || baralho[10].naipe == baralho[7].naipe || baralho[10].naipe == baralho[8].naipe
     || baralho[10].naipe == baralho[9].naipe)){
        baralho[10].valor = rand() % 10;
        baralho[10].naipe = rand() % 4;
    }
    baralho[11].valor = rand() % 10;
    baralho[11].naipe = rand() % 4;
    while((baralho[11].valor == baralho[0].valor || baralho[11].valor == baralho[1].valor || baralho[11].valor == baralho[2].valor
        || baralho[11].valor == baralho[3].valor || baralho[11].valor == baralho[4].valor || baralho[11].valor == baralho[5].valor
        || baralho[11].valor == baralho[6].valor || baralho[11].valor == baralho[7].valor || baralho[11].valor == baralho[8].valor
        || baralho[11].valor == baralho[9].valor || baralho[11].valor == baralho[10].valor)
    && (baralho[11].naipe == baralho[0].naipe || baralho[11].naipe == baralho[1].naipe || baralho[11].naipe == baralho[2].naipe
     || baralho[11].naipe == baralho[3].naipe || baralho[11].naipe == baralho[4].naipe || baralho[11].naipe == baralho[5].naipe
     || baralho[11].naipe == baralho[6].naipe || baralho[11].naipe == baralho[7].naipe || baralho[11].naipe == baralho[8].naipe
     || baralho[11].naipe == baralho[9].naipe || baralho[11].naipe == baralho[10].naipe)){
        baralho[11].valor = rand() % 10;
        baralho[11].naipe = rand() % 4;
    }

    for(int i = 0; i < 12; i++) printf("%c %c\n", baralho[i].valor, baralho[i].naipe);

    return 0;
}
