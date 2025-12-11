#include "poligono.h"
#include "svg.h"
#include "anteparos.h"

int main(){
    lista formas = criarLista();
    lista anteparos = criarLista();
    linha l = criarLinha(1, 50.0, 10.0, 50.0, 90.0, "#000000");
    inserirLista(formas, l, 3);
    inserirLista(anteparos, transformarLinha(l), 5);
    poligono visibilidade = criarPoligono(); 
    lista atingidos = criarLista();
    arquivo svg;
    abrirArquivoSvg(&svg, "teste_visibilidade_linha.svg");
    inicializarSVG(svg);
    calcularPoligono(visibilidade, anteparos, atingidos, 25.0, 50.0, 'm', 10);
    inserirPoligonoSVG(svg, visibilidade, "gray", "black");
    circulo bomba = criarCirculo(2, 25.0, 50.0, 5.0, "black", "red");
    inserirCirculoSVG(svg, bomba);
    liberarCirculo(bomba);
    liberarPoligono(visibilidade);
    liberarLista(formas);
    liberarLista(anteparos);
    liberarApenasNosLista(atingidos);
    fecharSVG(svg);
    fclose(svg);
}