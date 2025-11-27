#include "sort.h"

void insertionSort(void *base, int n, size_t tamanho, int (*compar)(const void *, const void *)) {
    char *arr = (char *)base;
    char *temp = (char *)malloc(tamanho);
    for (int i = 1; i < n; i++) {
        memcpy(temp, arr + i * tamanho, tamanho);
        int j = i - 1;
        while (j >= 0 && compar(arr + j * tamanho, temp) > 0) {
            memcpy(arr + (j + 1) * tamanho, arr + j * tamanho, tamanho);
            j--;
        }
        memcpy(arr + (j + 1) * tamanho, temp, tamanho);
    }
    free(temp);
}

void merge(void *base, int esq, int meio, int dir, size_t tamanho, int (*compar)(const void *, const void *)) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    char* L = (char*) malloc(n1 * tamanho);
    char* R = (char*) malloc(n2 * tamanho);
    memcpy(L, (char*) base + esq * tamanho, n1 * tamanho);
    memcpy(R, (char*) base + (meio + 1) * tamanho, n2 * tamanho);
    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2){
        if (compar(L + i * tamanho, R + j * tamanho) <= 0) {
            memcpy((char *)base + k * tamanho, L + i * tamanho, tamanho);
            i++;
        } else{
            memcpy((char *)base + k * tamanho, R + j * tamanho, tamanho);
            j++;
        }
        k++;
    }
    while (i < n1){
        memcpy((char *)base + k * tamanho, L + i * tamanho, tamanho);
        i++; k++;
    }
    while (j < n2){
        memcpy((char *)base + k * tamanho, R + j * tamanho, tamanho);
        j++; k++;
    }
    free(L);
    free(R);
}

void mergeSortRecursivo(void *base, int esq, int dir, size_t tamanho, int (*compar)(const void *, const void *), int limiteInsertion) {
    if (esq < dir){
        if ((dir - esq + 1) <= limiteInsertion) {
            insertionSort((char *)base + esq * tamanho, dir - esq + 1, tamanho, compar);
        } else {
            int meio = esq + (dir - esq) / 2;
            mergeSortRecursivo(base, esq, meio, tamanho, compar, limiteInsertion);
            mergeSortRecursivo(base, meio + 1, dir, tamanho, compar, limiteInsertion);
            merge(base, esq, meio, dir, tamanho, compar);
        }
    }
}

void msort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int limite){
    if (nmemb > 0) mergeSortRecursivo(base, 0, nmemb - 1, size, compar, limite);
}