#include "arvore.h"
#include <stdio.h>

typedef struct elemento{
    anteparo an;
    struct elemento* e;
    struct elemento* d;
} Elemento;

typedef Elemento* raiz;

typedef struct{
    raiz r;
} Arvore;

arvore criarAvore(){
    Arvore* ar = (Arvore*) malloc(sizeof(Arvore));
    if (ar != NULL){
        ar->r = NULL;
    }
    return ar;
}

void inserirArvore(arvore ar, anteparo an){

}   

void removerArvore(arvore ar, anteparo an){

}

void liberarArvore(arvore ar){

}