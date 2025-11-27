#include "geometria.h"

#define pi 3.14159265358979323846

double calcularDistancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(y2-y1, 2)+pow(x2-x1, 2));
}

double normalizarAngulo(double angulo){
    if (angulo < 0) return angulo + 2 * pi;
    return angulo;
}

vertice calcularInterseccao(double bx, double by, double angulo, anteparo a){
    double x1 = getX1Anteparo(a);
    double y1 = getY1Anteparo(a);
    double x2 = getX2Anteparo(a);
    double y2 = getY2Anteparo(a); 
    double dx_raio = cos(angulo);
    double dy_raio = sin(angulo);
    double dx_seg = x2 - x1;
    double dy_seg = y2 - y1;
    double det = dx_raio * dy_seg - dy_raio * dx_seg;
    if (fabs(det) < 1e-10){ 
        vertice v = criarVertice();
        setXVertice(v, x1);
        setYVertice(v, y1);
        return v; 
    }
    double t = ((x1 - bx) * dy_seg - (y1 - by) * dx_seg) / det;
    vertice v = criarVertice();
    setXVertice(v, bx + (dx_raio * t));
    setYVertice(v, by + (dy_raio * t));
    return v;
}