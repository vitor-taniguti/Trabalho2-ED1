#ifndef COLISAO_H
#define COLISAO_H

#include "poligono.h"

/// @brief Pega as formas que foram atingidas pela bomba
/// @param bx Coordenada X da bomba
/// @param by Coordenada Y da bomba
/// @param anteparos Lista dos anteparos
/// @param alvos Lista das formas
/// @return Uma lista com as formas que foram atingidas
lista obterAlvosAtingidos(double bx, double by, lista anteparos, lista alvos);

#endif