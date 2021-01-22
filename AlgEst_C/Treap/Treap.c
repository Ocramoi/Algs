#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Treap.h"

// Inicializa nova treap
Treap *criaTreap(int (*comparador)(void*, void*), void (*exibicao)(void*)) {
    srand(time(NULL)); // Inicializa nova semente randômica para treap
    Treap *arv = malloc(sizeof(Treap)); // Aloca memória para estrutura da treap
    arv->raiz = NULL;
    arv->comparador = comparador;
    arv->exibicao = exibicao;
    return arv;
}

// Confere se treap em questão está vazia
int vaziaTreap(Treap *arv) {
    if (!arv) return -1; // Confere se treap existe
    return !(arv->raiz); // Confere se vazia
}

// Libera memória de nó recursivamente ao seus filhos
void finalizaNo(no *raiz) {
    if (!raiz) return;
    
    finalizaNo(raiz->esq);
    finalizaNo(raiz->dir);
    free(raiz->val);
    free(raiz);
}

// Libera memória referente a treap
int finalizaTreap(Treap *arv) {
    if (!arv) return -1; // Confere se árvore existe
    if(!arv->raiz) return 1; // Confere se há nós
    finalizaNo(arv->raiz); // Finaliza nós recursivamente a partir da raíz
    free(arv); // Libera estrutura da árvore
    return 0;
}

// Rotação de nós à direita
no *rotacaoDireitaSimples(no *des) {
    no *aux = des->esq; // Nó a "subir"
    des->esq = aux->dir; // "Sobe" filhos inferiores
    aux->dir = des; // Reposiciona raíz movida
    return aux;
}

// Rotação de nós à esquerda
no *rotacaoEsquerdaSimples(no *des) {
    no *aux = des->dir; // Nó a "subir"
    des->dir = aux->esq; // "Sobe" filhos inferiores
    aux->esq = des; // Reposiciona raíz movida
    return aux;
}

// Insere nó a partir de pai
no *insereNo(no *raiz, char *val, int prior, Comparador_f comparador) {
    if (!raiz) { // Se espaço vazio, insere
        raiz = malloc(sizeof(no)); // Aloca nó
        // Inicializa informações
        raiz->val = val;
        raiz->esq = raiz->dir = NULL;
        raiz->prior = prior;
    }
    else {
        if (comparador(val, raiz->val) < 0) { // Se valor menor que nó atual, adiciona a esquerda recursivamente
            raiz->esq = insereNo(raiz->esq, val, prior, comparador);
            if (raiz->esq && raiz->esq->prior < raiz->prior)
                raiz = rotacaoDireitaSimples(raiz); // Rotaciona em relação à prioridade, se necessário
        }
        else { // Se valor maior que nó atual, adiciona a direita recursivamente
            raiz->dir = insereNo(raiz->dir, val, prior, comparador);
            if (raiz->dir && raiz->dir->prior < raiz->prior)
                raiz = rotacaoEsquerdaSimples(raiz); // Rotaciona em relação à prioridade, se necessário
        }
    }
    return raiz;
}

// Insere elemento à treap
int insereTreap(Treap *arv, void *val) {
    if (!arv) return -1; // Confere se árvore existe
    
    if (buscaTreap(arv, val)) return 1; // Confere se elemento não já presente
    arv->raiz = insereNo(arv->raiz, val, rand(), arv->comparador); // Insere nó e atualiza raíz
    return 0;
}

// Busca nó recursivamente em função de seu valor
no *buscaNo(no *raiz, void *val, Comparador_f comparador) {
    if (!raiz) return NULL; // Confere fim da árvore

    int comp = comparador(val, raiz->val); // Compara valores do nó atual e valor buscado
    if (!comp)
        return raiz; // Caso achado, retorna nó
    // Caso contrário, continua busca na direção correta, recursivamente
    if (comp < 0)
        return buscaNo(raiz->esq, val, comparador);
    else
        return buscaNo(raiz->dir, val, comparador);
}

// Busca valor na treap
no *buscaTreap(Treap *arv, void *val) {
    if (!arv || vaziaTreap(arv)) return NULL; // Confere se árvore existe e possui elementos
    return buscaNo(arv->raiz, val, arv->comparador); // Busca a partir da raíz
}

no *removeNoTreap(no *raiz, void *val, Comparador_f comparador) {
    if(!raiz) return NULL;

    int comp = comparador(val, raiz->val);
    if (comp < 0) raiz->esq = removeNoTreap(raiz->esq, val, comparador);
    else if (comp > 0) raiz->dir = removeNoTreap(raiz->dir, val, comparador);
    else {
        if (!raiz->esq || !raiz->dir) {
            no *temp;
            if (raiz->dir) temp = raiz->dir;
            else temp = raiz->esq;
            free(raiz);
            raiz = temp;
        }
        else {
            if (raiz->esq->prior < raiz->prior) {
                raiz = rotacaoDireitaSimples(raiz);
                raiz->dir = removeNoTreap(raiz->dir, val, comparador);
            }
            else {
                raiz = rotacaoEsquerdaSimples(raiz);
                raiz->esq = removeNoTreap(raiz->esq, val, comparador);
            }
        }
    }

    return raiz;
}

// Remove elemento da treap
int removeTreap(Treap *arv, void *val) {
    if (!arv || vaziaTreap(arv)) return 1;
    arv->raiz = removeNoTreap(arv->raiz, val, arv->comparador);
    return 0;
}

void preOrdemNo(no *raiz, Exibicao_f exibicao) {
    if (!raiz) return;
    // Exibe filhos em ordem
    exibicao(raiz->val); // Exibe valor do nó
    preOrdemNo(raiz->esq, exibicao);
    preOrdemNo(raiz->dir, exibicao);
}

// Exibe elementos em pós ordem
void preOrdemTreap(Treap *arv) {
    if (!arv || vaziaTreap(arv)) return;
    preOrdemNo(arv->raiz, arv->exibicao);
}

void emOrdemNo(no *raiz, Exibicao_f exibicao) {
    if (!raiz) return;
    // Exibe filhos em ordem
    emOrdemNo(raiz->esq, exibicao);
    exibicao(raiz->val); // Exibe valor do nó
    emOrdemNo(raiz->dir, exibicao);
}

// Exibe elementos em pós ordem
void emOrdemTreap(Treap *arv) {
    if (!arv || vaziaTreap(arv)) return;
    emOrdemNo(arv->raiz, arv->exibicao);
}

void posOrdemNo(no *raiz, Exibicao_f exibicao) {
    if (!raiz) return;
    // Exibe filhos em ordem
    posOrdemNo(raiz->esq, exibicao);
    posOrdemNo(raiz->dir, exibicao);
    exibicao(raiz->val); // Exibe valor do nó
}

// Exibe elementos em pós ordem
void posOrdemTreap(Treap *arv) {
    if (!arv || vaziaTreap(arv)) return;
    posOrdemNo(arv->raiz, arv->exibicao);
}

// Imprime nó recursivamente com seu valor e prioridade
void imprimeNoTreap(no *raiz, Exibicao_f exibicao) {
    if (raiz) { // Se nó existe
        exibicao(raiz->val); // Exibe seu valor
        imprimeNoTreap(raiz->esq, exibicao);
        printf(", ");
        imprimeNoTreap(raiz->dir, exibicao);
        printf(")");
    }
    else
        printf("nil"); // Caso nó inexistente
}

// Imprime estrutura de nós da treap
void imprimeTreap(Treap *arv) {
    if (!arv || !arv->raiz) return;
    imprimeNoTreap(arv->raiz, arv->exibicao);
}
