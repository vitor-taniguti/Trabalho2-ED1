#include "poligono.h"
#include "svg.h"
#include "anteparos.h"

int main(){
    lista formas = criarLista();
    lista anteparos = criarLista();
    retangulo r = criarRetangulo(1, 0.0, 0.0, 200.0, 200.0, "#000000", "#FFFFFF");
    circulo c = criarCirculo(2, 100.0, 100.0, 25.0, "#000000", "#FFFFFF");
    inserirLista(formas, r, 1);
    inserirLista(formas, c, 2);
    anteparo* antRet = transformarRetangulo(r);
    for (int i = 0; i < 4; i++){
        inserirLista(anteparos, antRet[i], 5);
    }
    inserirLista(anteparos, transformarCirculo(c, 'v'), 5);
    poligono visibilidade = criarPoligono(); 
    lista atingidos = criarLista();
    arquivo svg;
    abrirArquivoSvg(&svg, "teste_visibilidade.svg");
    inicializarSVG(svg);
    calcularPoligono(visibilidade, anteparos, atingidos, 50.0, 100.0, 'm', 10);
    inserirPoligonoSVG(svg, visibilidade, "gray", "black");
    circulo bomba = criarCirculo(3, 50.0, 100.0, 5.0, "black", "red");
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