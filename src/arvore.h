#ifndef ARVORE_H
#define ARVORE_H

#include "anteparos.h"

typedef void* arvore;
typedef void* iterador;

/// @brief Cria a estrutura de dado árvore binária de busca
/// @return Um ponteiro para a árvore criada
arvore criarArvore();

/// @brief Insere, de forma ordenada e recursiva, o anteparo na árvore
/// @param ar Ponteiro para a árvore que o anteparo será inserido
/// @param an Ponteiro para o anteparo que será inserido
/// @param bx Coordenada X da bomba
/// @param by Coordenada Y da bomba
/// @param angulo Angulo atual em relação à bomba
/// @param distanciaDoEvento Distância em relação ao evento atual
void inserirArvore(arvore ar, anteparo an, double bx, double by, double angulo, double distanciaDoEvento);

/// @brief Pega o elemento com a menor distância em relação à outro elemento
/// @param i Ponteiro para o elemento que a distância será comparada
/// @return Ponteiro para o elemento com a menor distância em relação à outro elemento
iterador getMenorRecursivo(iterador i);

/// @brief Pega o elemento com a menor distância da árvore
/// @param ar Ponteiro para a árvore que o elemento será pego
/// @return Ponteiro para o elemento com menor distância
iterador getMenorArvore(arvore ar);

/// @brief Pega o elemento com a maior distância em relação à outro elemento
/// @param i Ponteiro para o elemento que a distância será comparada
/// @return Ponteiro para o elemento com a maior distância em relação à outro elemento
iterador getMaiorRecursivo(iterador i);

/// @brief Pega o elemento com a maior distâcia da árvore
/// @param ar Ponteiro para a árvore que o elemento será pego
/// @return Ponteiro para o elemento com a maior distância
iterador getMaiorArvore(arvore ar);

/// @brief Remove o anteparo solicitado da árvore
/// @param ar Ponteiro para a árvore que o anteparo será removido
/// @param an Ponteiro para o anteparo que será removido
void removerArvore(arvore ar, anteparo an);

/// @brief Pega o anteparo do elemento solicitado
/// @param i Ponteiro para o elemento que o anteparo será pego
/// @return Ponteiro para o anteparo pego
anteparo getAnteparoArvore(iterador i);

/// @brief Libera toda a memória alocada para a construção da árvore
/// @param ar Ponteiro para a árvore que será liberada
void liberarArvore(arvore ar);

#endif