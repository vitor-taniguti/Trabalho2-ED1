#include "vertice.h"
#include "geometria.h"

#define inicio 1
#define fim 2

typedef struct{
    double x, y;
    double angulo;
    double distancia;
    int tipo;
    anteparo an;
} Vertice;

vertice criarVertice(){
    Vertice* v = (Vertice*) malloc(sizeof(Vertice));
    v->x = 0.0;
    v->y = 0.0;
    v->angulo = 0.0;
    v->distancia = 0.0;
    v->tipo = 0;
    v->an = NULL;
    return v;
}

double getXVertice(vertice v){
    return ((Vertice*)v)->x;
}

double getYVertice(vertice v){
    return ((Vertice*)v)->y;
}

double getAnguloVertice(vertice v){
    return ((Vertice*)v)->angulo;
}

double getDistanciaVertice(vertice v){
    return ((Vertice*)v)->distancia;
}

int getTipoVertice(vertice v){
    return ((Vertice*)v)->tipo;
}

anteparo getAnteparoVertice(vertice v){
    return ((Vertice*)v)->an;
}

void setXVertice(vertice v, double x){
    Vertice* ver = (Vertice*)v;
    ver->x = x;
}

void setYVertice(vertice v, double y){
    Vertice* ver = (Vertice*)v;
    ver->y = y;
}

int compararVertices(const void* a, const void* b){
    Vertice* v1 = (Vertice*) a;
    Vertice* v2 = (Vertice*) b;
    if (v1->angulo < v2->angulo) return -1;
    if (v1->angulo > v2->angulo) return 1;
    if (v1->angulo == v2->angulo){
        if (v1->tipo < v2->tipo) return -1;
        if (v1->tipo > v2->tipo) return 1;
    }
    return 0;
}

lista criarListaOrdenadaVertices(lista listaAnteparos, double x, double y, int tipoSort, int limite){
    int tamanhoLista = getTamanhoLista(listaAnteparos);
    Vertice* vertices = (Vertice*) malloc(2*tamanhoLista*sizeof(Vertice));
    iterador atual = getPrimeiroLista(listaAnteparos);
    int i = 0;
    while (atual != NULL){
        anteparo a = getFormaLista(atual);
        double x1 = getX1Anteparo(a);
        double y1 = getY1Anteparo(a);
        double x2 = getX2Anteparo(a);
        double y2 = getY2Anteparo(a);
        double ang1 = atan2(y1-y, x1-x);
        double ang2 = atan2(y2-y, x2-x);
        vertices[i].x = x1;
        vertices[i].y = y1;
        vertices[i].angulo = ang1;
        vertices[i].distancia = calcularDistancia(x, y, x1, y1);
        vertices[i].tipo = (ang1 < ang2) ? inicio : fim;
        vertices[i].an = a;
        vertices[i+1].x = getX2Anteparo(a);
        vertices[i+1].y = getY2Anteparo(a);
        vertices[i+1].angulo = ang2;
        vertices[i+1].distancia = calcularDistancia(x, y, x2, y2);
        vertices[i+1].tipo = (ang2 < ang1) ? inicio : fim;
        vertices[i+1].an = a;
        i += 2;
        atual = getProximoLista(atual);
    }
    if (tipoSort == 'q'){
        qsort(vertices, 2*tamanhoLista, sizeof(Vertice), compararVertices);
    } else{
        msort(vertices, 2*tamanhoLista, sizeof(Vertice), compararVertices, limite);
    }
    lista listaVertices = criarLista();
    for (int i = 0; i < 2*tamanhoLista; i++){
        Vertice* v = criarVertice();
        *v = vertices[i];
        inserirLista(listaVertices, v, 6);
    }
    free(vertices);
    return listaVertices;
}

void liberarVertice(vertice v){
    Vertice* ver = (Vertice*)v;
    if (ver != NULL) free(ver);
}