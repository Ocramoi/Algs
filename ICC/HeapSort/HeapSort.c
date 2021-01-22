#include "HeapSort.h"

// Ordena recursivamente sub árvore a partir de idx em max heap
void heapify(void **elems, int tam, int idx, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*)) {
    int max = idx, // Assume elems[idx] como maior elemento entre filhos
        // Calcula índices de filhos
        esq = 2*idx + 1,
        dir = 2*idx + 2;

    // Procura elemento maior que idx entre seus filhos que existem
    if (esq < tam && delta_f(elems[esq], elems[max]) > 0)
        max = esq;
    if (dir < tam && delta_f(elems[dir], elems[max]) > 0)
        max = dir;

    if (max == idx) return; // Caso pai já seja maior elemento entre filhos, retorna
    // Caso contrário, "sobre" filho maior e ordena sub árvore alterada
    swap_f(elems[idx], elems[max]);
    heapify(elems, tam, max, delta_f, swap_f);
}

// Heap sort para lista de tipo genérico
void heapSort(void **elems, int tam, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*)) {
    for (int i = tam/2 - 1; i >= 0; --i)
        heapify(elems, tam, i, delta_f, swap_f); // Ordena sub ávores a partir de folhas
    // "Carrega" maiores elementos ordenados para fim da lista e reorderna sub árvores
    int temp = tam - 1;
    while (temp) {
        swap_f(elems[0], elems[temp]);
        heapify(elems, temp, 0, delta_f, swap_f);
        --temp;
    }
}
