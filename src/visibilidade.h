#ifndef VISIBILIDADE_H  
#define VISIBILIDADE_H

#include "anteparos.h"

typedef void* ponto;

/// @brief Compara a distancia entre os anteparos com a reta que vai do observador até o destino
/// @param observador Ponto onde a reta começa (local da bomba)
/// @param destino Ponto onde a reta termina (ponto de um anteparo)
/// @param a1 Ponteiro para o primeiro anteparo que será comparado
/// @param a2 Ponteiro para o segundo anteparo qeu será comparado
/// @return -1 se a1 for mais perto, 1 se a2 for mais perto e 0 se os dois estiverem equidistantes
int compararDistanciaAnteparos(ponto observador, ponto destino, anteparo a1, anteparo a2);

#endif