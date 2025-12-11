#include "poligono.h"
#include "svg.h"
#include "anteparos.h"

int main(){
    lista formas = criarLista();
    lista anteparos = criarLista();
    retangulo r = criarRetangulo(1, 50.0, 50.0, 100.0, 100.0, "#000000", "#FFFFFF");
    inserirLista(formas, r, 1);
    anteparo* antRet = transformarRetangulo(r);
    for (int i = 0; i < 4; i++){
        inserirLista(anteparos, antRet[i], 5);
    }
    poligono visibilidade = criarPoligono(); 
    lista atingidos = criarLista();
    arquivo svg;
    abrirArquivoSvg(&svg, "teste_visibilidade_retangulo.svg");
    inicializarSVG(svg);
    calcularPoligono(visibilidade, anteparos, atingidos, 10.0, 10.0, 'm', 10);
    inserirPoligonoSVG(svg, visibilidade, "gray", "black");
    circulo bomba = criarCirculo(2, 10.0, 10.0, 5.0, "black", "red");
    inserirCirculoSVG(svg, bomba);
    liberarCirculo(bomba);
    liberarPoligono(visibilidade);
    liberarLista(formas);
    liberarLista(anteparos);
    liberarApenasNosLista(atingidos);
    free(antRet);
    fecharSVG(svg);
    fclose(svg);
}