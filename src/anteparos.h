#ifndef ANTEPAROS_H
#define ANTEPAROS_H

#include "forma.h"

typedef void* anteparo; 

/// @brief Cria um anteparo com os atributos especificados
/// @param x1 Primeira coordenada X do anteparo
/// @param y1 Primeira coordenada Y do anteparo
/// @param x2 Segunda coordenada X do anteparo
/// @param y2 Segunda coordenada Y do anteparo
/// @param cor Cor do anteparo
/// @return Um ponteiro para o anteparo criado
anteparo criarAnteparo(double x1, double y1, double x2, double y2, char* cor);

/// @brief Transforma um círculo em anteparo
/// @param f Ponteiro para a forma que será transformada em anteparo 
/// @param tipoForma Tipo da forma que será transformada em anteparo (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @return Um ponteiro para o anteparo criado
anteparo transformarFormaAnteparo(forma f, int tipoForma);

#endif