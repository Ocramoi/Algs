#ifndef __LLRB_H_
#define __LLRB_H_

typedef int (*Comparador_f)(void*, void*);
typedef void (*Exibicao_f)(void*);

typedef struct no_t_llrb no_llrb;
struct no_t_llrb {
    void *val; // Valor de tipo genérico
    char vermelho; // Booleano se vermelho
    no_llrb *pai, // Pai do nó
            *esq, *dir; // Filhos do nó
};

typedef struct {
    no_llrb *raiz; // Raíz da árvore
    Comparador_f comparador; // Função de comparação para tipo genérico
    Exibicao_f exibicao; // Função de exibição de tipo genérico
} LLRB; // Estrutura da LLRB

// Inicializa nova LLRB
LLRB *criaLLRB(int (*Comparador)(void*, void*), void (*Exibicao)(void*));
// Confere de LLRB está vazia
int vaziaLLRB(LLRB *arv);
// Desaloca árvore
int desalocaLLRB(LLRB *arv);
// Busca nó de chave passada na árvore
no_llrb *buscaLLRB(LLRB* arv, void *chave);
// Retorna nó sucessor daquele com chave passada
no_llrb *sucessorLLRB(LLRB *arv, void *chave);
// Retorna nó predecessor daquele com chave passada
no_llrb *predecessorLLRB(LLRB *arv, void *chave);
// Retorna nó com valor máximo na LLRB
no_llrb *maxLLRB(LLRB *arv);
// Retorna nó com valor mínimo na LLRB
no_llrb *minLLRB(LLRB *arv);
// Insere nó com chave indicada na árvore
int insereLLRB(LLRB *arv, void *chave);
// Remove nó com chave indicada da árvore
int removeLLRB(LLRB *arv, void *chave);

/* Modos de exibição */

// Exibição pré ordem
void preOrdemLLRB(LLRB *arv);
// Exibição em ordem
void emOrdemLRRB(LLRB *arv);
// Exibição pós ordem
void posOrdemLLRB(LLRB *arv);

#endif // __LLRB_H_
