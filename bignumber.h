#ifndef BIGNUMBER_H     // evita que o cabecario ser usado
#define BIGNUMBER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    int valor;          // (0 - 9)
    struct Node* prox;  //ponteiro para o proximo numero
    struct Node* ant;   //ponteiro para o numero anterior
}   Node;

//lista duplamente encadeada

typedef struct BigNumber {
    Node* head;         //ponteiro para início da lista
    Node* tail;         //ponteiro para final da lista
    int tamanho;        //quantidade de dígitos
    int eh_negativo;    //bool para sinal (0 -> positivo, 1 -> negativo)
    int identificacao; //0 se é menor e 1 se é maior
}   BigNumber;

//estrutra de Bignumber, cabeça, calda, tamanho, sinal;

BigNumber* criar_BigNumber();
void adiciona(BigNumber* number, int valor);
BigNumber* incrementa_bignumber(BigNumber* a);
BigNumber* string_para_BigNumber(const char* string);
void libera_BigNumber(BigNumber* number);
void printBigNumber(BigNumber* number);
BigNumber* soma_BigNumber(BigNumber* a, BigNumber* b);
BigNumber* subtrai_BigNumber(BigNumber* a, BigNumber* b);
BigNumber* divide_BigNumber(BigNumber* a, BigNumber* b);

//funções

char maiorBigNumber(BigNumber* a, BigNumber* b);
char maiorInt(int a, int b);

BigNumber* operacao(BigNumber* a, BigNumber* b, char sinal);
void alteraSinalSoma(BigNumber* a, BigNumber* total);
void alteraSinalSubtracao(BigNumber* a, BigNumber* b, BigNumber* total);
void alteraSinalDivisao(BigNumber* a, BigNumber* b, BigNumber* quociente);
void remove_zero(BigNumber* a);

#endif //BIGNUMBER_H