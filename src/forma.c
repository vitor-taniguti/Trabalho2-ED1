#include "forma.h"

int getIdForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getIdRetangulo(f);
            break;
        case 2:
            return getIdCirculo(f);
            break;
        case 3:
            return getIdLinha(f);
            break;
        case 4:
            return getIdTexto(f);
            break;
    }
}

double getXForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getXRetangulo(f);
            break;
        case 2:
            return getXCirculo(f);
            break;
        case 3:
            return fmin(getX1Linha(f), getX2Linha(f));
            break;
        case 4:
            return getXtTexto(f);
            break;
    }
}

double getYForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getYRetangulo(f);
            break;
        case 2:
            return getYCirculo(f);
            break;
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
            break;
        case 4:
            return getYtTexto(f);
            break;
    }
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