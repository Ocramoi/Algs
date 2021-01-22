#include "InsertionSort.h"

// Insertion sort para tipos genéricos
void insertionSort(void **elems, int ini, int fim, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*)) {
    for (int i = ini + 1; i <= fim; ++i) { // Loop entre elementos
        void *temp = elems[i]; // Elemento atual
        int j = i - 1; // Inicializa índice para loop entre elementos anteriores

        while (j >= ini && delta_f(elems[j], temp) > 0) { // Percorre lista de elementos anteriores procurando elemento maior que o atual
            elems[j + 1] = elems[j]; // Atualiza elemento da lista
            --j; // Atualiza índice
        }
        elems[j + 1] = temp; // Trata final da lista percorrida
    }
}
