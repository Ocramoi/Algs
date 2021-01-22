#include <stdlib.h>
#include <limits.h>

#include "BucketSort.h"

// Nó para de lista (bucket)
typedef struct no_bucket_t no_bucket;
struct no_bucket_t {
    void *val;
    no_bucket *prox;
};

// Lista encadeada (bucket)
typedef struct {
    no_bucket *ini,
              *fim;
} Bucket;

// Bucket sort para tipos genéricos
void bucketSort(void **elems, long long tam, long long (*Valor_el)(void*)) {
    long long min = LLONG_MAX, max = LLONG_MIN; // Inicializa extremos do vetor
    for (long long i = 0; i < tam; ++i) { // Lê maior e menor valores
        if (Valor_el(elems[i]) < min)
            min = Valor_el(elems[i]);
        if (Valor_el(elems[i]) > max)
            max = Valor_el(elems[i]);
    }

    long long nBuckets = max - min + 1; // Número de buckets (npumero de chaves diferentes)
    Bucket *buckets = malloc(nBuckets*sizeof(Bucket)); // Aloca listas necessárias
    for (int i = 0; i < nBuckets; ++i) { // Inicializa listas
        buckets[i].ini = NULL;
        buckets[i].fim = NULL;
    }

    for (long long i = 0; i < tam; ++i) { // Percorre elementos da lista
        no_bucket *novo = malloc(sizeof(no_bucket)); // Aloca novo nó
        novo->val = elems[i];
        novo->prox = NULL;

        long long nLista = Valor_el(elems[i]) - min; // Índice da lista correta para adição
        if (!buckets[nLista].ini) // Trata lista vazia
            buckets[nLista].ini = novo;
        else // Caso lista cheia atualiza referência do último elemento
            buckets[nLista].fim->prox = novo;
        buckets[nLista].fim = novo; // Atualiza fim de lista
    }

    long long i = -1; // Variável auxiliar de elemento final da lista ordenada
    for (long long j = 0; j < nBuckets; ++j) { // Percorre "buckets"
        no_bucket *temp = buckets[j].ini; // Início do "bucket" atual
        while (temp) { // Percorre lista
            no_bucket *aux = temp; // Variável auxiliar para exclusão do elemento
            elems[++i] = temp->val; // Adiciona elemento
            temp = temp->prox; // Atualiza elemento
            free(aux); // Libera memória do nó
        }
    }
    free(buckets); // Libera memória das listas
}
