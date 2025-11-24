#ifndef ARVORE_H
#define ARVORE_H

#include "anteparos.h"

typedef void* arvore;
typedef void* iterador;

/// @brief Cria a estrutura de dado árvore binária de busca
/// @return Um ponteiro para a árvore
arvore criarAvore();

/// @brief Insere, de forma ordenada e recursiva, o anteparo na árvore
/// @param ar Ponteiro para a árvore que o anteparo será inserido
/// @param an Ponteiro para o anteparo que será inserido
void inserirArvore(arvore ar, anteparo an);

/// @brief Remove o anteparo solicitado da árvore
/// @param ar Ponteiro para a árvore que o anteparo será removido
/// @param an Ponteiro para o anteparo que será removido
void removerArvore(arvore ar, anteparo an);

/// @brief Libera toda a memória alocada para a construção da árvore
/// @param ar Ponteiro para a árvore que será liberada
void liberarArvore(arvore ar);

#endif