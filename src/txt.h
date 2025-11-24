#ifndef TXT_H
#define TXT_H

#include <stdio.h>
#include <stdlib.h>
#include "forma.h"

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos com final .txt.
Os comentários feitos estão no padrão que o trabalho solicitou.
*/

typedef FILE* arquivo;
typedef void* Forma;

/// @brief Abre um arquivo de texto para gravação
/// @param txt Ponteiri duplo para o endereço do arquivo
/// @param caminhoTxt Ponteiro para o caminho onde será salvo o arquivo de texto
void abrirArquivoTxt(arquivo *txt, char *caminhoTxt);

/// @brief Imprime os dados da forma
/// @param txt Ponteiro para o arquivo de saída
/// @param f Ponteiro para a forma carregada
/// @param tipoForma Tipo da forma que os dados serão printados (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
void printarDadosForma(arquivo txt, forma f, int tipoForma);

#endif