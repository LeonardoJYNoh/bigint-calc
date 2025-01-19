#include "bignumber.h"
#include <stdio.h>

int main() {

    BigNumber* a = string_para_BigNumber("-2130813");
    BigNumber* b = string_para_BigNumber("+123");

    char sinal = '-';

    BigNumber* resultado = operacao(a, b, sinal);

    printf("Resultado da operacao: ");
    printBigNumber(resultado);

    libera_BigNumber(a);
    libera_BigNumber(b);
    libera_BigNumber(resultado);

    return 0;
}