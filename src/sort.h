#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <string.h>

/// @brief Ordena a base usando o método dividir e conquistar
/// @param base Ponteiro para a base que será ordenada
/// @param nmemb Número de elementos da base
/// @param size Tamanho de um elemento da base
/// @param compar Função de comparação dos elementos
/// @param limite Limite até o insertion sort ser utilizado
void msort(void* base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int limite);

#endif