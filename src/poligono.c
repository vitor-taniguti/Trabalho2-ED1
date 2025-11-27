#include "poligono.h"
#include "geometria.h"
#include <float.h>

#define inicio 1
#define fim 2

typedef struct{
    lista vertices;
    double minX, minY, maxX, maxY;
} Poligono;

poligono criarPoligono(){
    Poligono* p = (Poligono*) malloc(sizeof(Poligono));
    p->vertices = criarLista();
    p->minX = DBL_MAX;
    p->maxX = -DBL_MAX;
    p->minY = DBL_MAX;
    p->maxY = -DBL_MAX;
    return (poligono) p;
}

void adicionarVerticePoligono(poligono p, double x, double y) {
    Poligono* pol = (Poligono*)p;
    vertice v = criarVertice(); 
    setXVertice(v, x);
    setYVertice(v, y);
    inserirLista(pol->vertices, v, 6);
    if (x < pol->minX) pol->minX = x;
    if (x > pol->maxX) pol->maxX = x;
    if (y < pol->minY) pol->minY = y;
    if (y > pol->maxY) pol->maxY = y;
}

anteparo* adicionarBordasTemporarias(lista anteparos, double bx, double by, double delta) {
    double minX = bx, maxX = bx, minY = by, maxY = by;
    iterador atual = getPrimeiroLista(anteparos);
    while (atual != NULL){
        anteparo a = getFormaLista(atual);
        double x1 = getX1Anteparo(a); double y1 = getY1Anteparo(a);
        double x2 = getX2Anteparo(a); double y2 = getY2Anteparo(a);
        if (x1 < minX) minX = x1; 
        if (x2 < minX) minX = x2;
        if (x1 > maxX) maxX = x1; 
        if (x2 > maxX) maxX = x2;
        if (y1 < minY) minY = y1; 
        if (y2 < minY) minY = y2;
        if (y1 > maxY) maxY = y1; 
        if (y2 > maxY) maxY = y2;
        atual = getProximoLista(atual);
    }
    minX -= delta; 
    minY -= delta;
    maxX += delta; 
    maxY += delta;
    anteparo* bordas = malloc(4 * sizeof(anteparo));
    bordas[0] = criarAnteparo(-1, minX, minY, maxX, minY, "#000000");
    bordas[1] = criarAnteparo(-2, maxX, minY, maxX, maxY, "#000000");
    bordas[2] = criarAnteparo(-3, maxX, maxY, minX, maxY, "#000000");
    bordas[3] = criarAnteparo(-4, minX, maxY, minX, minY, "#000000");
    for(int i=0; i<4; i++) inserirLista(anteparos, bordas[i], 5);
    return bordas;
}

poligono calcularPoligono(poligono p, lista listaAnteparos, lista atingidos, double bx, double by, char tipoSort, int limite){
    Poligono* pol = (Poligono*)p;
    anteparo* bordasTemporarias = adicionarBordasTemporarias(listaAnteparos, bx, by, 10.0);
    lista verticesOrdenados = criarListaOrdenadaVertices(listaAnteparos, bx, by, tipoSort, limite);
    arvore segAtivos = criarArvore();
    anteparo biombo = NULL; 
    iterador atual = getPrimeiroLista(verticesOrdenados);
    while (atual != NULL){
        vertice v = getFormaLista(atual);
        anteparo an = getAnteparoVertice(v);
        double angulo = getAnguloVertice(v);
        if (getTipoVertice(v) == inicio){ 
            inserirArvore(segAtivos, an, getDistanciaVertice(v));
        } else{
            removerArvore(segAtivos, an);
        }
        anteparo s = getAnteparoArvore(getMenorArvore(segAtivos));      
        if (biombo != s){
            if (biombo != NULL){
                vertice v1 = calcularInterseccao(bx, by, angulo, biombo);
                adicionarVerticePoligono(p, getXVertice(v1), getYVertice(v1));
                liberarVertice(v1);
                if (atingidos != NULL && buscarLista(atingidos, biombo) == NULL) inserirLista(atingidos, biombo, 5);
            }
            if (s != NULL){
                vertice v2 = calcularInterseccao(bx, by, angulo, s);
                adicionarVerticePoligono(p, getXVertice(v2), getYVertice(v2));
                liberarVertice(v2);
                if (atingidos != NULL && buscarLista(atingidos, s) == NULL) inserirLista(atingidos, s, 5);
            }
            biombo = s; 
        } else{
            if (s != NULL){
                vertice vAtual = calcularInterseccao(bx, by, angulo, s);
                adicionarVerticePoligono(p, getXVertice(vAtual), getYVertice(vAtual));
                liberarVertice(vAtual);
                if (atingidos != NULL && buscarLista(atingidos, s) == NULL) inserirLista(atingidos, s, 5);
            }
        }
        atual = getProximoLista(atual);
    }
    for(int i=0; i<4; i++){
        iterador atual = buscarLista(listaAnteparos, bordasTemporarias[i]);
        if (atual != NULL) removerLista(listaAnteparos, atual); 
    }
    free(bordasTemporarias);
    liberarArvore(segAtivos);
    liberarLista(verticesOrdenados);
    return pol;
}

void getBoundingBoxPoligono(poligono p, double* minX, double* minY, double* maxX, double* maxY){
    Poligono* pol = (Poligono*)p;
    *minX = pol->minX;
    *minY = pol->minY;
    *maxX = pol->maxX;
    *maxY = pol->maxY;
}

int getTotalVerticesPoligono(poligono p){
    Poligono* pol = (Poligono*)p;
    return getTamanhoLista(pol->vertices);
}

void getVerticePoligono(poligono p, int n, double* x, double* y){
    Poligono* pol = (Poligono*)p;
    iterador atual = getPrimeiroLista(pol->vertices);
    for (int i = 0; i < n; i++){
        atual = getProximoLista(atual);
    }
    vertice v = getFormaLista(atual);
    *x = getXVertice(v);
    *y = getYVertice(v);
}

void liberarPoligono(poligono p){
    Poligono* pol = (Poligono*)p;
    if (pol->vertices != NULL) liberarLista(pol->vertices);
    free(pol);
}