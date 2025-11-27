#include "anteparos.h"
#include <string.h>
#include <stdlib.h>

typedef struct{
    int id;
    double x1, y1, x2, y2;
    char* cor;
} Anteparo;

anteparo criarAnteparo(int id, double x1, double y1, double x2, double y2, char* cor){
    Anteparo* ant = malloc(sizeof(Anteparo));
    ant->id = id;
    ant->x1 = x1;
    ant->y1 = y1;
    ant->x2 = x2;
    ant->y2 = y2;
    ant->cor = malloc(strlen(cor)+1);
    strcpy(ant->cor, cor);
    return ant;
}

anteparo* transformarRetangulo(forma f){
    anteparo* arrayAnteparos = malloc(4*sizeof(void*));
    int id = getIdRetangulo(f);
    double x = getXRetangulo(f);
    double y = getYRetangulo(f);
    double w = getWRetangulo(f);
    double h = getHRetangulo(f);
    char* cor = getCorBRetangulo(f);
    arrayAnteparos[0] = (Anteparo*) criarAnteparo(id, x, y, x+w, y, cor);
    arrayAnteparos[1] = (Anteparo*) criarAnteparo(id, x+w, y, x+w, y+h, cor);
    arrayAnteparos[2] = (Anteparo*) criarAnteparo(id, x, y+h, x+w, y+h, cor);
    arrayAnteparos[3] = (Anteparo*) criarAnteparo(id, x, y, x, y+h, cor);
    return arrayAnteparos;
}

anteparo transformarCirculo(forma f, char orientacao){
    Anteparo* ant;
    int id = getIdCirculo(f);
    double x = getXCirculo(f);
    double y = getYCirculo(f);
    double r = getRCirculo(f);
    char* cor = getCorBCirculo(f);
    switch (orientacao){
        case 'h':
            ant = criarAnteparo(id, x-r, y, x+r, y, cor);
            break;
        case 'v':
            ant = criarAnteparo(id, x, y-r, x, y+r, cor);
            break;
    }
    return ant;
}

anteparo transformarLinha(forma f){
    int id = getIdLinha(f);
    double x1 = getX1Linha(f);
    double y1 = getY1Linha(f);
    double x2 = getX2Linha(f);
    double y2 = getY2Linha(f);
    char* cor = getCorLinha(f);
    Anteparo* ant = criarAnteparo(id, x1, y1, x2, y2, cor);
    return ant;
}

anteparo transformarTexto(forma f){
    int id = getIdTexto(f);
    double x1 = getX1Texto(f);
    double y1 = getYtTexto(f);
    double x2 = getX2Texto(f);
    double y2 = getYtTexto(f);
    char* cor = getCorBTexto(f);
    Anteparo* ant = criarAnteparo(id, x1, y1, x2, y2, cor);
    return ant;
}

int getIdAnteparo(anteparo a){
    return ((Anteparo*)a)->id;
}

double getX1Anteparo(anteparo a){
    return ((Anteparo*)a)->x1;
}

double getY1Anteparo(anteparo a){
    return ((Anteparo*)a)->y1;
}

double getX2Anteparo(anteparo a){
    return ((Anteparo*)a)->x2;
}

double getY2Anteparo(anteparo a){
    return ((Anteparo*)a)->y2;
}

void setCorAnteparo(anteparo a, char* cor){
    Anteparo* an = (Anteparo*)a;
    strcpy(an->cor, cor);
}

void liberarAnteparo(anteparo a){
    Anteparo* ant = a;
    free(ant->cor);
    free(ant);
}