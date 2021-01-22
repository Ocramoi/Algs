#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <stdlib.h>

void quickSort(void **elems, int ini, int max, int (*delta_f)(void*, void*), void (*swap)(void*, void*));

#endif
