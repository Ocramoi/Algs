#include <stdio.h>
#include "QuickSort.h"

#define NUM 15

int comparador (void *a, void *b) {
    return *((int*) a) - *((int*) b);
}

void swap (void *a, void *b) {
    int temp = *((int*) a);
    *((int*) a) = *((int*) b);
    *((int*) b) = temp;
}

int main(void) {
    int **vals = malloc(NUM*sizeof(int*));
    for (int i = 0; i < NUM; ++i) {
        int *temp = malloc(sizeof(int));
        *temp = NUM - i;
        vals[i] = temp;
    }
    for (int i = 0; i < NUM; ++i)
        printf("%d\n", *((int*)vals[i]));
    quickSort((void**) vals, 0, NUM - 1, &comparador, &swap);
    printf("------------------------\n");
    for (int i = 0; i < NUM; ++i) {
        printf("%d\n", *((int*)vals[i]));
        free(vals[i]);
    } free(vals);
    return 0;
}
