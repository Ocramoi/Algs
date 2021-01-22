#ifndef __INSERTIONSORT_H_
#define __INSERTIONSORT_H_

// Insertion sort para tipos genéricos
void insertionSort(void **elems, int ini, int fim, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*));

#endif // __INSERTIONSORT_H_
