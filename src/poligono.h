#ifndef POLIGONO_H
#define POLIGONO_H

#include "anteparos.h"
#include "sort.h"
#include "lista.h"
#include "arvore.h"

typedef void* poligono;
typedef void* ponto;

/// @brief Cria o polígono de visibilidade da bomba
/// @param listaAnteparos Lista com os anteparos 
/// @param bx Coordenada X da bomba
/// @param by Coordenada Y da bomba
/// @return Um ponteiro para o polígono criado
poligono criarPoligono(lista listaAnteparos, double bx, double by);

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
int getTotalPontosPoligono(poligono p);

/// @brief Pega as coordenadas de um ponto específico do polígono
/// @param p Ponteiro para o polígono que as coordenadas do ponto serão pegas
/// @param n Número do ponto que será pego
/// @param x Coordenada X do ponto que será pego
/// @param y Coordenada Y do ponto que será pego
void getPontoPoligono(poligono p, int n, double* x, double* y);

/// @brief Libera o polígono 
/// @param p Ponteiro para o polígono criado
void liberarPoligono(poligono p);


#endif