#include "poligono.h"
#include "geometria.h"
#include "svg.h"
#include <float.h>

#define inicio 1
#define fim 2
#define pi 3.14159265358979323846 
#define epsilon 1e-9

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

anteparo* adicionarBordasTemporarias(lista anteparos, double bx, double by, double delta){
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
    bordas[0] = criarAnteparo(-1, maxX, maxY, minX, maxY, "#000000");
    bordas[1] = criarAnteparo(-2, minX, maxY, minX, minY, "#000000");
    bordas[2] = criarAnteparo(-3, minX, minY, maxX, minY, "#000000");
    bordas[3] = criarAnteparo(-4, maxX, minY, maxX, maxY, "#000000");

    for(int i=0; i < 4; i++) inserirLista(anteparos, bordas[i], 5);
    return bordas;
}

void tratarAnteparosIniciais(lista anteparos, double bx, double by){
    lista novosAnteparos = criarLista(); 
    iterador atual = getPrimeiroLista(anteparos);
    while (atual != NULL){
        iterador proximo = getProximoLista(atual);
        anteparo a = getFormaLista(atual);
        vertice v = calcularInterseccao(bx, by, 0.0, a);
        if (v != NULL){
            int id = getIdAnteparo(a);
            double x = getXVertice(v);
            double y = getYVertice(v);
            inserirLista(novosAnteparos, criarAnteparo(id*1000+1, getX1Anteparo(a), getY1Anteparo(a), x, y, "black"), 5);
            inserirLista(novosAnteparos, criarAnteparo(id*1000+2, x, y, getX2Anteparo(a), getY2Anteparo(a), "black"), 5);
            removerLista(anteparos, atual);
            liberarVertice(v);
        }
        atual = proximo;
    }
    iterador itNovos = getPrimeiroLista(novosAnteparos);
    while(itNovos != NULL){
        anteparo novoAnt = getFormaLista(itNovos);
        inserirLista(anteparos, novoAnt, 5);
        itNovos = getProximoLista(itNovos);
    }
    liberarApenasNosLista(novosAnteparos); 
}

void calcularPoligono(poligono p, lista listaAnteparos, lista atingidos, double bx, double by, char tipoSort, int limite){
    anteparo* bordasTemporarias = adicionarBordasTemporarias(listaAnteparos, bx, by, 300.0);
    tratarAnteparosIniciais(listaAnteparos, bx, by);
    lista verticesOrdenados = criarListaOrdenadaVertices(listaAnteparos, bx, by, tipoSort, limite);
    arvore segAtivos = criarArvore();
    iterador atual = getPrimeiroLista(verticesOrdenados);
    anteparo biomboAnterior = NULL;
    int i = 1;
    printf("\nMontagem do polígono iniciada:\n\n");
    while (atual != NULL){
        vertice vPrimeiro = getFormaLista(atual);
        double anguloAtual = getAnguloVertice(vPrimeiro);
        int tocouBiomboAtual = 0;
        while (atual != NULL){
            vertice v = getFormaLista(atual);
            if (fabs(getAnguloVertice(v) - anguloAtual) > epsilon) break;
            anteparo an = getAnteparoVertice(v);
            if (biomboAnterior != NULL && an == biomboAnterior) {
                tocouBiomboAtual = 1;
            }
            if (getTipoVertice(v) == inicio){
                inserirArvore(segAtivos, an, bx, by, anguloAtual, getDistanciaVertice(v));
            } else{
                removerArvore(segAtivos, an);
            }
            atual = getProximoLista(atual);
        }
        printf("%d - Ângulo: %lf | ", i++, (anguloAtual/pi)*180);
        if (biomboAnterior != NULL){
            printf("%d. ", getIdAnteparo(biomboAnterior));
        } else{
            printf("Nenhum. ");
        }
        iterador noMenor = getMenorArvore(segAtivos);
        anteparo s = NULL;
        if (noMenor != NULL) s = getAnteparoArvore(noMenor);
        if (biomboAnterior != s){
            if (s != NULL){
                printf("Houve mudança, novo anteparo : %d\n", getIdAnteparo(s));
            } else{
                printf("Houve mudança, novo anteparo: Nenhum\n");
            }
            if (biomboAnterior != NULL){
                vertice v1 = calcularInterseccao(bx, by, anguloAtual, biomboAnterior);
                if (v1 != NULL){
                    adicionarVerticePoligono(p, getXVertice(v1), getYVertice(v1));
                    liberarVertice(v1);
                    if (buscarLista(atingidos, biomboAnterior) == NULL && getIdAnteparo(biomboAnterior) >= 0) inserirLista(atingidos, biomboAnterior, 5);
                }
            }
            if (s != NULL){
                vertice v2 = calcularInterseccao(bx, by, anguloAtual, s);
                if (v2 != NULL){
                    adicionarVerticePoligono(p, getXVertice(v2), getYVertice(v2));
                    liberarVertice(v2);
                    if (buscarLista(atingidos, s) == NULL && getIdAnteparo(s) >= 0) inserirLista(atingidos, s, 5);
                } else{
                    adicionarVerticePoligono(p, getXVertice(vPrimeiro), getYVertice(vPrimeiro));
                    if (buscarLista(atingidos, s) == NULL && getIdAnteparo(s) >= 0) inserirLista(atingidos, s, 5);
                }
            }
            biomboAnterior = s;
        } else{
            if (biomboAnterior != NULL){
                if (tocouBiomboAtual){
                    printf("Quina detectada no anteparo %d.\n", getIdAnteparo(biomboAnterior));
                    adicionarVerticePoligono(p, getXVertice(vPrimeiro), getYVertice(vPrimeiro));
                } else {
                    printf("Evento ignorado (oculto atrás do anteparo %d).\n", getIdAnteparo(biomboAnterior));
                }
            } else {
                printf("Continua no vazio.\n");
            }
        }
    }
    atual = getPrimeiroLista(listaAnteparos);
    while (atual != NULL){
        iterador proximo = getProximoLista(atual);
        anteparo a = getFormaLista(atual);
        if (getIdAnteparo(a) < 0) removerLista(listaAnteparos, atual);
        atual = proximo;
    }
    free(bordasTemporarias);
    liberarArvore(segAtivos);
    liberarLista(verticesOrdenados);
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