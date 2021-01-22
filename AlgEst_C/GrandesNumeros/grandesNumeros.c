#include <stdlib.h>
#include <stdio.h>
#include "grandesNumeros.h"

numero *geraNumero(char *entrada) { // Gera número a partir da entrada em string
    char *p = entrada; // Armazena ponteiro da string de entrada
    numero *novo = malloc(sizeof(numero)); // Aloca novo número
    novo->negativo = 0; // Inicializa valor como positivo
    while (*p != '-' && (*p < '0' || *p > '9')) { // Pula valores não numéricos ou '-'
        if (*p == '\0') {
            free(novo);
            return NULL;
        }
        p++;
    }
    novo->valor = criaLista(); // Cria lista do valor do número
    if (*p == '-') { // Trata entrada negativa
        novo->negativo = 1;
        p++;
    }
    while (*p) { // Adiciona elementos para todos os algarismos significativos
        if (*p != '0' || novo->valor->tam != 0) // Ignora 0s a esquerda
            adicionaElemento(novo->valor, *p - '0', -1);
        p++;
    }

    return novo;
}

int destroiNumero(numero *v) { // Libera memória referente ao número
    if (!v) return 1; // Confere se número existe
    destroiLista(v->valor); // Libera memória da lista que contém seu valor
    free(v); // Libera seu ponteiro
    return 0;
}

numero *soma(numero *v1, numero *v2) { // Função que soma valores previamente gerados
    numero *s = malloc(sizeof(numero));
    s->valor = criaLista(); // Aloca memórias referente ao número

    no *f1 = v1->valor->fim,
       *f2 = v2->valor->fim; // Inicializa ponteiros em ambos os algaritmos menos significativos
    int resto = 0; // Variável auxiliar

    if (v1->negativo == v2->negativo) { // Caso ambos os valores possuam o mesmo sinal -> soma
        while (f1 || f2) { // Enquanto há elementos em uma das listas
            int v; // Variável auxiliar de valor para o valor final
            if (f1 && f2) { // Caso ainda haja elementos em ambos os vetores
                v = f1->val + f2->val + resto; // Soma valores e resto
                adicionaElemento(s->valor, v%10, 0); // Adiciona unidades da soma
                resto = v/10; // Atualiza resto
                f1 = f1->ant; f2 = f2->ant; // Atualiza elemento atual de ambos os vetores
            }
            else {
                v = f1 ? (f1->val + resto) : (f2->val + resto); // Estabelece o valor com base em qual elemento existe + resto
                adicionaElemento(s->valor, v%10, 0); // Adiciona unidades da soma
                resto = v/10; // Atualiza resto
                f1  = f1 ? f1->ant : NULL; // Atualiza elementos
                f2  = f2 ? f2->ant : NULL;
            }
        }
        if (resto > 0)
            adicionaElemento(s->valor, resto, 0); // Adiciona resto caso haja ao final da soma dos elementos
    }
    else { // Caso os valores não possuam o mesmo sinal -> subtração
        // Considera v1 como o maior valor (em módulo)
        char n1 = v1->negativo, n2 = v2->negativo;
        v1->negativo = 0; v2->negativo = 0;
        if (big(v2, v1)) { 
            numero *temp = v1;
            v1 = v2;
            v2 = temp;
            f1 = v1->valor->fim; f2 = v2->valor->fim;
            v1->negativo = n2; v2->negativo = n1;
        }
        else
            v1->negativo = n1; v2->negativo = n2;
        
        while (f1 || f2) { // Enquanto há elementos em uma das listas
            int v; // Variável auxiliar de valor
            // Realiza operações nos moldes da soma
            if (f1 && f2) {
                resto = 0; // Inicializa resto
                v = f1->val - f2->val - resto; // Considera valor como agora a subtração com o resto
                if (f1->val - resto < f2->val) { // Confere se necessário "emprestar" do algarismo vizinho
                    v += 10; // Atualiza valor, tornando-o positivo
                    resto = 1; // Atualiza resto
                }
                
                adicionaElemento(s->valor, v, 0); // Adiciona elemento do valor
                f1 = f1->ant; f2 = f2->ant; // Atualiza ponteiros
            }
            else { // Caso apenas um dos elementos exista
                v = f1 ? f1->val : f2->val; // Atualiza valor correto
                adicionaElemento(s->valor, v - resto, 0); // Adiciona valor subtraído do resto 
                resto = 0; // Atualiza resto
                f1  = f1 ? f1->ant : NULL; // Atualiza ponteiro correto
                f2  = f2 ? f2->ant : NULL;
            }
        }
    }
    s->negativo = v1->negativo; // Corrige sinal
    return s;
}

