#ifndef FORMA_H
#define FORMA_H

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "anteparos.h"
#include <math.h>

typedef void* forma;

/// @brief Pega o id da forma solicitada
/// @param f Ponteiro para a forma que o id será pego
/// @param tipoForma Tipo da forma que o id será pego (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @return Um inteiro com o id da forma
int getIdForma(forma f, int tipoForma);

/// @brief Pega a coordenada X da forma solicitada
/// @param f Ponteiro para a forma que a coordenada será pega
/// @param tipoForma Tipo da forma que a coordenada será pega (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @return Um double com a coordenada X da forma
double getXForma(forma f, int tipoForma);

/// @brief Pega a coordenada Y da forma solicitada
/// @param f Ponteiro para a forma que a coordenada será pega
/// @param tipoForma Tipo da forma que a coordenada será pega (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @return Um double com a coordenada Y da forma
double getYForma(forma f, int tipoForma);

/// @brief Define a cor de borda da forma solicitada
/// @param f Ponteiro para a forma que a cor será definida
/// @param tipoForma Tipo da forma que a cor será definida
/// @param corB String contendo a cor de borda a ser definida
void setCorBForma(forma f, int tipoForma, char* corB);

/// @brief Define a cor de preenchimento da forma solicitada
/// @param f Ponteiro para a forma que a cor será definida
/// @param tipoForma Tipo da forma que a cor será definida
/// @param corP String contendo a cor de borda a ser definida
void setCorPForma(forma f, int tipoForma, char* corP);

/// @brief Clona a forma solicitada
/// @param f Ponteiro para a forma que será clonada
/// @param tipoForma Tipo da forma que será clonada
/// @param listaFormas Lista das formas
/// @return Ponteiro para a forma clonada
forma clonarForma(forma f, int tipoForma, lista listaFormas);

/// @brief Calcula o bounding box da forma solicitada
/// @param f Ponteiro para a forma que o bounding box será calculado
/// @param tipoForma Tipo da forma que o bounding box será calculado
/// @param x1 Menor coordenada X da forma
/// @param y1 Menor coordenada Y da forma
/// @param x2 Maior coordenada X da forma 
/// @param y2 Maior coordenada Y da forma
void calcularBoundingBoxForma(forma f, int tipoForma, double *x1, double *y1, double *x2, double *y2);

/// @brief Libera a forma solicitada
/// @param f Ponteiro para a forma que será liberada
/// @param tipoForma Tipo da forma que será liberada
void liberarForma(forma f, int tipoForma);

#endif