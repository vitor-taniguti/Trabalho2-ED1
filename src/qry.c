#include "qry.h"
#include "txt.h"
#include "svg.h"
#include "lista.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void abrirArquivoQry(arquivo *qry, char *caminhoQry){
    *qry = fopen(caminhoQry, "r");
    if(*qry == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, lista listaFormas, arvore anteparos){
    if (qry == NULL){
        printf("Arquivo não foi aberto!");
        return;
    }
    char linha[256], comando[5];
    while (fgets(linha, sizeof(linha), qry)){
        int i = 0;
        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }
        comando[i] = '\0';
        processarLinhaComandos(linha, comando, listaFormas, anteparos, txt, svg);
    }
}

void processarLinhaComandos(char *linha, char *comando, lista listaFormas, arvore anteparos, arquivo txt, arquivo svg){
    int i, j;
    double x, y, dx, dy;
    char orientacao, com[4], sfx[16], cor[8];
    fprintf(txt, "[*] %s\n", linha);
    if (strcmp(comando, "a") == 0){
        sscanf(linha, "%2s %d %d %c", com, &i, &j, &orientacao); 
        a(i, j, orientacao, listaFormas, txt);
    } else if (strcmp(comando, "d") == 0){
        sscanf(linha, "%2s %lf %lf %s", com, &x, &y, sfx);
        d(x, y, sfx, listaFormas, anteparos, txt, svg);
    } else if (strcmp(comando, "p") == 0){
        sscanf(linha, "%2s %lf %lf %8s %s", com, &x, &y, cor, sfx);
        p(x, y, cor, sfx, listaFormas, anteparos, txt, svg);
    } else if (strcmp(comando, "cln") == 0){
        sscanf(linha, "%4s %lf %lf %lf %lf %s", com, &x, &y, &dx, &dy, sfx);
        cln(x, y, dx, dy, sfx, listaFormas, anteparos, txt, svg);
    }
}

void a(int i, int j, char orientacao, lista listaFormas, arquivo txt){
    fprintf(txt, "Formas transformadas em anteparo:\n\n");
    iterador atual = getPrimeiroFila(listaFormas);
    while (atual != NULL){
        forma forma = getFormaFila(atual);
        int tipoForma = getTipoFormaFila(atual);
        int id = getIdForma(forma, tipoForma);
        iterador proximo = getProximoLista(atual);
        if (id >= i && id <= j){
            switch (tipoForma){
                case 1:
                    anteparo* a = transformarRetangulo(atual);
                    for (int i = 0; i < 4; i++){
                        inserirLista(listaFormas, a[i], 5);
                    }
                    break;
                case 2:
                    inserirLista(listaFormas, transformarCirculo(atual, orientacao), 5);
                    break;
                case 3:
                    inserirLista(listaFormas, transformarLinha(atual), 5);
                    break;
                case 4:
                    inserirLista(listaFormas, transformarTexto(atual), 5);
                    break;
            }
            removerLista(listaFormas, atual);
            printarDadosForma(txt, forma, tipoForma);
        }
        atual = proximo;
    }
}