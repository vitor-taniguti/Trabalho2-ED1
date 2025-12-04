#ifndef VERTICE_H
#define VERTICE_H

#include "anteparos.h"
#include "lista.h"
#include "sort.h"

typedef void* vertice;

/// @brief Cria a forma vértice
/// @return Ponteiro para forma vértice criada
vertice criarVertice();

/// @brief Pega a coordenada X do vértice
/// @param v Ponteiro para o vértice
/// @return Um double com a coordenada X do vértice
double getXVertice(vertice v);

/// @brief Pega a coordenada Y do vértice
/// @param v Ponteiro para o vértice
/// @return Um double com a coordenada Y do vértice
double getYVertice(vertice v);

/// @brief Pega o ângulo do vértice
/// @param v Ponteiro para o vértice
/// @return Um double com o ângulo do vértice
double getAnguloVertice(vertice v);

/// @brief Pega a distância do vértice
/// @param v Ponteiro para o vértice
/// @return Um double com a distância do vértice
double getDistanciaVertice(vertice v);

/// @brief Pega o tipo do vértice
/// @param v Ponteiro para o vértice
/// @return Um inteiro com o tipo do vértice (1-Início, 2-Fim)
int getTipoVertice(vertice v);

/// @brief Pega o anteparo relacionado ao vértice
/// @param v Ponteiro para o vértice
/// @return Ponteiro para o anteparo relacionado ao vértice
anteparo getAnteparoVertice(vertice v);

/// @brief Define a coordenada X do vértice
/// @param v Ponteiro para o vértice
/// @param x Nova coordenada X do vértice
void setXVertice(vertice v, double x);

/// @brief Define a coordenada Y do vértice
/// @param v Ponteiro para o vértice
/// @param x Nova coordenada Y do vértice
void setYVertice(vertice v, double y);

/// @brief Define a distância do vértice
/// @param v Ponteiro para o vértice
/// @param distancia Nova distância do vértice
void setDistanciaVertice(vertice v, double distancia);

/// @brief Cria uma lista ordenada dos vértices com relação ao ângulo
/// @param listaAnteparos Lista de anteparos 
/// @param x Coordenada X da bomba
/// @param y Coordenada Y da bomba
/// @param tipoSort Tipo de ordenação que será utilizada
/// @param limite Limite para o uso de insertion sort
/// @return Ponteiro para a lista ordenada criada
lista criarListaOrdenadaVertices(lista listaAnteparos, double x, double y, int tipoSort, int limite);

/// @brief Libera o vértice solicitado
/// @param v Ponteiro para o vértice que será liberado
void liberarVertice(vertice v);

#endif