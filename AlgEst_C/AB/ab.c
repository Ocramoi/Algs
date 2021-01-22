#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ab.h"

arvore *cria() {
    arvore *ar = malloc(sizeof(arvore));
    ar->raiz = NULL;
    return ar;
}

int esta_vazia(arvore *ar) {
    assert(ar != NULL);
    return !ar->raiz;
}

void finaliza(no *raiz) {
    if (!raiz) return;
    
    finaliza(raiz->esq);
    finaliza(raiz->dir);
    free(raiz);
}

void imprime(no *raiz) {
    if (raiz) {
        printf("%d(", raiz->val);
        imprime(raiz->esq);
        printf(", ");
        imprime(raiz->dir);
        printf(")");
    }
    else
        printf("nil");
}

int altura(no *raiz, int tam) {
    if (!raiz) return tam;

    int altEsq = altura(raiz->esq, tam + 1),
        altDir = altura(raiz->dir, tam + 1);
    
    return (altDir > altEsq) ? altDir : altEsq;
}

no *busca(no *raiz, int x) {
    if (!raiz) return NULL;
    if (raiz->val == x) return raiz;

    no *p = busca(raiz->dir, x);
    if (p) return p;

    return busca(raiz->esq, x);
}

no *buscaPai(no *raiz, int x) {
    if (!raiz) return NULL;

    if (raiz->esq && raiz->esq->val == x)
        return raiz;
    if (raiz->dir && raiz->dir->val == x)
        return raiz;

    no *p = buscaPai(raiz->dir, x);
    if (p) return p;

    return buscaPai(raiz->esq, x);
}

int inserirEsq(arvore *ar, int x, int pai) {
    no *novo = malloc(sizeof(no));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->val = x;

    if (pai == -1) {
        if (!ar->raiz)
            ar->raiz = novo;
        else {
            free(novo);
            return 0;
        }
    }
    else {
        no *noPai = busca(ar->raiz, pai);
        if (noPai && noPai->esq == NULL)
            noPai->esq = novo;
        else {
            free(novo);
            return 0;
        }
    }
    return 1;
}

int inserirDir(arvore *ar, int x, int pai) {
    no *novo = malloc(sizeof(no));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->val = x;

    if (pai == -1) {
        if (!ar->raiz)
            ar->raiz = novo;
        else {
            free(novo);
            return 0;
        }
    }
    else {
        no *noPai = busca(ar->raiz, pai);
        if (noPai && noPai->dir == NULL)
            noPai->dir = novo;
        else {
            free(novo);
            return 0;
        }
    }
    return 1;
}

int remover(arvore *ar, int x) {
    no *p, *pai;
    char dir = 0;
    if (ar->raiz != NULL && ar->raiz->val == x) {
        p = ar->raiz;
        pai = NULL;
    }
    else {
        pai = buscaPai(ar->raiz, x);
        if (pai != NULL) {
            if (pai->esq && pai->esq->val == x) {
                p = pai->esq;
            }
            else {
                p = pai->dir;
                dir = 1;
            }
        }
        else
            p = NULL;
    }

    if (p == NULL) return 0;

    if (p->esq == NULL && p->dir == NULL) {
        if (pai == NULL) {
            free(p);
            ar->raiz = NULL;
        }
        else {
            if (dir) pai->dir = NULL;
            else pai->esq = NULL;

            free(p);
            
            return 1;
        }
    }
    else {
        if (p->esq) {
            p->val = p->esq->val;
            p->esq->val = x;
        }
        else {
            p->val = p->dir->val;
            p->dir->val = x;
        }
        return remover(ar, x);
    }

    return 0;
}

void preOrdem(no *raiz) {
    if (raiz) {
        printf("%d ", raiz->val);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void emOrdem(no *raiz) {
    if (raiz) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->val);
        emOrdem(raiz->dir);
    }
}

void posOrdem(no *raiz) {
    if (raiz) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->val);
    }
}