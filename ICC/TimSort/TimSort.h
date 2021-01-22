#ifndef __TIMSORT_H_
#define __TIMSORT_H_

#define RUN 32

// TimSort para tipos genéricos
void timSort(void **elems, int tam, int (*delta_f)(void*, void*), void (*swap_f)(void*, void*));

#endif // __TIMSORT_H_
