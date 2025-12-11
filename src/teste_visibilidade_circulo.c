#include "poligono.h"
#include "svg.h"
#include "anteparos.h"

int main(){
    lista formas = criarLista();
    lista anteparos = criarLista();
    circulo c = criarCirculo(1, 100.0, 100.0, 25.0, "#000000", "#FFFFFF");
    inserirLista(formas, c, 2);
    inserirLista(anteparos, transformarCirculo(c, 'v'), 5);
    poligono visibilidade = criarPoligono(); 
    lista atingidos = criarLista();
    arquivo svg;
    abrirArquivoSvg(&svg, "teste_visibilidade_circulo.svg");
    inicializarSVG(svg);
    calcularPoligono(visibilidade, anteparos, atingidos, 50.0, 100.0, 'm', 10);
    inserirPoligonoSVG(svg, visibilidade, "gray", "black");
    circulo bomba = criarCirculo(2, 50.0, 100.0, 5.0, "black", "red");
    inserirCirculoSVG(svg, bomba);
    liberarCirculo(bomba);
    liberarPoligono(visibilidade);
    liberarLista(formas);
    liberarLista(anteparos);
    liberarApenasNosLista(atingidos);
    fecharSVG(svg);
    fclose(svg);
}