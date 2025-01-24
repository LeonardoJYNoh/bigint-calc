#include "bignumber.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//cria BigNumber vazio
BigNumber* criar_BigNumber() {
    BigNumber* number = malloc(sizeof(BigNumber));
    number->head = number->tail = NULL;
    number->tamanho = 0;
    number->eh_negativo = 0;
    number->identificacao = 0;

    return number;
}

//libera memória para um BigNumber 
void libera_BigNumber(BigNumber* number) {
    Node* atual = number->head;
    int count = number->tamanho;

    while (count > 0) { 
        Node* prox = atual->prox; 
        free(atual);              
        atual = prox;             
        count--;                  
    }

    free(number); 
}

//multiplica bignumber por inteiro
BigNumber* multiplica_BigNumber_inteiro(BigNumber* a, int b){
    char *str = (char*) malloc(20 * sizeof(char));
    sprintf(str, "%d", b);

    BigNumber* temp = multiplica_BigNumber(a, string_para_BigNumber(str));

    free(str);

    return temp;
}

//remove possíveis zeros à esquerda do BigNumber, para representá-lo de maneira correta
void remove_zero(BigNumber* a){
    if((a->head->ant == NULL && a->head->prox == NULL && a->head->valor == 0) || a->head->valor != 0){
        return;
    }else if(a->head->valor == 0){
        while(a->head->valor == 0){
            a->head = a->head->prox;
            a->head->ant = NULL;
            a->tamanho--;
        }
    }else{
        printf("deu erro aqui");
    }
}

//acrescenta valores no final da "lista"
void adiciona_no_final(BigNumber* number, int valor){
    Node* novo_node = malloc(sizeof(Node));
    novo_node->valor = valor; 
    novo_node->prox = NULL;   
    novo_node->ant = number->tail; 

    if (number->tail) {
        number->tail->prox = novo_node; 
    } else {
        number->head = novo_node; 
    }

    number->tail = novo_node;  
    number->tamanho++;           
}

//acrescenta valores no início da "lista"
void adiciona_no_inicio(BigNumber* number, int valor) {
    Node* novo_node = malloc(sizeof(Node));
    novo_node->valor = valor;
    novo_node->prox = number->head; 
    novo_node->ant = NULL;          

    if (number->head) {
        number->head->ant = novo_node; 
    } else {
        number->tail = novo_node; 
    }

    number->head = novo_node; 
    number->tamanho++;
}

//retorna o maior int
char maiorInt(int a, int b){
    if(b > a){
        return 'b';
    }else{
        return 'a';
    }
}

//retorna o maior BigNumber em módulo
char maiorBigNumber(BigNumber* a, BigNumber* b){
    if(a->tamanho != b->tamanho){
        return maiorInt(a->tamanho, b->tamanho);
    }
    else{
        Node* casa_a = a->head;
        Node* casa_b = b->head;

        while(casa_a != NULL && casa_b != NULL){
            if(casa_a->valor != casa_b->valor){
                return maiorInt(casa_a->valor, casa_b->valor);
            }

            casa_a = casa_a->prox;
            casa_b = casa_b->prox;            
        }

        return 'c';     
    }
}

//altera sinal se necessario
void alteraSinalSoma(BigNumber* a, BigNumber* total){
    if(a->eh_negativo == 1){
        total->eh_negativo = 1;
    }
}

//determina o sinal da subtração
void alteraSinalSubtracao(BigNumber* a, BigNumber* b, BigNumber* total){
    char maior = maiorBigNumber(a, b);

    if(maior == 'a' && (a->eh_negativo == 1)){
        total->eh_negativo = 1;
    }else if(maior == 'b' && (a->eh_negativo == 0)){
        total->eh_negativo = 1;
    }
}

//determina o sinal da divisão e multiplicação
void alteraSinalDivisaoMultiplicacao(BigNumber* a, BigNumber*b, BigNumber* total){
    if(a->eh_negativo != b->eh_negativo){
        total->eh_negativo = 1;
    }
}

