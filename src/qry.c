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

arquivo abrirNovoSVG(char* diretorioSaida, char* nomeBase, char* sufixo) {
    char nomeCompleto[512];
    sprintf(nomeCompleto, "%s/%s-%s.svg", diretorioSaida, nomeBase, sufixo);
    FILE* f = fopen(nomeCompleto, "w");
    if (f) {
        fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    }
    return f;
}

void logicaSfx(char* sfx, poligono p, arquivo svg, char* dirSaida, char* nomeGeo, double bx, double by){
    if (strcmp(sfx, "-") == 0){
        inserirPoligonoSVG(svg, p, "gray", "black");
        fprintf(svg, "<circle cx=\"%f\" cy=\"%f\" r=\"3\" stroke=\"black\" fill=\"red\" />\n", bx, by);
    } else{
        arquivo arquivoSfx = abrirNovoSVG(dirSaida, nomeGeo, sfx);
        inserirPoligonoSVG(arquivoSfx, p, "gray", "black");
        fprintf(arquivoSfx, "<circle cx=\"%f\" cy=\"%f\" r=\"3\" stroke=\"black\" fill=\"red\" />\n", bx, by);
        fecharSVG(arquivoSfx);
        fclose(arquivoSfx);
    }
}

void a(int i, int j, char orientacao, lista listaFormas, lista listaAnteparos, arquivo txt){
    fprintf(txt, "\nFormas transformadas em anteparo:\n\n");
    iterador atual = getPrimeiroLista(listaFormas);
    while (atual != NULL){
        forma f = getFormaLista(atual);
        int tipoForma = getTipoFormaLista(atual);
        int id = getIdForma(f, tipoForma);
        iterador proximo = getProximoLista(atual);
        if (id >= i && id <= j){
            switch (tipoForma){
                case 1:
                    anteparo* a = transformarRetangulo(f);
                    for (int k = 0; k < 4; k++){
                        inserirLista(listaAnteparos, a[k], 5);
                    }
                    free(a);
                    break;
                case 2:
                    inserirLista(listaAnteparos, transformarCirculo(f, orientacao), 5);
                    break;
                case 3:
                    inserirLista(listaAnteparos, transformarLinha(f), 5);
                    break;
                case 4:
                    inserirLista(listaAnteparos, transformarTexto(f), 5);
                    break;
            }
            printarDadosForma(txt, f, tipoForma);
            removerLista(listaFormas, atual);
        }
        atual = proximo;
    }
    fprintf(txt, "\n");
}

void d(double x, double y, char* sfx, lista formas, lista anteparos, arquivo txt, arquivo svg, char* dirSaida, char* nomeGeo, char tipoSort, int limite){
    fprintf(txt, "Formas destruídas: \n\n");
    poligono visibilidade = criarPoligono();
    lista atingidos = criarLista();
    calcularPoligono(visibilidade, anteparos, atingidos, x, y, tipoSort, limite);
    obterAlvosAtingidos(visibilidade, atingidos, formas);
    iterador atual = getPrimeiroLista(atingidos);
    while (atual != NULL){
        printarDadosForma(txt, getFormaLista(atual), getTipoFormaLista(atual));
        iterador proximo = getProximoLista(atual);
        int tipoFormaDestruida = getTipoFormaLista(atual);
        iterador elementoDestruido;
        if (tipoFormaDestruida != 5){
            elementoDestruido = buscarLista(formas, getFormaLista(atual));
            removerLista(formas, elementoDestruido);
        } else{
            elementoDestruido = buscarLista(anteparos, getFormaLista(atual));
            removerLista(anteparos, elementoDestruido);
        }
        atual = proximo;
    }
    logicaSfx(sfx, visibilidade, svg, dirSaida, nomeGeo, x, y);
    liberarPoligono(visibilidade);
    liberarApenasNosLista(atingidos);
    fprintf(txt, "\n");
}

