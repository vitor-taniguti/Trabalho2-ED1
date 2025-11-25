#ifndef POLIGONO_H
#define POLIGONO_H

#include "anteparos.h"
#include "sort.h"
#include "lista.h"
#include "arvore.h"

typedef void* poligono;

/// @brief Cria o polígono de visibilidade da bomba
/// @param listaAnteparos Lista com os anteparos 
/// @param bx Coordenada X da bomba
/// @param by Coordenada Y da bomba
/// @return Um ponteiro para o polígono criado
poligono criarPoligono(lista listaAnteparos, double bx, double by);

#endif