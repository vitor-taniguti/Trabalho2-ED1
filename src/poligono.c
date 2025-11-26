#include "poligono.h"
#include <math.h>
#include <float.h>

#define inicio 1
#define fim 2
#define pi 3.1415

typedef struct vertice{
    double x, y;
    double angulo;
    double distancia;
    int tipo;
    anteparo an;
} Vertice;

typedef struct ponto{
    double x, y;
} Ponto;

typedef struct poligono{
    Ponto* pontos;
    int totalPontos;
    int capacidade;
    double minX, minY, maxX, maxY;
} Poligono;

double calcularDistancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(y2-y1, 2)+pow(x2-x1, 2));
}

double normalizarAngulo(double angulo){
    if (angulo < 0) return angulo + 2 * pi;
    return angulo;
}

Vertice* criarArrayVertices(lista listaAnteparos, double x, double y){
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
        ang1 = normalizarAngulo(ang1);
        ang2 = normalizarAngulo(ang2);

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
    return vertices;
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

void adicionarPontoPoligono(poligono p, double x, double y){
    Poligono* pol = (Poligono*) p;
    if (pol->totalPontos >= pol->capacidade){
        pol->capacidade *= 2;
        pol->pontos = realloc(pol->pontos, pol->capacidade * sizeof(Ponto));
    }
    pol->pontos[pol->totalPontos].x = x;
    pol->pontos[pol->totalPontos].y = y;
    pol->totalPontos++;
    if (x < pol->minX) pol->minX = x;
    if (x > pol->maxX) pol->maxX = x;
    if (y < pol->minY) pol->minY = y;
    if (y > pol->maxY) pol->maxY = y;
}

Ponto calcularInterseccao(double bx, double by, double angulo, anteparo a){
    double x3 = getX1Anteparo(a);
    double y3 = getY1Anteparo(a);
    double x4 = getX2Anteparo(a);
    double y4 = getY2Anteparo(a);
    double dx_raio = cos(angulo);
    double dy_raio = sin(angulo);
    double dx_seg = x4 - x3;
    double dy_seg = y4 - y3;
    double det = dx_raio * dy_seg - dy_raio * dx_seg;
    if (fabs(det) < 1e-10) { 
        Ponto p = {x3, y3}; 
        return p; 
    }
    double t = ((x3 - bx) * dy_seg - (y3 - by) * dx_seg) / det;
    Ponto p;
    p.x = bx + (dx_raio * t);
    p.y = by + (dy_raio * t);
    return p;
}

poligono criarPoligonoVazio(){
    Poligono* p = (Poligono*) malloc(sizeof(Poligono));
    p->totalPontos = 0;
    p->capacidade = 10;
    p->pontos = (Ponto*) malloc(p->capacidade*sizeof(Ponto));
    p->minX = DBL_MAX;
    p->maxX = -DBL_MAX;
    p->minY = DBL_MAX;
    p->maxY = -DBL_MAX;
    return (poligono) p;
}

poligono criarPoligono(lista listaAnteparos, lista atingidos, double bx, double by){
    int qtdAnteparos = getTamanhoLista(listaAnteparos);
    Vertice* vertices = criarArrayVertices(listaAnteparos, bx, by);
    qsort(vertices, 2*qtdAnteparos, sizeof(Vertice), compararVertices);
    poligono p = criarPoligonoVazio();
    arvore ar = criarArvore();
    anteparo anteriorMaisProximo = NULL;
    for (int i = 0; i < 2*qtdAnteparos; i++){
        Vertice v = vertices[i];
        anteriorMaisProximo = getAnteparoArvore(getMenorArvore(ar));
        if (v.tipo == inicio){
            inserirArvore(ar, v.an, v.distancia);
        } else{
            removerArvore(ar, v.an);
        }
        anteparo atualMaisProximo = getAnteparoArvore(getMenorArvore(ar));
        if (anteriorMaisProximo != atualMaisProximo){
            if (anteriorMaisProximo != NULL){
                Ponto p1 = calcularInterseccao(bx, by, v.angulo, anteriorMaisProximo);
                adicionarPontoPoligono(p, p1.x, p1.y);
                if (buscarLista(atingidos, anteriorMaisProximo) == NULL) inserirLista(atingidos, anteriorMaisProximo, 5);
            }
            if (atualMaisProximo != NULL){
                Ponto p2 = calcularInterseccao(bx, by, v.angulo, atualMaisProximo);
                adicionarPontoPoligono(p, p2.x, p2.y);
                if (buscarLista(atingidos, anteriorMaisProximo) == NULL) inserirLista(atingidos, anteriorMaisProximo, 5);
            }
        } else{
            if (atualMaisProximo != NULL){
                Ponto pAtual = calcularInterseccao(bx, by, v.angulo, atualMaisProximo);
                adicionarPontoPoligono(p, pAtual.x, pAtual.y);
                if (buscarLista(atingidos, atualMaisProximo) == NULL) inserirLista(atingidos, atualMaisProximo, 5);
            }
        }
    }
    free(vertices);
    return p;
}

void getBoundingBoxPoligono(poligono p, double* minX, double* minY, double* maxX, double* maxY){
    Poligono* pol = (Poligono*)p;
    (*minX) = pol->minX; 
    (*minY) = pol->minY; 
    (*maxX) = pol->maxX; 
    (*maxY) = pol->maxY; 
}

double getTotalPontosPoligono(poligono p){
    return ((Poligono*)p)->totalPontos;
}

void getPontoPoligono(poligono p, int n, double* x, double* y){
    Poligono* pol = (Poligono*)p;
    if (n >= 0 && n < pol->totalPontos){
        (*x) = pol->pontos[n].x;
        (*y) = pol->pontos[n].y;
    }
}

void liberarPoligono(poligono p){
    Poligono* pol = (Poligono*)p;
    if (pol->pontos != NULL) free(pol->pontos);
    free(pol);
}