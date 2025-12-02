#ifndef COLISAO_H
#define COLISAO_H

#include "poligono.h"

/// @brief Pega as formas que foram atingidas pela bomba e insere na lista de atingidos
/// @param p Ponteiro para o polígono de visibilidade
/// @param atingidos Lista das formas atingidas
/// @param alvos Lista das formas
void obterAlvosAtingidos(poligono p, lista atingidos, lista alvos);

#endif