#include "QuickSort.h"

int partition(void **elems, int ini, int max, int (*delta_f)(void*, void*), void (*swap)(void*, void*)) {
    void *pivot = elems[max];
    int base = ini - 1;

    for (int i = ini; i < max; ++i) {
        if (delta_f(elems[i], pivot) < 0) {
            ++base;
            swap(elems[base], elems[i]);
        }
    }
    ++base;
    swap(elems[base], elems[max]);
    return base;
}

void quickSort(void **elems, int ini, int max, int (*delta_f)(void*, void*), void (*swap)(void*, void*)) {
    if (ini >= max) return;

    int partInd = partition(elems, ini, max, delta_f, swap);
    quickSort(elems, ini, partInd - 1, delta_f, swap);
    quickSort(elems, partInd + 1, max, delta_f, swap);
}
