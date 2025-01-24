#ifndef BIGNUMBER_H     // evita que o cabeçalho seja usado
#define BIGNUMBER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//estutura para um nó da lista duplamente encadeada
typedef struct Node {
    int valor;          // (0 - 9)
    struct Node* prox;  //ponteiro para o proximo numero
    struct Node* ant;   //ponteiro para o numero anterior
}   Node;

//estrutura para o BigNumber
typedef struct BigNumber {
    Node* head;         //ponteiro para início da lista
    Node* tail;         //ponteiro para final da lista
    int tamanho;        //quantidade de dígitos
    int eh_negativo;    //bool para sinal (0 -> positivo, 1 -> negativo)
    int identificacao; //0 se é menor e 1 se é maior
}   BigNumber;

BigNumber* criar_BigNumber();
void adiciona(BigNumber* number, int valor);
BigNumber* incrementa_bignumber(BigNumber* a);
BigNumber* string_para_BigNumber(const char* string);
void libera_BigNumber(BigNumber* number);
void printBigNumber(BigNumber* number);
void remove_zero(BigNumber* a);
BigNumber* multiplica_BigNumber_inteiro(BigNumber* a, int b);

char maiorBigNumber(BigNumber* a, BigNumber* b);
char maiorInt(int a, int b);

void alteraSinalSoma(BigNumber* a, BigNumber* total);
void alteraSinalSubtracao(BigNumber* a, BigNumber* b, BigNumber* total);
void alteraSinalDivisaoMultiplicacao(BigNumber* a, BigNumber* b, BigNumber* total);

BigNumber* soma_BigNumber(BigNumber* a, BigNumber* b);
BigNumber* subtrai_BigNumber(BigNumber* a, BigNumber* b);
BigNumber* multiplica_BigNumber(BigNumber* a, BigNumber* b);
BigNumber* divide_BigNumber(BigNumber* a, BigNumber* b);
BigNumber* resto_BigNumber(BigNumber* a, BigNumber* b);

BigNumber* operacao(BigNumber* a, BigNumber* b, char sinal);

#endif //BIGNUMBER_H
