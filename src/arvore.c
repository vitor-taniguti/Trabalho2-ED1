#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    anteparo an;
    double distancia;
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

Elemento* inserirRecursivo(Elemento* no, anteparo an, double distancia){
    if (no == NULL){
        Elemento* novo = malloc(sizeof(Elemento));
        novo->an = an;
        novo->distancia = distancia;
        novo->e = NULL;
        novo->d = NULL;
        return novo;
    }
    if (distancia < no->distancia){
        no->e = inserirRecursivo(no->e, an, distancia);
    } else{
        no->d = inserirRecursivo(no->d, an, distancia);
    }
    return no;
}

void inserirArvore(arvore ar, anteparo an, double distancia){
    Arvore* arv = (Arvore*)ar;
    arv->r = inserirRecursivo(arv->r, an, distancia);
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
        raiz->distancia = temp->distancia; 
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

double getDistanciaArvore(iterador i){
    return ((Elemento*)i)->distancia;
}

void liberarRecursivo(iterador i){
    Elemento* no = (Elemento*)i;
    if (no->e != NULL) liberarRecursivo(no->e);
    if (no->d != NULL) liberarRecursivo(no->d);
    liberarAnteparo(no->an);
    free(no);
}

void liberarArvore(arvore ar){
    Arvore* a = (Arvore*)ar;
    if (a->r == NULL) return;
    liberarRecursivo(a->r);
    free(a);
}