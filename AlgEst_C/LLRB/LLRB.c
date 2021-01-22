#include <stdlib.h>

#include "LLRB.h"

// Procede por filho mínimo de raíz, retornando menor valor
static no_llrb *minNoLLRB(no_llrb *raiz) {
    if (!raiz->esq) return raiz;
    return minNoLLRB(raiz->esq);
}

// Procede por filho máximo de raíz, retornando maior valor
static no_llrb *maxNoLLRB(no_llrb *raiz) {
    if (!raiz->dir) return raiz;
    return maxNoLLRB(raiz->dir);
}

// Rotação de nó simples a esquerda
static no_llrb *rotaEsq(no_llrb *raiz) {
    no_llrb *aux = raiz->dir; // Nó a "subir"
    raiz->dir = aux->esq; // "Sobe" filhos inferiores
    aux->esq = raiz; // Reposiciona raíz movida
    return aux;

}

// Rotação de nó simples a direita
static no_llrb *rotaDir(no_llrb *raiz) {
    no_llrb *aux = raiz->esq; // Nó a "subir"
    raiz->esq = aux->dir; // "Sobe" filhos inferiores
    aux->dir = raiz; // Reposiciona raíz movida
    return aux;
}

// Troca cores entre dois nós
static void trocaCores(no_llrb *a, no_llrb *b) {
    char temp = a->vermelho;
    a->vermelho = b->vermelho;
    b->vermelho = temp;
}

// Confere se nó existe e é vermelho
static char confVerm(no_llrb *raiz) {
    return (raiz && raiz->vermelho);
}

// Inicializa nova LLRB
LLRB *criaLLRB(int (*Comparador)(void*, void*), void (*Exibicao)(void*)) {
    LLRB *cria = malloc(sizeof(LLRB)); // Aloca nova LLRB
    cria->raiz = NULL; // Inicializa raíz nula
    // Adiciona métodos
    cria->comparador = Comparador;
    cria->exibicao = Exibicao;
    return cria;
}

// Confere de LLRB está vazia
int vaziaLLRB(LLRB *arv) {
    if (!arv) return -1; // Confere se árvore existe
    // Retorna se raíz está vazia
    if (!arv->raiz) return 1;
    return 0;
}

// Desaloca nós recursivamente
static void desalocaNoLLRB(no_llrb *raiz) {
    if (!raiz) return; // Confere existência do nó
    // Desaloca filhos recursivamente
    desalocaNoLLRB(raiz->esq);
    desalocaNoLLRB(raiz->dir);
    // Desaloca nó
    free(raiz->val);
    free(raiz);
}

// Desaloca árvore
int desalocaLLRB(LLRB *arv) {
    if (vaziaLLRB(arv)) return 1; // Confere se árvore existe e é não vazia
    desalocaNoLLRB(arv->raiz); // Desaloca a partir da raíz
    free(arv); // Desaloca árvore
    return 0;
}

// Busca nó recursivamente
no_llrb *buscaNoLLRB(no_llrb *raiz, void *chave, Comparador_f comp) {
    if (!raiz) return NULL; // Confere se nó existe
    int c = comp(chave, raiz->val); // Compara chave com nó atual
    if (!c) return raiz; // Caso nó achado
    // Busca recursivamente
    if (c < 0) return buscaNoLLRB(raiz->esq, chave, comp);
    else return buscaNoLLRB(raiz->dir, chave, comp);
}

// Busca nó de chave passada na árvore
no_llrb *buscaLLRB(LLRB* arv, void *chave) {
    if (!arv || vaziaLLRB(arv)) return NULL; // Confere árvore
    return buscaNoLLRB(arv->raiz, chave, arv->comparador); // Busca a partir da raíz
}

// Retorna nó sucessor daquele com chave passada
no_llrb *sucessorLLRB(LLRB *arv, void*chave) {
    if (!arv || vaziaLLRB(arv)) return NULL; // Confere árvore
    // Busca nó e o confere
    no_llrb *aux = buscaLLRB(arv, chave);
    if (!aux) return NULL;

    if (aux->dir) // Caso sucessor direto, retorna menor nó entre os maiores que aquele com a chave
        return minNoLLRB(aux->dir);

    // Busca primeiro pai maior caso não haja sucessor direto
    no_llrb *temp = aux->pai;
    while (temp && temp->dir == aux) {
        aux = temp;
        temp = temp->pai;
    }
    if (arv->comparador(temp->val, aux->val) > 0)
        return temp;
    return NULL;
}

// Retorna nó predecessor daquele com chave passada
no_llrb *predecessorLLRB(LLRB *arv, void *chave) {
    if (!arv || vaziaLLRB(arv)) return NULL; // Confere árvore
    // Busca nó e o confere
    no_llrb *aux = buscaLLRB(arv, chave);
    if (!aux) return NULL;

    if (aux->esq) // Caso predecessor direto, retorna maior nó entre os maiores que aquele com a chave
        return maxNoLLRB(aux->esq);

    // Busca primeiro pai menor caso não haja sucessor direto
    no_llrb *temp = aux->pai;
    while (temp && temp->esq == aux) {
        aux = temp;
        temp = temp->pai;
    }
    if (arv->comparador(temp->val, aux->val) < 0)
        return temp;
    return NULL;
}

