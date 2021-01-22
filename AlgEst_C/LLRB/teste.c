#include <stdio.h>
#include <stdlib.h>

#include "LLRB.h"

int comparador(void *a, void *b) {
    return *((int*) a) - *((int*) b);
}

void exibe(void *val) {
    printf("%d ", *((int*) val));
}

int main(void) {
    LLRB *teste = criaLLRB(&comparador, &exibe);
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int *ins = malloc(sizeof(int));
        scanf("%d", ins);
        insereLLRB(teste, ins);
    }

    emOrdemLRRB(teste);
    printf("\n");

    int b; scanf("%d", &b);
    no_llrb *temp = predecessorLLRB(teste, &b);
    exibe(temp->val);
    printf("\n");

    desalocaLLRB(teste);

    return 0;
}
