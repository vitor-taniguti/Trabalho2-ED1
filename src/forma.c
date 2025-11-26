#include "forma.h"
#include "lista.h"

int getIdForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getIdRetangulo(f);
        case 2:
            return getIdCirculo(f);
        case 3:
            return getIdLinha(f);
        case 4:
            return getIdTexto(f);
    }
    return 0;
}

double getXForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getXRetangulo(f);
        case 2:
            return getXCirculo(f);
        case 3:
            return fmin(getX1Linha(f), getX2Linha(f));
        case 4:
            return getXtTexto(f);
    }
    return 0.0;
}

double getYForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getYRetangulo(f);
        case 2:
            return getYCirculo(f);
        case 3:
            double x1 = getX1Linha(f);
            double y1 = getY1Linha(f);
            double x2 = getX2Linha(f);
            double y2 = getY2Linha(f);
            if (x1 < x2){
                return y1;
            } else if (x2 < x1){
                return y2;
            } else{
                return fmin(y1, y2);
            }
        case 4:
            return getYtTexto(f);
    }
    return 0.0;
}

void setCorBForma(forma f, int tipoForma, char* corB){
    switch (tipoForma){
        case 1:
            setCorBRetangulo(f, corB);
            break;
        case 2:
            setCorBCirculo(f, corB);
            break;
        case 3: 
            setCorLinha(f, corB);
            break;
        case 4:
            setCorBTexto(f, corB);
            break;
    }
}

void setCorPForma(forma f, int tipoForma, char* corP){
    switch (tipoForma){
        case 1:
            setCorPRetangulo(f, corP);
            break;
        case 2:
            setCorPCirculo(f, corP);
            break;
        case 3: 
            calcCorComplementarLinha(f);
            break;
        case 4:
            setCorBTexto(f, corP);
            break;
    }
}

double calcAreaForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return calcAreaRetangulo(f);
        case 2:
           return calcAreaCirculo(f);
        case 3:
            return calcAreaLinha(f);
        case 4:
            return calcAreaTexto(f);
    }
    return 0.0;
}

forma clonarForma(forma f, int tipoForma, lista listaFormas){
    forma formaNova;
    int id = getMaiorId(listaFormas) + 1;
    double x, y, w, h, r, x2, y2;
    char *corP, *corB, a, *txto;
    switch (tipoForma){
        case 1:
            x = getXRetangulo(f);
            y = getYRetangulo(f);
            w = getWRetangulo(f);
            h = getHRetangulo(f);
            corP = getCorPRetangulo(f);
            corB = getCorBRetangulo(f);
            formaNova = criarRetangulo(id, x, y, w, h, corB, corP);
            break;
        case 2:
            x = getXCirculo(f);
            y = getYCirculo(f);
            r = getRCirculo(f);
            corP = getCorPCirculo(f);
            corB = getCorBCirculo(f);
            formaNova = criarCirculo(id, x, y, r, corB, corP);
            break;
        case 3:
            x = getX1Linha(f);
            y = getY1Linha(f);
            x2 = getX2Linha(f);
            y2 = getY2Linha(f);
            corB = getCorLinha(f);
            formaNova = criarLinha(id, x, y, x2, y2, corB);
            break;
        case 4:
            x = getXtTexto(f);
            y = getYtTexto(f);
            a = getATexto(f);
            corP = getCorPTexto(f);
            corB = getCorBTexto(f);
            txto = getTxtoTexto(f);
            formaNova = criarTexto(id, x, y, corB, corP, a, txto);
            break;
    }
    return formaNova;
}

void calcularBoundingBoxForma(forma f, int tipoForma, double *x1, double *y1, double *x2, double *y2){
    switch (tipoForma){
        case 1:
            *x1 = getXRetangulo(f);
            *y1 = getYRetangulo(f);
            *x2 = *x1 + getWRetangulo(f);
            *y2 = *y1 + getHRetangulo(f);
            break;
        case 2:
        {
            double raio = getRCirculo(f);
            double x = getXCirculo(f);
            double y = getYCirculo(f);
            *x1 = x - raio;
            *y1 = y - raio;
            *x2 = x + raio;
            *y2 = y + raio;
            break;
        }
        case 3:
        {
            double xA = getX1Linha(f);
            double xB = getX2Linha(f);
            double yA = getY1Linha(f);
            double yB = getY2Linha(f);
            *x1 = fmin(xA, xB);
            *y1 = fmin(yA, yB);
            *x2 = fmax(xA, xB);
            *y2 = fmax(yA, yB);
            break;
        }
        case 4:
        {
            setX1X2Texto(f, getATexto(f)); 
            
            double xA = getX1Texto(f);
            double xB = getX2Texto(f);
            double yA = getYtTexto(f);
            double yB = getYtTexto(f);

            *x1 = fmin(xA, xB);
            *y1 = fmin(yA, yB);
            *x2 = fmax(xA, xB);
            *y2 = fmax(yA, yB);
            break;
        }
    }
}

void liberarForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            liberarRetangulo(f);
            break;
        case 2:
            liberarCirculo(f);
            break;
        case 3:
            liberarLinha(f);
            break;
        case 4:
            liberarTexto(f);
            break;
        case 5:
            liberarAnteparo(f);
            break;
    }
}