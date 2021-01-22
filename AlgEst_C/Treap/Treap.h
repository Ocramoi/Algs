#ifndef _TREAP_H
#define _TREAP_H

typedef int (*Comparador_f)(void*, void*);
typedef void (*Exibicao_f)(void*);

typedef struct no_t no;
struct no_t {
    void *val;
    unsigned int prior;
    no *esq, *dir;
}; // Estrutura de nó da treap

typedef struct {
    no *raiz; // Raíz da árvore
    Comparador_f comparador; // Função de comparação para tipo genérico
    Exibicao_f exibicao; // Função de exibição de tipo genérico
} Treap; // Estrutura da treap

// Inicializa nova treap
Treap *criaTreap(int (*comparador)(void*, void*), void (*exibicao)(void*));
// Confere se treap em questão está vazia
int vaziaTreap(Treap *arv);
// Libera memória referente a treap
int finalizaTreap(Treap *arv);
// Insere elemento à treap
int insereTreap(Treap *arv, void *val);
// Busca valor na treap
no *buscaTreap(Treap *arv, void *val);
// Remove elemento da treap
int removeTreap(Treap *arv, void *val);

// Imprime estrutura de nós da treap
void imprimeTreap(Treap *arv);
// Imprime treap em ordem nível a nível
void preOrdemTreap(Treap *arv);
// Exibe elementos da treap em ordem
void emOrdemTreap(Treap *arv);
// Exibe elementos em pós ordem
void posOrdemTreap(Treap *arv);

#endif
