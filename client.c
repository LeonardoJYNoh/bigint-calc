#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* x = NULL;
    char* y = NULL;
    size_t tamanhoX = 0, tamanhoY = 0;

    while (1) {
        if (getline(&x, &tamanhoX, stdin) == -1){
            break;
        }
        if (x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
        }

        if (getline(&y, &tamanhoY, stdin) == -1) {
            free(x);
            break;
        }
        if (y[strlen(y) - 1] == '\n') {
            y[strlen(y) - 1] = '\0';
        }

        char sinal;
        if (scanf(" %c", &sinal) == EOF) {
            free(x);
            free(y);
            break;
        }
        getchar(); 

        BigNumber *a = string_para_BigNumber(x);
        BigNumber *b = string_para_BigNumber(y);

        free(x);
        free(y);

        BigNumber *resultado = operacao(a, b, sinal);

        if (resultado != NULL) {
            printBigNumber(resultado);
        }

        libera_BigNumber(a);
        libera_BigNumber(b);
        libera_BigNumber(resultado);

        x = NULL;
        y = NULL;
        tamanhoX = 0;
        tamanhoY = 0;
    }

    return 0;
}
