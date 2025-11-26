#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include "forma.h"

/*
Módulo responsável por gerenciar a estrutura de dado lista, incluindo suas operações de criar, inserir, remover, get e liberar memória.
*/

typedef FILE *arquivo;
typedef void *lista;
typedef void *iterador;

/// @brief Cria uma nova lista vazia
/// @return Ponteiro para a nova lista criada
lista criarLista();

/// @brief Insere um elemento no final da lista
/// @param l Ponteiro para a lista onde a forma será inserida
/// @param forma Forma a ser inserida na lista
/// @param tipoForma Tipo da forma a ser inserida na lista (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto, 5-Anteparo)
void inserirLista(lista l, forma forma, int tipoForma);

/// @brief Remove o primeiro elemento da lista
/// @param l Ponteiro para a lista onde a forma será removida
/// @param i Ponteiro para o elemento que será apagado
void removerLista(lista l, iterador i);

/// @brief Busca o ponteiro para o elemento solicitado
/// @param l Ponteiro para a lista onde acontecerá a busca
/// @param alvo Forma que será buscada
/// @return Ponteiro para o elemento encontrado ou NULL se falhar
iterador buscarLista(lista l, forma alvo);

/// @brief Pega o primeiro elemento da lista (sem remover)
/// @param l Ponteiro para a lista onde o elemento será pego
/// @return Ponteiro para o primeiro elemento ou NULL se estiver vazia
iterador getPrimeiroLista(lista l);

/// @brief Pega o proximo elemento da lista (sem remover)
/// @param i Elemento que o próximo elemento será pego
/// @return Ponteiro para o próximo elemento ou NULL se estiver vazia
iterador getProximoLista(iterador i);

/// @brief Pega o elemento anterior da lista (sem remover)
/// @param i Elemento que o elemento anterior será pego
/// @return Ponteiro para o elemento anterior ou NULL se estiver vazia
iterador getAnteriorLista(iterador i);

/// @brief Pega a forma do elemento da lista
/// @param i Ponteiro para o elemento que a forma será pega
/// @return Um ponteiro para a forma pega
forma getFormaLista(iterador i);

/// @brief Pega o tipo da forma do elemento da lista
/// @param i Ponteiro para o elemento que o tipo será pego
/// @return Um inteiro com o tipo da forma pega
int getTipoFormaLista(iterador i);

/// @brief Pega o maior id das formas
/// @param l Ponteiro para a lista onde o id será pego
/// @return Um inteiro com o maior id
int getMaiorIdLista(lista l);

/// @brief Pega o tamanho da lista
/// @param l Ponteiro para a lista onde o tamanho será pego
/// @return Um inteiro com o tamanho da lista
int getTamanhoLista(lista l);

/// @brief Percorre pela lista e aplica uma ação a cada elemento
/// @param l Ponteiro para a lista a ser percorrida
/// @param svg Ponteiro para o arquivo SVG onde os elementos serão inseridos
/// @param tipoTexto Tipo do texto a ser usado nos elementos tipo texto
void passarPelaLista(lista l, arquivo svg, tipoTexto tipoTexto);

/// @brief Seleciona a ação a ser realizada para um elemento da lista
/// @param forma Ponteiro para a forma a ser processada
/// @param tipoForma Tipo de elemento na lista (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto, 5-Anteparo)
/// @param svg Ponteiro para o arquivo SVG onde os elementos serão inseridos
/// @param tipoTexto Tipo do texto a ser usado nos elementos tipo texto
void selecionarAcaoLista(forma forma, int tipoForma, arquivo svg, tipoTexto tipoTexto);

/// @brief Libera toda memória alocada da lista e seus elementos
/// @param l Ponteiro para a lista que será liberada
void liberarLista(lista l);

/// @brief Libera apenas os nós da lista (sem liberar o conteúdo)
/// @param l Ponteiro para a lista que os nós serão liberados
void liberarApenasNosLista(lista l);

#endif