//converte a string obtida nos inputs em BigNumbers
BigNumber* string_para_BigNumber(const char* string) {
    BigNumber* number = criar_BigNumber(); 

    int start = 0; 
    if (string[0] == '-') {
        number->eh_negativo = 1;
        start = 1; 
    } else if (string[0] == '+') {
        start = 1; 
    }

    for (int i = start; string[i] != '\0'; i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            adiciona_no_final(number, string[i] - '0'); 
        } else {
            printf("Erro no caracter '%c'\n", string[i]);
            libera_BigNumber(number);
            return NULL;
        }
    }

    remove_zero(number);

    return number;
}

//imprime o BigNumber obtido como resultado
void printBigNumber(BigNumber* number) {
    
    if (number->eh_negativo){
        printf("-"); // Imprime o sinal nos casos necessários
    }

    Node* atual = number->head;

    while(atual != NULL){
        printf("%d", atual->valor);
        atual = atual->prox;
    }

    printf("\n");
}

//função para somar BigNumbers
BigNumber* soma_BigNumber(BigNumber* a, BigNumber* b){

    BigNumber* total = criar_BigNumber();
    
    Node* casa_a = a->tail; 
    Node* casa_b = b->tail; 
    int retencao = 0; 

    while (casa_a != NULL || casa_b != NULL || retencao){
        int soma = retencao; 

        if (casa_a != NULL){
            soma += casa_a->valor;
            casa_a = casa_a->ant;
        }

        if (casa_b != NULL){
            soma += casa_b->valor;
            casa_b = casa_b->ant;
        }

        retencao = soma / 10;
        adiciona_no_inicio(total, soma % 10);    
    }

    alteraSinalSoma(a, total);

    remove_zero(total);

    return total;
}

//função para subtrair BigNumbers
BigNumber* subtrai_BigNumber(BigNumber* a, BigNumber* b){

    BigNumber* total = criar_BigNumber();

    char maior = maiorBigNumber(a, b);

    Node* casa_maior;
    Node* casa_menor;

    if(maior == 'a'){
        casa_maior = a->tail; 
        casa_menor = b->tail; 
    }else if(maior == 'b'){
        casa_maior = b->tail; 
        casa_menor = a->tail; 
    }else{
        adiciona_no_final(total, 0); 
        return total;
    }

    Node* posVar;

    while(casa_maior != NULL){
        
        int subAtual = 0;

        if(casa_menor == NULL){
            subAtual = casa_maior->valor;
        }
        else if(casa_maior->valor >= casa_menor->valor){
            subAtual = casa_maior->valor - casa_menor->valor;
        }
        else{
            int count = 1;

            posVar = casa_maior->ant;

            while(posVar->valor == 0){
                posVar = posVar->ant;
                count++;
            }

            posVar->valor--;

            for(int i = 0; i < count; i++){
                posVar = posVar->prox;
                if(i == count-1){
                    posVar->valor += 10;
                }else{
                    posVar->valor += 9;
                }
            }

            subAtual = casa_maior->valor - casa_menor->valor;
        }

        casa_maior = casa_maior->ant;
        casa_menor = (casa_menor != NULL) ? casa_menor->ant : casa_menor;

        adiciona_no_inicio(total, subAtual);
    }
    
    alteraSinalSubtracao(a, b, total);

    remove_zero(total);

    return total;
}

//função para multiplicar BigNumbers
BigNumber* multiplica_BigNumber(BigNumber* a, BigNumber* b) {
    BigNumber* total = criar_BigNumber();

    Node* casa_b = b->tail;
    int valor_decimal = 0;  

    while (casa_b != NULL) {
        if (casa_b->valor != 0) { 
            BigNumber* soma_parcial = criar_BigNumber(); 
            int valor_atual = casa_b->valor;

            for (int i = 0; i < valor_atual; i++) {
                BigNumber* soma = soma_BigNumber(soma_parcial, a); 
                libera_BigNumber(soma_parcial); 
                soma_parcial = soma; 
            }
	    
            for (int i = 0; i < valor_decimal; i++) {
                adiciona_no_final(soma_parcial, 0); 
            }

            BigNumber* parcial = soma_BigNumber(total, soma_parcial);
            libera_BigNumber(total);
            total = parcial;

            libera_BigNumber(soma_parcial);
        }
        casa_b = casa_b->ant;
        valor_decimal++;
    }

    alteraSinalDivisaoMultiplicacao(a, b, total);
    remove_zero(total);

    return total;
}

