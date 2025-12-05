#include "arvore.h"
#include "vertice.h"
#include "geometria.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct elemento{
    anteparo an;
    struct elemento* e;
    struct elemento* d;
} Elemento;

typedef Elemento* raiz;

typedef struct{
    raiz r;
} Arvore;

arvore criarArvore(){
    Arvore* ar = (Arvore*) malloc(sizeof(Arvore));
    ar->r = NULL;
    return ar;
}

double calcularDistanciaFutura(double bx, double by, double angulo, anteparo an){
    double anguloFuturo = angulo + 0.0001; 
    vertice v = calcularInterseccao(bx, by, anguloFuturo, an);
    if (v != NULL){
        double dist = getDistanciaVertice(v);
        liberarVertice(v);
        return dist;
    }
    return 999999999.0;
}

Elemento* inserirRecursivo(Elemento* no, anteparo an, double bx, double by, double angulo, double distNovoFixa){
    if (no == NULL){
        Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
        novo->an = an;
        novo->e = NULL;
        novo->d = NULL;
        return novo;
    }
    double distNovo = distNovoFixa;
    vertice vNo = calcularInterseccao(bx, by, angulo, no->an);
    double distNo = (vNo != NULL) ? getDistanciaVertice(vNo) : 999999999.0;
    if (vNo != NULL) liberarVertice(vNo);
    if (fabs(distNovo - distNo) < 0.00001) {
        double distNovoFutura = calcularDistanciaFutura(bx, by, angulo, an);
        double distNoFutura = calcularDistanciaFutura(bx, by, angulo, no->an);
        if (distNovoFutura < distNoFutura){
            no->e = inserirRecursivo(no->e, an, bx, by, angulo, distNovoFixa);
        } else {
            no->d = inserirRecursivo(no->d, an, bx, by, angulo, distNovoFixa);
        }
    } 
    else if (distNovo < distNo){
        no->e = inserirRecursivo(no->e, an, bx, by, angulo, distNovoFixa);
    } 
    else {
        no->d = inserirRecursivo(no->d, an, bx, by, angulo, distNovoFixa);
    }
    return no;
}

void inserirArvore(arvore ar, anteparo an, double bx, double by, double angulo, double distanciaDoEvento){
    Arvore* arv = (Arvore*)ar;
    arv->r = inserirRecursivo(arv->r, an, bx, by, angulo, distanciaDoEvento);
}

iterador getMenorRecursivo(iterador i){
    Elemento* no = (Elemento*)i;
    if (no->e == NULL) return no;
    return getMenorRecursivo(no->e);
}

iterador getMenorArvore(arvore ar){
    Arvore* a = (Arvore*)ar;
    if (a->r == NULL) return NULL;
    return getMenorRecursivo(a->r);
}

iterador getMaiorRecursivo(iterador i){
    Elemento* no = (Elemento*)i;
    if (no->d == NULL) return no;
    return getMaiorRecursivo(no->d);
}

iterador getMaiorArvore(arvore ar){
    Arvore* a = (Arvore*)ar;
    if (a->r == NULL) return NULL;
    return getMaiorRecursivo(a->r);
}

Elemento* removerRecursivo(Elemento* raiz, anteparo an){
    if (raiz == NULL) return raiz;
    if (raiz->an == an){
        if (raiz->e == NULL) {
            Elemento* temp = raiz->d;
            free(raiz);
            return temp;
        } else if (raiz->d == NULL){
            Elemento* temp = raiz->e;
            free(raiz);
            return temp;
        }
        Elemento* temp = getMenorRecursivo(raiz->d);
        raiz->an= temp->an;
        raiz->d = removerRecursivo(raiz->d, temp->an);
    } else{
        Elemento* novaEsq = removerRecursivo(raiz->e, an);        
        if (novaEsq != raiz->e){ 
            raiz->e = novaEsq;
        } else{
            raiz->d = removerRecursivo(raiz->d, an);
        }
    }
    return raiz;
}

void removerArvore(arvore ar, anteparo an){
    Arvore* arv = (Arvore*)ar;
    if (arv->r != NULL){
        arv->r = removerRecursivo(arv->r, an);
    }
}

anteparo getAnteparoArvore(iterador i){
    if (i == NULL) return NULL;
    return ((Elemento*)i)->an;
}

void liberarRecursivo(iterador i){
    Elemento* no = (Elemento*)i;
    if (no->e != NULL) liberarRecursivo(no->e);
    if (no->d != NULL) liberarRecursivo(no->d);
    free(no);
}

void liberarArvore(arvore ar){
    Arvore* a = (Arvore*)ar;
    if (a == NULL) return; 
    if (a->r != NULL) liberarRecursivo(a->r);
    free(a); 
}