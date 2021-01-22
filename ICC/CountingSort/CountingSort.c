#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "CountingSort.h"

// Counting sort para tipos genéricos
void countingSort(void **elems, int tam, long long (*Valor_el)(void*)) {
    long long min = LLONG_MAX, max = LLONG_MIN; // Inicializa extremos do vetor
    for (int i = 0; i < tam; ++i) { // Lê maior e menor valores
        if (Valor_el(elems[i]) < min)
            min = Valor_el(elems[i]);
        if (Valor_el(elems[i]) > max)
            max = Valor_el(elems[i]);
    }

    long long *qnts = calloc((max - min + 1), sizeof(long long)); // Vetor de quantidades de cada valor dentro do alcance da lista

    for (int i = 0; i < tam; ++i)
        qnts[Valor_el(elems[i]) - min]++; // Lê quantidade de valores

    // Transforma vetor de quantidade em vetor de posição
    long long count = 0;
    for (int i = 0; i < (max - min + 1); ++i) {
        long long temp = qnts[i];
        qnts[i] = count;
        count += temp;
    }

    void **ret = malloc(tam*sizeof(void*)); // Vetor de retorno com posições corretas
    for (int i = 0; i < tam; ++i) { // Posiciona elementos nas posições corretas do vetor de retorno
        void *temp = elems[i];
        ret[qnts[Valor_el(temp) - min]] = temp;
        qnts[Valor_el(temp) - min]++;
    }

    for (int i = 0; i < tam; ++i) elems[i] = ret[i]; // Copia vetor de retorno para o vetor original

    free(qnts); free(ret); // Libera memória auxiliar
}