//função para dividir BigNumbers
BigNumber* divide_BigNumber(BigNumber* a, BigNumber* b){

    BigNumber* quociente = criar_BigNumber();
    
    if(maiorBigNumber(a,b) == 'b'){
        adiciona_no_final(quociente, 0);
        return quociente;
    }else if(b->head->valor == 0){
        adiciona_no_final(quociente, 0);
        return quociente;
    }

    adiciona_no_final(quociente, 1);

    int temp = a->eh_negativo;

    int i = 1;
    int j = 1;

    while(maiorBigNumber(a, multiplica_BigNumber_inteiro(b, i)) == 'a' || maiorBigNumber(a, multiplica_BigNumber_inteiro(b, i)) == 'c'){
        i*=10;
    }

    i=i/10;

    while(maiorBigNumber(a, multiplica_BigNumber_inteiro(b, i * j)) == 'a' || maiorBigNumber(a, multiplica_BigNumber_inteiro(b, i * j)) == 'c'){
        j++;
    }

    j--;

    a = subtrai_BigNumber(a, multiplica_BigNumber_inteiro(b, i * j));
    quociente = multiplica_BigNumber_inteiro(quociente, i * j);

    while(maiorBigNumber(a, b) == 'a' || maiorBigNumber(a, b) == 'c'){
        a = subtrai_BigNumber(a, b);
        quociente = incrementa_bignumber(quociente);
    }

    a->eh_negativo = temp;

    alteraSinalDivisaoMultiplicacao(a, b, quociente);

    remove_zero(quociente);

    return quociente;
}

//função extra para obter o resto das divisões entre BigNumbers
BigNumber* resto_BigNumber(BigNumber* a, BigNumber* b) {
    
    if (b->head->valor == 0) {
        return NULL;
    }
    
    BigNumber* resto = criar_BigNumber();
    Node* casa_a = a->head;
    while (casa_a != NULL) {
        adiciona_no_final(resto, casa_a->valor);
        casa_a = casa_a->prox;
    }
    
    if (maiorBigNumber(a, b) == 'b') {
        return resto;
    }

    while (maiorBigNumber(resto, b) == 'a' || maiorBigNumber(resto, b) == 'c') {
        BigNumber* subtracao = subtrai_BigNumber(resto, b);
        libera_BigNumber(resto);
        resto = subtracao;
    }

    resto->eh_negativo = a->eh_negativo;

    remove_zero(resto);

    return resto;
}

//função usada para obter o quociente na divisão
BigNumber* incrementa_bignumber(BigNumber* a){
    BigNumber* incremento = criar_BigNumber();
    adiciona_no_final(incremento, 1);

    return soma_BigNumber(a, incremento);
}

//chama a operação a ser executada dependendo do input fornecido
BigNumber* operacao(BigNumber* a, BigNumber* b, char sinal){
    if((sinal == '+' && (a->eh_negativo == b->eh_negativo)) || (sinal == '-' && (a->eh_negativo != b->eh_negativo))){
        return soma_BigNumber(a, b);
    }else if((sinal == '+' && (a->eh_negativo != b->eh_negativo)) || (sinal == '-' && (a->eh_negativo == b->eh_negativo))){
        return subtrai_BigNumber(a, b);
    }else if(sinal == '/'){
        return divide_BigNumber(a, b);
    }else if(sinal == '*'){
        return multiplica_BigNumber(a, b);
    }else if(sinal == '%'){
        return resto_BigNumber(a, b);
    }else{
	return NULL;
    }
}
