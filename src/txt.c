#include "txt.h"

void abrirArquivoTxt(arquivo *saida, char *caminhoTxt){
    *saida = fopen(caminhoTxt, "w");
    if (*saida == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
}

void printarDadosForma(arquivo txt, forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            fprintf(txt, "Retângulo - Id: %d\n", getIdRetangulo(f));
            break;
        case 2:
            fprintf(txt, "Círculo - Id: %d\n", getIdCirculo(f));
            break;
        case 3:
            fprintf(txt, "Linha - Id: %d\n", getIdLinha(f));
            break;
        case 4:
            fprintf(txt, "Texto - Id: %d\n", getIdTexto(f));
            break;
        default:
            printf("Tipo de forma inválido!\n");
            break;
    }
}