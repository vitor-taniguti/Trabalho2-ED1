#include "poligono.h"
#include "svg.h"
#include "anteparos.h"

int main(){
    lista formas = criarLista();
    lista anteparos = criarLista();
    texto t = criarTexto(1, 20.0, 50.0, "#000000", "#FFFFFF", 'i', "FLAMENGOOOOOOOOOO");
    inserirLista(formas, t, 3);
    inserirLista(anteparos, transformarTexto(t), 5);
    poligono visibilidade = criarPoligono(); 
    lista atingidos = criarLista();
    arquivo svg;
    abrirArquivoSvg(&svg, "teste_visibilidade_texto.svg");
    inicializarSVG(svg);
    calcularPoligono(visibilidade, anteparos, atingidos, 100.0, 100.0, 'm', 10);
    inserirPoligonoSVG(svg, visibilidade, "gray", "black");
    circulo bomba = criarCirculo(2, 100.0, 100.0, 5.0, "black", "red");
    inserirCirculoSVG(svg, bomba);
    liberarCirculo(bomba);
    liberarPoligono(visibilidade);
    liberarLista(formas);
    liberarLista(anteparos);
    liberarApenasNosLista(atingidos);
    fecharSVG(svg);
    fclose(svg);
}