#include "bignumber.h"
#include <stdlib.h>
#include <stdio.h>

BigNumber* criar_BigNumber() {
    BigNumber* number = malloc(sizeof(BigNumber));
    number->head = number->tail = NULL;
    number->tamanho = 0;
    number->eh_negativo = 0;
    number->identificacao = 0;

    return number;

    //cria um BigNumber vazio
}

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

void adiciona_no_final(BigNumber* number, int valor){
    //criação de um novo nó

    Node* novo_node = malloc(sizeof(Node));
    novo_node->valor = valor; //agrega um valor ao nó
    novo_node->prox = NULL;   //proximo valor dele será nulo
    novo_node->ant = number->tail; //o anterior será o nó que atualmente é o tail

    if (number->tail) {
        number->tail->prox = novo_node; // o antigo tail aponta para o novo nó, caso a lista não estaja vazia(number->tail não é NULL)
    } else {
        number->head = novo_node; // se a lista estava vazia, o head também é o novo nó
    }

    number->tail = novo_node;  // atualiza o tail para o novo nó
    number->tamanho++;           // incrementa o valor do tamanho

//acrescenta valores no final da "lista".

}

void adiciona_no_inicio(BigNumber* number, int valor) {
    Node* novo_node = malloc(sizeof(Node));
    novo_node->valor = valor;
    novo_node->prox = number->head; // o próximo nó é o atual head
    novo_node->ant = NULL;          // não há anterior para o novo head

    if (number->head) {
        number->head->ant = novo_node; // atualiza o anterior do antigo head
    } else {
        number->tail = novo_node; // se a lista estava vazia, tail também aponta para o novo nó
    }

    number->head = novo_node; // atualiza o head para o novo nó
    number->tamanho++;
}

BigNumber* incrementa_bignumber(BigNumber* a){
    BigNumber* incremento = criar_BigNumber();
    adiciona_no_final(incremento, 1);

    return soma_BigNumber(a, incremento);
}

BigNumber* string_para_BigNumber(const char* string) {
    BigNumber* number = criar_BigNumber(); 

    int start = 0; // Índice inicial
    if (string[0] == '-') {
        number->eh_negativo = 1;
        start = 1; // Começa após o sinal
    } else if (string[0] == '+') {
        start = 1; // Ignora o sinal '+'
    }

    for (int i = start; string[i] != '\0'; i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            adiciona_no_final(number, string[i] - '0'); // Converte caractere para inteiro
        } else {
            printf("Erro no caracter '%c'\n", string[i]);
            libera_BigNumber(number);
            return NULL;
        }
    }

    remove_zero(number);

    return number;
}

void libera_BigNumber(BigNumber* number) {
    Node* atual = number->head;
    int count = number->tamanho;

    while (count > 0) { // Usa o tamanho como critério
        Node* prox = atual->prox; // Salva o próximo nó
        free(atual);              // Libera o nó atual
        atual = prox;             // Avança para o próximo nó
        count--;                  // Decrementa o contador
    }

    free(number); // Libera a estrutura principal do BigNumber
}

void printBigNumber(BigNumber* number) {
    
    if (number->eh_negativo){
        printf("-"); // Imprime o sinal, se necessário
    }

    Node* atual = number->head;

    while(atual != NULL){
        printf("%d", atual->valor);
        atual = atual->prox;
    }

    printf("\n");
}


BigNumber* soma_BigNumber(BigNumber* a, BigNumber* b){

    BigNumber* total = criar_BigNumber();
    
    Node* casa_a = a->tail; //começa pela casa das unidades
    Node* casa_b = b->tail; //começa pela casa das unidades
    int retencao = 0; //numero para a proxima casa

    while (casa_a != NULL || casa_b != NULL || retencao){
        int soma = retencao; //começa com 0 nas unidades, e se a soma der >= 10 a soma começara com um valor diferente de 0

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

BigNumber* subtrai_BigNumber(BigNumber* a, BigNumber* b){

    BigNumber* total = criar_BigNumber();

    char maior = maiorBigNumber(a, b);

    Node* casa_maior;
    Node* casa_menor;

    if(maior == 'a'){
        casa_maior = a->tail; //começa pela casa das unidades
        casa_menor = b->tail; //começa pela casa das unidades
    }else if(maior == 'b'){
        casa_maior = b->tail; //começa pela casa das unidades
        casa_menor = a->tail; //começa pela casa das unidades
    }else{
        adiciona_no_final(total, 0); //simplesmente retorna 0 pois ambos bignumbers sao iguais
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

BigNumber* divide_BigNumber(BigNumber* a, BigNumber* b){

    BigNumber* quociente = criar_BigNumber();

    if(maiorBigNumber(a,b) == 'b'){
        adiciona_no_final(quociente, 0);
        return quociente;
    }else if(b->head->valor == 0){
        adiciona_no_final(quociente, 0);
        return quociente;
    }

    int temp = a->eh_negativo;

    while(maiorBigNumber(a, b) == 'a' || maiorBigNumber(a, b) == 'c'){
        a = subtrai_BigNumber(a, b);
        quociente = incrementa_bignumber(quociente);
    }

    a->eh_negativo = temp;

    alteraSinalDivisaoMultiplicacao(a, b, quociente);

    remove_zero(quociente);

    return quociente;
}

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

//altera sinal se necessario
void alteraSinalSoma(BigNumber* a, BigNumber* total){
    if(a->eh_negativo == 1){
        total->eh_negativo = 1;
    }
}

void alteraSinalSubtracao(BigNumber* a, BigNumber* b, BigNumber* total){
    char maior = maiorBigNumber(a, b);

    if(maior == 'a' && (a->eh_negativo == 1)){
        total->eh_negativo = 1;
    }else if(maior == 'b' && (a->eh_negativo == 0)){
        total->eh_negativo = 1;
    }
}

void alteraSinalDivisaoMultiplicacao(BigNumber* a, BigNumber*b, BigNumber* total){
    if(a->eh_negativo != b->eh_negativo){
        total->eh_negativo = 1;
    }
}

//retorna o int maior
char maiorInt(int a, int b){
    if(b > a){
        return 'b';
    }else{
        return 'a';
    }
}

//retorna a se o maior for o primeiro numero e retorna b se o maior for o segundo
//em modulo
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

//chama operacao soma ou subtracao dependendo dos sinais
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
