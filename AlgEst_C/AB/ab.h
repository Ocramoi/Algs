typedef struct no_t no;

struct no_t {
    no *esq,
       *dir;
    int val;
};

typedef struct {
    no *raiz;
} arvore;

arvore *cria();
int esta_vazia(arvore *ar);
void finaliza(no *raiz);
void imprime(no *raiz);
int altura(no *raiz, int tam);
no *busca(no *raiz, int x);
no *buscaPai(no *raiz, int x);
int inserirEsq(arvore *ar, int x, int pai);
int inserirDir(arvore *ar, int x, int pai);
int remover(arvore *ar, int x);
void preOrdem(no *raiz);
void emOrdem(no *raiz);
void posOrdem(no *raiz);