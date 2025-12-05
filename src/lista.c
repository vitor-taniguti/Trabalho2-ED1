#include "lista.h"
#include "svg.h"
#include "forma.h"
#include <stdio.h>
#include <stdlib.h>

typedef void* forma;

typedef struct elemento{
    forma forma;
    int tipoForma;
    struct elemento *prox;
    struct elemento *ant;
} Elemento;

typedef Elemento *pont;

typedef struct{
    int tamanho;
    pont topo;
    pont fim;
} Lista;

lista criarLista(){
    Lista *l = malloc(sizeof(Lista));
    if (l == NULL){
        printf("Falha na alocação de memória! Na criação da lista!\n");
        exit(1);
    }
    l->topo = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return ((Lista*)l);
}

void inserirLista(lista l, forma forma, int tipoForma){
    Lista *lista = ((Lista*)l);
    Elemento *novoElemento = (Elemento*) malloc(sizeof(Elemento));
    if (novoElemento == NULL){
        printf("Falha na alocação de memória! Na inserição na lista\n");
        exit(1);
    }
    novoElemento->forma = forma;
    novoElemento->tipoForma = tipoForma;
    novoElemento->prox = NULL;
    if (lista->fim == NULL){  
        novoElemento->ant = NULL;
        lista->topo = novoElemento;
        lista->fim = novoElemento;
    } else{
        novoElemento->ant = lista->fim;
        lista->fim->prox = novoElemento;     
        lista->fim = novoElemento;
    }
    lista->tamanho++;
}

void removerLista(lista l, iterador i){
    Lista *lista = ((Lista*)l);
    Elemento *alvo = (Elemento*)i;
    if (lista == NULL || alvo == NULL) return;
    if (alvo->ant != NULL){
        alvo->ant->prox = alvo->prox;
    } else{
        lista->topo = alvo->prox;
    }
    if (alvo->prox != NULL){
        alvo->prox->ant = alvo->ant;
    } else{
        lista->fim = alvo->ant;
    }
    if (alvo->forma != NULL) liberarForma(alvo->forma, alvo->tipoForma);
    free(alvo);
    lista->tamanho--;
}

iterador buscarLista(lista l, forma alvo){
    Lista* lista = (Lista*)l;
    Elemento* atual = lista->topo;
    if (lista == NULL) return NULL;
    while (atual != NULL){
        if (atual->forma == alvo){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

iterador getPrimeiroLista(lista l){
    Lista *lista = ((Lista*)l);
    if (lista->topo == NULL){
        return NULL;
    }
    return lista->topo;
}

iterador getProximoLista(iterador i){
    Elemento *e = (Elemento*)i;
    if (e == NULL || e->prox == NULL){
        return NULL;
    }
    return e->prox;
}

iterador getAnteriorLista(iterador i){
    Elemento *e = (Elemento*)i;
    if (e == NULL || e->prox == NULL){
        return NULL;
    }
    return e->ant;
}

iterador getUltimoLista(lista l){
    Lista *lista = ((Lista*)l);
    return lista->fim;
}

forma getFormaLista(iterador i){
    Elemento *e = (Elemento*)i;
    return e->forma;
}

int getTipoFormaLista(iterador i){
    Elemento *e = (Elemento*)i;
    return e->tipoForma;
}

int getMaiorIdLista(lista l){
    Lista* lista = ((Lista*)l);
    Elemento* atual = lista->topo;
    int maior = 0;
    while (atual != NULL){
        forma forma = getFormaLista(atual);
        int tipoForma = getTipoFormaLista(atual);
        int id = getIdForma(forma, tipoForma);
        if (id > maior){
            maior = id;
        }
        atual = atual->prox;
    }
    return maior;
}

int getTamanhoLista(lista l){
    return ((Lista*)l)->tamanho;
}

void passarPelaLista(lista l, arquivo svg, tipoTexto tipoTexto){
    Lista *lista = ((Lista*)l);
    Elemento *elementoAtual = lista->topo;
    while (elementoAtual != NULL){
        selecionarAcaoLista(elementoAtual->forma, elementoAtual->tipoForma, svg, tipoTexto);
        Elemento *proximoElemento = elementoAtual->prox;
        elementoAtual = proximoElemento;
    }
}

void selecionarAcaoLista(forma forma, int tipoForma, arquivo svg, tipoTexto tipoTexto){
    switch (tipoForma){
        case 1:
            inserirRetanguloSVG(svg, forma);
            break;
        case 2:
            inserirCirculoSVG(svg, forma);
            break;
        case 3:
            inserirLinhaSVG(svg, forma);
            break;
        case 4:
            inserirTextoSVG(svg, forma, tipoTexto);
            break;
        case 5:
            inserirLinhaSVG(svg, forma);
        default:
            break;
    }
}

void liberarLista(lista l){
    Lista *lista = ((Lista*)l);
    Elemento *elementoAtual = lista->topo;
    while (elementoAtual != NULL){
        Elemento *proximoElemento = elementoAtual->prox;
        if (elementoAtual->forma != NULL){
            liberarForma(elementoAtual->forma, elementoAtual->tipoForma);
        }
        free(elementoAtual);
        elementoAtual = proximoElemento;
    }
    free(lista);
}

void liberarApenasNosLista(lista l){
    Lista* lista = (Lista*)l;
    Elemento* atual = lista->topo;
    while (atual != NULL){
        Elemento* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}