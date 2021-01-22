#ifndef _LISTA
#define _LISTA

typedef int (*Comparador_f)(void*, void*);

typedef struct no_t no_lista;
struct no_t {
    void *val;
    no_lista *prox,
       *ant;
};

typedef struct {
    no_lista *ini,
       *fim;
    int tam;
    Comparador_f comp;
} lista;

// Cria estrutura da lista
lista *criaLista(int (*Comparador)(void*, void*));

// Adiciona elemento a posição correta (-1 para adicionar ao final)
int adicionaElemento(lista *l, void *val, int pos);

// Adiciona elemento ordenadamente
int adicionaElementoOrdenado(lista *l, void *val);

// Remove elemento por índice id
int removeIndice(lista *l, int id);

// Confere se a lista existe e se seu tamanho é não-zero
int listaVazia(lista *l);

// Confere se lista existe e libera seus ponteiros
int destroiLista(lista *l);

#endif
