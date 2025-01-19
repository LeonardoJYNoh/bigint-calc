#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char* x = NULL;
    size_t tamanhoX = 0;
    getline(&x, &tamanhoX, stdin);
    if (x[strlen(x) - 1] == '\n') {
        x[strlen(x) - 1] = '\0';
    }

    char* y = NULL;
    size_t tamanhoY = 0;
    getline(&y, &tamanhoY, stdin);
    if (y[strlen(y) - 1] == '\n') {
        y[strlen(y) - 1] = '\0';
    }

    BigNumber* a = string_para_BigNumber(x);
    BigNumber* b = string_para_BigNumber(y);

    free(x);
    free(y);

    char sinal;
    scanf("%c", &sinal);

    BigNumber* resultado = operacao(a, b, sinal);

    printBigNumber(resultado);

    libera_BigNumber(a);
    libera_BigNumber(b);
    libera_BigNumber(resultado);

    return 0;
}