#ifndef POLIGONO_H
#define POLIGONO_H

#include "anteparos.h"
#include "vertice.h"
#include "sort.h"
#include "lista.h"
#include "arvore.h"

typedef void* poligono;

/// @brief Cria o polígono de visibilidade
/// @return Ponteiro para o polígono criado
poligono criarPoligono();

/// @brief Calcula o polígono de visibilidade da bomba
/// @param p Ponteiro para o polígono que será calculado
/// @param listaAnteparos Lista com os anteparos 
/// @param atingidos Lista com as formas atingidas
/// @param bx Coordenada X da bomba
/// @param by Coordenada Y da bomba
/// @param tipoSort Char para o tipo de ordenação utilizada ('q' - qsort, 'm' - msort)
/// @param limite Limite para utilizar o insertion sort
void calcularPoligono(poligono p, lista listaAnteparos, lista atingidos, double bx, double by, char tipoSort, int limite);

/// @brief Pega o bounding box do polígono solicitado
/// @param p Ponteiro para o polígono que o bounding box será pego
/// @param minX Menor coordenada X do polígono
/// @param minY Menor coordenada Y do polígono
/// @param maxX Maior coordenada X do polígono 
/// @param maxY Maior coordenada Y do polígono
void getBoundingBoxPoligono(poligono p, double* minX, double* minY, double* maxX, double* maxY);

/// @brief Pega a quantidade total de pontos no polígono
/// @param p Ponteiro para o polígono que o total de pontos será pego
/// @return Um double com a quantidade total de pontos do polígono
int getTotalVerticesPoligono(poligono p);

/// @brief Pega as coordenadas de um ponto específico do polígono
/// @param p Ponteiro para o polígono que as coordenadas do ponto serão pegas
/// @param n Número do ponto que será pego
/// @param x Coordenada X do ponto que será pego
/// @param y Coordenada Y do ponto que será pego
void getVerticePoligono(poligono p, int n, double* x, double* y);

/// @brief Calcula a distância entre dois pontos
/// @param x1 Primeira coordenada X do ponto
/// @param y1 Primeira coordenada Y do ponto
/// @param x2 Segunda coordenada X do ponto
/// @param y2 Segunda coordenada Y do ponto
/// @return Um double com a distância entre os dois pontos
double calcularDistancia(double x1, double y1, double x2, double y2);

/// @brief Libera o polígono 
/// @param p Ponteiro para o polígono criado
void liberarPoligono(poligono p);

#endif