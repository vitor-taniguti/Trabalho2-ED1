#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "poligono.h"
#include "vertice.h"
#include <math.h>

/// @brief Calcula a distância entre dois pontos
/// @param x1 Coordenada X do primeiro ponto
/// @param y1 Coordenada Y do segundo ponto
/// @param x2 Coordenada X do primeiro ponto
/// @param y2 Coordenada Y do segundo ponto
/// @return Um double com a distância entre os dois pontos
double calcularDistancia(double x1, double y1, double x2, double y2);

/// @brief Transforma ângulos negativos para seus relativos positivos
/// @param angulo Ângulo que será normalizado
/// @return Um double com o ângulo normalizado
double normalizarAngulo(double angulo);

/// @brief Calcula o ponto de intersecção do segmento e de uma reta de origem na bomba e destino no segmento
/// @param bx Coordenada X da bomba
/// @param by Coordenada Y da bomba
/// @param angulo Ângulo da reta de origem na bomba e destino no segmento
/// @param a Ponteiro para o anteapro (segmento) que será analisado
/// @return Ponteiro para o vértice (ponto de intersecção)
vertice calcularInterseccao(double bx, double by, double angulo, anteparo a);

#endif