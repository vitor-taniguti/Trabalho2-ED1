#include "colisao.h"
#include "forma.h"
#include <math.h>
#include <stdlib.h>

double distanciaPontoSegmento(double px, double py, double x1, double y1, double x2, double y2){
    double l2 = calcularDistancia(x1, y1, x2, y2);
    if (l2 == 0) return calcularDistancia(px, py, x1, y1);
    double t = ((px - x1) * (x2 - x1) + (py - y1) * (y2 - y1)) / l2;
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    double projX = x1 + t * (x2 - x1);
    double projY = y1 + t * (y2 - y1);
    return calcularDistancia(px, py, projX, projY);
}

int detectarInterseccao(double ax, double ay, double bx, double by, double cx, double cy){
    double val = (by - ay) * (cx - bx) - (bx - ax) * (cy - by);
    if (fabs(val) < 1e-9) return 0; 
    return (val > 0) ? 1 : 2;
}

int segmentosIntersectam(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy){
    int o1 = detectarInterseccao(ax, ay, bx, by, cx, cy);
    int o2 = detectarInterseccao(ax, ay, bx, by, dx, dy);
    int o3 = detectarInterseccao(cx, cy, dx, dy, ax, ay);
    int o4 = detectarInterseccao(cx, cy, dx, dy, bx, by);
    if (o1 != o2 && o3 != o4) return 1;
    return 0;
}

int pontoDentroPoligono(poligono p, double x, double y) {
    int i, j, dentro = 0;
    int n = getTotalVerticesPoligono(p);
    for (i = 0, j = n - 1; i < n; j = i++){
        double xi, yi, xj, yj;
        getVerticePoligono(p, i, &xi, &yi);
        getVerticePoligono(p, j, &xj, &yj);
        if (((yi > y) != (yj > y)) && (x < (xj - xi) * (y - yi) / (yj - yi) + xi)) dentro = !dentro;
    }
    return dentro;
}

int colidePoligonoRetangulo(poligono p, retangulo r){
    double rx = getXRetangulo(r);
    double ry = getYRetangulo(r);
    double w = getWRetangulo(r);
    double h = getHRetangulo(r);
    double pontosRetangulo[4][2] = {
        {rx, ry},         
        {rx + w, ry},     
        {rx + w, ry + h}, 
        {rx, ry + h}      
    };
    for (int i = 0; i < 4; i++){
        if (pontoDentroPoligono(p, pontosRetangulo[i][0], pontosRetangulo[i][1])) return 1;
    }
    int n = getTotalVerticesPoligono(p);
    for (int i = 0; i < n; i++){
        double x, y;
        getVerticePoligono(p, i, &x, &y);
        if (x >= rx && x <= rx + w && y >= ry && y <= ry + h) {
            return 1;
        }
    }
    for (int i = 0; i < n; i++){
        double x1, y1, x2, y2;
        getVerticePoligono(p, i, &x1, &y1);
        getVerticePoligono(p, (i + 1) % n, &x2, &y2);
        for (int j = 0; j < 4; j++){
            double rx1 = pontosRetangulo[j][0];
            double ry1 = pontosRetangulo[j][1];
            double rx2 = pontosRetangulo[(j+1)%4][0];
            double ry2 = pontosRetangulo[(j+1)%4][1];
            if (segmentosIntersectam(x1, y1, x2, y2, rx1, ry1, rx2, ry2)){
                return 1;
            }
        }
    }
    return 0;
}

int colidePoligonoCirculo(poligono p, circulo c){
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double r = getRCirculo(c);
    if (pontoDentroPoligono(p, cx, cy)) return 1;
    int n = getTotalVerticesPoligono(p);
    for (int i = 0; i < n; i++){
        double x1, y1, x2, y2;
        getVerticePoligono(p, i, &x1, &y1);
        getVerticePoligono(p, (i + 1) % n, &x2, &y2);
        if (distanciaPontoSegmento(cx, cy, x1, y1, x2, y2) <= r) return 1;
        if (calcularDistancia(x1, y1, cx, cy) <= r) return 1;
    }
    return 0;
}

int colidePoligonoSegmento(poligono p, void* f, int tipoForma){
    double x1, y1, x2, y2;
    if (tipoForma == 3){
        x1 = getX1Linha(f);
        y1 = getY1Linha(f);
        x2 = getX2Linha(f);
        y2 = getY2Linha(f);
    } else{
        x1 = getX1Texto(f);
        y1 = getYtTexto(f);
        x2 = getX2Texto(f);
        y2 = getYtTexto(f);
    }
    if (pontoDentroPoligono(p, x1, y1)) return 1;
    if (pontoDentroPoligono(p, x2, y2)) return 1;
    int n = getTotalVerticesPoligono(p);
    for (int i = 0; i < n; i++){
        double px1, py1, px2, py2;
        getVerticePoligono(p, i, &px1, &py1);
        getVerticePoligono(p, (i + 1) % n, &px2, &py2);
        if (segmentosIntersectam(x1, y1, x2, y2, px1, py1, px2, py2)) return 1;
    }
    return 0;
}

int relamBoundingBox(double pMinX, double pMinY, double pMaxX, double pMaxY, double fMinX, double fMinY, double fMaxX, double fMaxY){
    if (pMinX > fMaxX || fMinX > pMaxX || pMinY > fMaxY || fMinY > pMaxY) return 0;
    return 1;
}

void obterAlvosAtingidos(poligono p, lista atingidos, lista alvos){
    double pMinX, pMinY, pMaxX, pMaxY;
    getBoundingBoxPoligono(p, &pMinX, &pMinY, &pMaxX, &pMaxY);
    iterador i = getPrimeiroLista(alvos);
    while (i != NULL){
        forma forma = getFormaLista(i); 
        int tipoForma = getTipoFormaLista(i);
        double fMinX, fMinY, fMaxX, fMaxY;
        getBoundingBoxForma(forma, tipoForma, &fMinX, &fMinY, &fMaxX, &fMaxY);
        if (relamBoundingBox(pMinX, pMinY, pMaxX, pMaxY, fMinX, fMinY, fMaxX, fMaxY)) {
            int atingiu = 0;
            switch (tipoForma){
                case 1:
                    atingiu = colidePoligonoRetangulo(p, forma);
                    break;
                case 2: 
                    atingiu = colidePoligonoCirculo(p, forma);
                    break;
                case 3:
                    atingiu = colidePoligonoSegmento(p, forma, tipoForma);
                    break;
                case 4:
                    atingiu = colidePoligonoSegmento(p, forma, tipoForma);
                    break;
            }
            if (atingiu) inserirLista(atingidos, forma, tipoForma);
        }
        i = getProximoLista(i);
    }
}