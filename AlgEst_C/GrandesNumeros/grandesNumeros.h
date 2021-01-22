#ifndef _GRANDES_NS
#define _GRANDES_NS

#include "lista.h"

typedef struct {
    char negativo;
    lista *valor;
} numero;

// Gera número a partir da entrada em string
numero *geraNumero(char *entrada);

 // Libera memória referente ao número
int destroiNumero(numero *v);

// Função que soma valores previamente gerados
numero *soma(numero *v1, numero *v2);

// Confere se o primeiro valor é maior que o segundo
int big(numero *v1, numero *v2);

// Confere se o primeiro valor é menor que o segundo
int sml(numero *v1, numero *v2);

// Confere se valores são iguais
int eql(numero *v1, numero *v2);

// Exibe o valor a partir de sua estrutura
void imprime(numero *v);

#endif