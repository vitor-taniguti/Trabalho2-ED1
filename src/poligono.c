#include "poligono.h"
#include <math.h>

double calcularDistancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(y2-y1, 2)+pow(x2-x1, 2));
}

int compararDistanciaAnteparos(double x1, double y1, double x2, double y2, anteparo a1, anteparo a2){
    
}