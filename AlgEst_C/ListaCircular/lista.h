#ifndef _LISTA
#define _LISTA

typedef struct no_t no;
struct no_t {
    void *val;
    no *prox,
       *ant;
};

typedef struct {
    no *ini,
       *fim;
    int tam;
} lista;

// Cria estrutura da lista
lista *criaLista();

// Adiciona elemento a posição correta (-1 para adicionar ao final)
int adicionaElemento(lista *l, void *val, int pos);

// Remove elemento por índice id
int removeIndice(lista *l, int id);

// Confere se a lista existe e se seu tamanho é não-zero
int listaVazia(lista *l);

// Confere se lista existe e libera seus ponteiros
int destroiLista(lista *l);

#endif