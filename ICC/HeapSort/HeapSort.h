#ifndef __HEAPSORT_H_
#define __HEAPSORT_H_

// Heap sort para lista de tipo genérico
void heapSort(void **elems, int tam, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*));

#endif // __HEAPSORT_H_