// Retorna nó com valor máximo na LLRB
no_llrb *maxLLRB(LLRB *arv) {
    if (vaziaLLRB(arv)) return NULL; // Confere árvore
    return maxNoLLRB(arv->raiz); // Retorna maior a partir da raíz
}

// Retorna nó com valor mínimo na LLRB
no_llrb *minLLRB(LLRB *arv) {
    if (vaziaLLRB(arv)) return NULL; // Confere árvore
    return minNoLLRB(arv->raiz); // Retorna menor a partir da raíz
}

// Insere nó com chave indicada na árvore
no_llrb *insereNoLLRB(no_llrb *raiz, no_llrb *pai, void *chave, Comparador_f comp) {
    if (!raiz) { // caso "espaço" vazio, alcoa nó
        raiz = malloc(sizeof(no_llrb)); // Aloca nó
        raiz->dir = raiz->esq = NULL; // Inicializa filhos nulos
        raiz->pai = pai; // Referencia pai
        raiz->val = chave; // Referencia valor
        raiz->vermelho = 1; // Cria inicialmente como nó vermelho
    } else {
        int c = comp(chave, raiz->val); // Compara chave com nó atual
        if (!c) return raiz; // Caso valor já presente, retorna
        else if (c < 0) raiz->esq = insereNoLLRB(raiz->esq, raiz, chave, comp); // Insere recursivamente a esquerda se menor
        else raiz->dir = insereNoLLRB(raiz->dir, raiz, chave, comp); // Insere recursivamente a direita se maior

        /* Confere e corrige regras de cores da LLRB */

        // Caso tenda a esquerda ou tenha filho (direito) preto
        if (confVerm(raiz->dir) && !confVerm(raiz->esq)) {
            raiz = rotaEsq(raiz); // Rotaciona garantido tendência
            trocaCores(raiz, raiz->esq); // Inverte cores garantindo filho vermelho
        }
        // Caso filho e neto esquerdos vermelhos
        if (confVerm(raiz->esq) && confVerm(raiz->esq->esq)) {
            raiz = rotaDir(raiz); // Corrige tendência
            trocaCores(raiz, raiz->dir); // Corrige distribuição de cores
        }
        // Caso ambos os filhos vermelhos
        if (confVerm(raiz->esq) && confVerm(raiz->dir)) {
            raiz->vermelho = !raiz->vermelho; // Inverte cor do nó atual
            raiz->esq->vermelho = raiz->dir->vermelho = 0; // Tranforma seus filhos em nós pretos
        }
    }
    return raiz;
}

// Insere nó com chave indicada na árvore
int insereLLRB(LLRB *arv, void *chave) {
    if (!arv) return 1; // Confere árvore
    arv->raiz = insereNoLLRB(arv->raiz, NULL, chave, arv->comparador); // Insere a partir da raíz garantindo estrutura
    arv->raiz->vermelho = 0; // Atualiza raíz preta
    return 0;
}

// Remove nó com chave indicada da árvore
int removeLLRB(LLRB *arv, void *chave); // Não implementada como não necessária no exercício!

/* Modos de exibição */

// Exibição pré ordem recursiva de nó
static void preOrdemNo(no_llrb *raiz, Exibicao_f exb) {
    if (!raiz) return; // Confere nó
    exb(raiz->val); // Exibe nó
    // Exibe filhos
    preOrdemNo(raiz->esq, exb);
    preOrdemNo(raiz->dir, exb);
}

// Exibição pré ordem
void preOrdemLLRB(LLRB *arv) {
    if (vaziaLLRB(arv)) return; // Confere árvore
    preOrdemNo(arv->raiz, arv->exibicao); // Exibe a partir da raíz
}

// Exibição em ordem recursiva de nó
static void emOrdemNo(no_llrb *raiz, Exibicao_f exb) {
    if (!raiz) return; // Confere nó
    emOrdemNo(raiz->esq, exb); // Exibe nó à esquerda
    exb(raiz->val); // Exibe nó
    emOrdemNo(raiz->dir, exb); // Exibe nós a direita
}

// Exibição em ordem
void emOrdemLRRB(LLRB *arv) {
    if (vaziaLLRB(arv)) return; // Confere árvore
    emOrdemNo(arv->raiz, arv->exibicao); // Exibe a partir da raíz
}

// Exibição pós ordem recursiva de nó
static void posOrdemNo(no_llrb *raiz, Exibicao_f exb) {
    if (!raiz) return; // Confere nó
    // Exibe filhos
    posOrdemNo(raiz->esq, exb);
    posOrdemNo(raiz->dir, exb);
    exb(raiz->val); // Exibe nó atual
}

// Exibição pós ordem
void posOrdemLLRB(LLRB *arv) {
    if (vaziaLLRB(arv)) return; // Confere árvore
    posOrdemNo(arv->raiz, arv->exibicao); // Exibe a partir da raíz
}
