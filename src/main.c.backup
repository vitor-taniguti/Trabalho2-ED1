#include "forma.h"
#include "lista.h"
#include "arvore.h"
#include "geo.h"
#include "qry.h"
#include "txt.h"
#include "svg.h"
#include "trataArquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LEN 512
#define FILE_NAME_LEN 256

typedef FILE* arquivo;

int main(int argc, char *argv[]) {
    char dirEntrada[PATH_LEN] = ".";
    char dirSaida[PATH_LEN] = ".";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    char tipoSort = 'q';
    int temGeo = 0, temSaida = 0, temQry = 0, limite = 0;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc){
            trataCaminho(dirEntrada, PATH_LEN, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc){
            trataCaminho(dirSaida, PATH_LEN, argv[++i]);
            temSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc){
            strcpy(nomeArquivoGeo, argv[++i]);
            temGeo = 1;
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc){
            strcpy(nomeArquivoQry, argv[++i]);
            temQry = 1;
        } else if (strcmp(argv[i], "-to") == 0 && i + 1 < argc){
            char* val = argv[++i];
            if (strcmp(val, "m") == 0) tipoSort = 'm';
            else tipoSort = 'q';
        } else if (strcmp(argv[i], "-in") == 0 && i + 1 < argc){
            limite = atoi(argv[++i]);
        } else{
            fprintf(stderr, "Parâmetro desconhecido ou inválido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!temGeo || !temSaida){
        fprintf(stderr, "Erro: parâmetros obrigatórios -f (geo) e -o (saida) não fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[PATH_LEN + FILE_NAME_LEN];
    snprintf(fullPathGeo, sizeof(fullPathGeo), "%s/%s", dirEntrada, nomeArquivoGeo);

    char fullPathQry[PATH_LEN + FILE_NAME_LEN];
    if (temQry) snprintf(fullPathQry, sizeof(fullPathQry), "%s/%s", dirEntrada, nomeArquivoQry);

    char baseNomeGeo[FILE_NAME_LEN];
    char baseNomeCombinado[FILE_NAME_LEN];
    
    combinacaoNomeArquivo(nomeArquivoGeo, NULL, baseNomeGeo, sizeof(baseNomeGeo));

    char arquivoSaidaSvgGeo[PATH_LEN + FILE_NAME_LEN];
    snprintf(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), "%s/%s.svg", dirSaida, baseNomeGeo);

    char arquivoSaidaSvgQry[PATH_LEN + FILE_NAME_LEN];
    char arquivoSaidaTxt[PATH_LEN + FILE_NAME_LEN];

    if (temQry){
        combinacaoNomeArquivo(nomeArquivoGeo, nomeArquivoQry, baseNomeCombinado, sizeof(baseNomeCombinado));
        snprintf(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry), "%s/%s.svg", dirSaida, baseNomeCombinado);
        snprintf(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), "%s/%s.txt", dirSaida, baseNomeCombinado);
    }

    arquivo geo = NULL;
    arquivo qry = NULL;
    arquivo txt = NULL;
    arquivo svgGeo = NULL;
    arquivo svgQry = NULL;

    abrirArquivoGeo(&geo, fullPathGeo);
    if (temQry){
        abrirArquivoQry(&qry, fullPathQry);
        abrirArquivoTxt(&txt, arquivoSaidaTxt);
        abrirArquivoSvg(&svgQry, arquivoSaidaSvgQry);
        inicializarSVG(svgQry);
    }
    abrirArquivoSvg(&svgGeo, arquivoSaidaSvgGeo);
    inicializarSVG(svgGeo);

    lista listaFormas = criarLista();
    lista listaAnteparos = criarLista();

    tipoTexto tt = criarTipoTexto("Arial, sans-serif", "normal", "12px");

    lerArquivoGeo(geo, listaFormas, tt);

    passarPelaLista(listaFormas, svgGeo, tt);
    fecharSVG(svgGeo);

    if (temQry){
        lerArquivoQry(qry, txt, svgQry, listaFormas, listaAnteparos, dirSaida, nomeArquivoGeo, tipoSort, limite);
        passarPelaLista(listaFormas, svgQry, tt);
        fecharSVG(svgQry);
    }

    liberarTipoTexto(tt);

    if (geo) fclose(geo);
    if (qry) fclose(qry);
    if (txt) fclose(txt);
    if (svgGeo) fclose(svgGeo);
    if (svgQry) fclose(svgQry);

    return 0;
}