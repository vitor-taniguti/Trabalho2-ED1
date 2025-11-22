#ifndef FORMA_H
#define FORMA_H

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "anteparos.h"
#include <math.h>

typedef void* forma;

/// @brief Pega o id do forma solicitada
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

/// @brief Transforma um círculo em anteparo
/// @param f Ponteiro para a forma que será transformada em anteparo 
/// @param tipoForma Tipo da forma que será transformada em anteparo (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @param oreitacao Caractere que identifica se o círculo será transformado em um anteparo na vertical (v) ou na horizontal (h)
/// @return Um ponteiro para o anteparo criado
anteparo transformarFormaAnteparo(forma f, int tipoForma, char orientacao);

#endif