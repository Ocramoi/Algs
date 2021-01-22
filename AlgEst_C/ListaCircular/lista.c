#include <stdlib.h>
#include "lista.h"

lista *criaLista() { // Cria estrutura da lista
    lista *nova = malloc(sizeof(lista)); // Aloca memória
    // Inicializa valores
    nova->ini = NULL;
    nova->fim = NULL;
    nova->tam = 0;
    return nova;
}

int adicionaElemento(lista *l, void *val, int pos) { // Adiciona elemento a posição correta (-1 para adicionar ao final)
    if (!l || pos < -1 || pos > l->tam) return 1; // Confere se lista existe, é válida e entrada é correta

    if (pos == l->tam) pos = -1; // Se posição além do final da lista, considera adição ao final

    // Aloca memória do nó a criar e inicializa seus valores
    no *novo = malloc(sizeof(no));
    novo->prox = NULL;
    novo->ant = NULL;
    novo->val = val;

    if (pos == -1) { // Caso adição ao final
        if (listaVazia(l))
            l->ini = novo; // Se lista vazia adiciona no começo
        else {
            novo->ant = l->fim; // Caso não, atualiza ponteiro do próximo valor do anteriormente último e anterior do adicionado
            l->fim->prox = novo;
        }
        
        l->fim = novo; // Adiciona ao final da lista 
        novo->prox = l->ini;
        l->ini->ant = novo;
    }
    else {
        if (pos == 0) { // Caso adição ao início
            l->ini->ant = novo; // Atualiza ponteiros de links
            novo->prox = l->ini;
            l->ini = novo; // Adiciona ao começo
            novo->ant = l->fim;
        }
        else { // Caso adição no meio da lista
            no *atual = l->ini;
            for (int i = 0; i < pos - 1 && atual; ++i)
                atual = atual->prox; // Percorre a lista a procura do local correto paara a adição

            // Atualiza ponteiros dos vizinhos e adiciona nó
            no *temp = atual->prox;
            atual->prox->ant = novo;
            atual->prox = novo;
            novo->prox = temp;
            novo->ant = atual;
        }
    }

    l->tam++; // Atualiza tamanho em caso de sucesso
    return 0;
}

int removeIndice(lista *l, int id) { // Remove elemento por índice id
    if (!l || l->tam == 0 || id >= l->tam) return 1; // Caso lista não exista, vazia ou índice fora da lista
    
    no *atual = l->ini, // Variáveis atuxiliares
       *ant = NULL;
    int i = 0;
    
    while (atual && i <= id) { // Procura por id atualizando ponteiro e seu anterior
        if (i == id) break;
        ant = atual;
        atual = atual->prox;
        i++;
    }

    if (!atual) return 1; // Caso id não achado, retorna erro

    // Trata casos adversos
    if (atual == l->fim) {
        l->fim = ant;
        ant->prox = l->ini;
    }

    if (!ant) {
        l->ini = atual->prox;
        atual->prox->ant = l->fim;
    }
    else {
        ant->prox = atual->prox;
        atual->prox->ant = ant;
    }

    // Libera ponteiro e atualiza tamanho
    free(atual->val);
    free(atual);
    l->tam--;
    return 0;
}

int listaVazia(lista *l) { // Confere se a lista existe e se seu tamanho é não-zero
    if (!l) return -1;
    return !l->tam;
}

void drestroiNo(no *el) { // Função recursiva para destruir nós subsequentes
    if (!el) return; // elemento nulo como caso base
    drestroiNo(el->prox); // Chama recursivamente a função para o próximo elemento
    // Libera memória do elemento
    free(el->val);
    free(el);
}

int destroiLista(lista *l) { // Confere se lista existe e libera seus ponteiros
    if (!l) return 1; // Confere se lista existe
    l->fim->prox = NULL; // Limita o fim da lista circular
    drestroiNo(l->ini); // Destroi nó inicial e seus subsequente (todos)
    free(l); // Libera ponteiro da lista
    return 0;
}