int big(numero *v1, numero *v2) { // Confere se o primeiro valor é maior que o segundo
    if (!v1 || !v2) return -1; // Confere se ambos os números existem
    if (v1->negativo ^ v2->negativo) // Caso apenas um deles seja negativo retorna se o negativo é o segundo valor
        return v2->negativo;
    if (v1->negativo == v2->negativo && v1->valor->tam != v2->valor->tam) // Caso ambos tenham o mesmo sinal e tamanhos diferentes
        return v1->negativo * (v1->valor->tam < v2->valor->tam) + !v1->negativo * (v1->valor->tam > v2->valor->tam); // Retorna o com mais algarismos caso positivos e o menor caso negativos
    
    // Caso não entrem em nenhum dos casos acima, ou seja, possuem o mesmo sinal e o mesmo número de algarismos
    no *atualV1 = v1->valor->ini,
       *atualV2 = v2->valor->ini;
    while (atualV1 && atualV2) { // Caminha entre os vetores a partir do algarismo mais significativo realizando a comparação correta
        if (atualV1->val > atualV2->val) return 1;
        atualV1 = atualV1->prox;
        atualV2 = atualV2->prox;
    }

    return 0;
}

int sml(numero *v1, numero *v2) { // Confere se o primeiro valor é menor que o segundo
    if (!v1 || !v2) return -1; // Confere se ambos os números existem
    if (v1->negativo ^ v2->negativo)  // Caso apenas um deles seja negativo retorna se o negativo é o primeiro valor
        return v1->negativo;
    if (v1->negativo == v2->negativo && v1->valor->tam != v2->valor->tam) // Caso ambos tenham o mesmo sinal e tamanhos diferentes
        return v1->negativo * (v1->valor->tam > v2->valor->tam) + !v1->negativo * (v1->valor->tam < v2->valor->tam); // Retorna o com menos algarismos caso positivos e o maior caso negativos
    
    // Caso não entrem em nenhum dos casos acima, ou seja, possuem o mesmo sinal e o mesmo número de algarismos
    no *atualV1 = v1->valor->ini,
       *atualV2 = v2->valor->ini;
    while (atualV1 && atualV2) {// Caminha entre os vetores a partir do algarismo mais significativo realizando a comparação correta
        if (atualV1->val < atualV2->val) return 1;
        atualV1 = atualV1->prox;
        atualV2 = atualV2->prox;
    }

    return 0;
}

int eql(numero *v1, numero *v2) { // Confere se valores são iguais
    if (!v1 || !v2) return -1; // Confere se ambos os números existem
    if (v1->negativo != v2->negativo || v1->valor->tam != v2->valor->tam) // Confere se possuem o mesmo sinal e número de algarismos
        return 0;
    
    no *atualV1 = v1->valor->ini,
       *atualV2 = v2->valor->ini;
    while (atualV1 && atualV2) { // Compara por diferenças entre os algarismo
        if (atualV1->val != atualV2->val) return 0;
        atualV1 = atualV1->prox;
        atualV2 = atualV2->prox;
    }

    return 1;
}

void imprime(numero *v) { // Exibe o valor a partir de sua estrutura
    if (!v || v->valor->tam == 0) return; // Confere se o número exista e possui algarismos 

    if (v->negativo) printf("-"); // Exibe '-' se negativo
    no *atual = v->valor->ini;
    while (atual) { // Percorre o vetor exibindo o valor de cada algarismo
        printf("%d", atual->val);
        atual = atual->prox;
    }
}