void p(double x, double y, char* cor, char* sfx, lista formas, lista anteparos, arquivo txt, arquivo svg, char* dirSaida, char* nomeGeo, char tipoSort, int limite){
    fprintf(txt, "Formas pintadas: \n\n");
    poligono visibilidade = criarPoligono();
    lista atingidos = criarLista();
    calcularPoligono(visibilidade, anteparos, atingidos, x, y, tipoSort, limite);
    obterAlvosAtingidos(visibilidade, atingidos, formas);
    iterador atual = getPrimeiroLista(atingidos);
    while (atual != NULL){
        printarDadosForma(txt, getFormaLista(atual), getTipoFormaLista(atual));
        iterador proximo = getProximoLista(atual);
        iterador elementoPintado = buscarLista(formas, getFormaLista(atual));
        if (elementoPintado != NULL) {
            forma formaPintada = getFormaLista(elementoPintado);
            int tipoFormaPintada = getTipoFormaLista(elementoPintado);
            setCorBForma(formaPintada, tipoFormaPintada, cor);
            setCorPForma(formaPintada, tipoFormaPintada, cor);
        }
        atual = proximo;
    }
    logicaSfx(sfx, visibilidade, svg, dirSaida, nomeGeo, x, y);
    liberarPoligono(visibilidade);
    liberarApenasNosLista(atingidos);
    fprintf(txt, "\n");
}

void cln(double x, double y, double dx, double dy, char* sfx, lista formas, lista anteparos, arquivo txt, arquivo svg, char* dirSaida, char* nomeGeo, char tipoSort, int limite){
    fprintf(txt, "Formas clonadas: \n\n");
    poligono visibilidade = criarPoligono();
    lista atingidos = criarLista();
    calcularPoligono(visibilidade, anteparos, atingidos, x, y, tipoSort, limite);
    obterAlvosAtingidos(visibilidade, atingidos, formas);
    iterador atual = getPrimeiroLista(atingidos);
    while (atual != NULL){
        printarDadosForma(txt, getFormaLista(atual), getTipoFormaLista(atual));
        iterador proximo = getProximoLista(atual);
        iterador elementoClonado = buscarLista(formas, getFormaLista(atual));
        if (elementoClonado != NULL){
            forma formaClonada = getFormaLista(elementoClonado);
            int tipoFormaClonada = getTipoFormaLista(elementoClonado);
            if (tipoFormaClonada != 5) inserirLista(formas, clonarForma(formaClonada, tipoFormaClonada, formas, dx, dy), tipoFormaClonada);
            else inserirLista(anteparos, clonarForma(formaClonada, tipoFormaClonada, formas, dx, dy), tipoFormaClonada);
        }
        atual = proximo;
    }
    logicaSfx(sfx, visibilidade, svg, dirSaida, nomeGeo, x, y);
    liberarPoligono(visibilidade);
    liberarApenasNosLista(atingidos);
    fprintf(txt, "\n");
}

void processarLinhaComandos(char *linha, char *comando, lista listaFormas, lista listaAnteparos, arquivo txt, arquivo svg, char* dirSaida, char* nomeGeo, char tipoSort, int limite){
    int i, j;
    double x, y, dx, dy;
    char orientacao, com[4], sfx[16], cor[8];
    fprintf(txt, "[*] %s\n", linha);
    if (strcmp(comando, "a") == 0){
        sscanf(linha, "%2s %d %d %c", com, &i, &j, &orientacao); 
        a(i, j, orientacao, listaFormas, listaAnteparos, txt);
    } else if (strcmp(comando, "d") == 0){
        sscanf(linha, "%2s %lf %lf %s", com, &x, &y, sfx);
        d(x, y, sfx, listaFormas, listaAnteparos, txt, svg, dirSaida, nomeGeo, tipoSort, limite);
    } else if (strcmp(comando, "p") == 0){
        sscanf(linha, "%2s %lf %lf %8s %s", com, &x, &y, cor, sfx);
        p(x, y, cor, sfx, listaFormas, listaAnteparos, txt, svg, dirSaida, nomeGeo, tipoSort, limite);
    } else if (strcmp(comando, "cln") == 0){
        sscanf(linha, "%4s %lf %lf %lf %lf %s", com, &x, &y, &dx, &dy, sfx);
        cln(x, y, dx, dy, sfx, listaFormas, listaAnteparos, txt, svg, dirSaida, nomeGeo, tipoSort, limite);
    }
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, lista listaFormas, lista listaAnteparos, char* dirSaida, char* nomeGeo, char tipoSort, int limite){
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
        processarLinhaComandos(linha, comando, listaFormas, listaAnteparos, txt, svg, dirSaida, nomeGeo, tipoSort, limite);
    }
}