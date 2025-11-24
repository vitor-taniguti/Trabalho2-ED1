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

/// @brief Transforma a forma retângulo em anteparo
/// @param f Ponteiro para a forma retângulo
/// @return Um ponteiro para o anteparo criado
anteparo* transformarRetangulo(forma f);

/// @brief Transforma a forma círculo em anteparo
/// @param f Ponteiro para a forma círculo
/// @return Um ponteiro para o anteparo criado
anteparo transformarCirculo(forma f, char orientacao);

/// @brief Transforma a forma linha em anteparo
/// @param f Ponteiro para a forma linha
/// @return Um ponteiro para o anteparo criado
anteparo transformarLinha(forma f);

/// @brief Transforma a forma texto em anteparo
/// @param f Ponteiro para a forma texto
/// @return Um ponteiro para o anteparo criado
anteparo transformarTexto(forma f);

/// @brief Libera o anteparo
/// @param a Ponteiro para o anteparo que será liberado
void liberarAnteparo(anteparo a);

#endif