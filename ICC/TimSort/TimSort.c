#include "TimSort.h"
#include "InsertionSort.h"

#include <stdlib.h>

void merge(void **elems, int ini, int mid, int fim, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*)) {
    int tamEsq = mid - ini + 1,
        tamDir = fim - mid;
    void **esq = malloc(tamEsq*sizeof(void*)),
         **dir = malloc(tamDir*sizeof(void*));
    for (int i = 0; i < tamEsq; ++i)
        esq[i] = elems[ini + i];
    for (int i = 0; i < tamDir; ++i)
        dir[i] = elems[mid + i + 1];

    int i = 0,
        j = 0,
        k = ini;
    while (i < tamEsq && j < tamDir) {
        if (delta_f(esq[i], dir[j]) <= 0) {
            elems[k] = esq[i];
            ++i;
        }
        else {
            elems[k] = dir[j];
            ++j;
        }
        ++k;
    }

    while (i < tamEsq) {
        elems[k] = esq[i];
        ++k; ++i;
    }
    while (j < tamDir) {
        elems[k] = dir[j];
        ++k; ++j;
    }
}

// TimSort para tipos genéricos
void timSort(void **elems, int tam, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*)) {
    for (int i = 0; i < tam; i += RUN)
        insertionSort(elems, i, ((i + 31) < (tam - 1) ? (i + 31) : (tam - 1)), delta_f, swap_f);

    for (int i = RUN; i < tam; i *= 2) {
        for (int esq = 0; esq < tam; esq += 2*i) {
            int mid = esq + i - 1;
            int dir = ((esq + 2*i - 1) < (tam - 1)) ? (esq + 2*i - 1) : (tam - 1);
            merge(elems, esq, mid, dir, delta_f, swap_f);
        }
    }
}
