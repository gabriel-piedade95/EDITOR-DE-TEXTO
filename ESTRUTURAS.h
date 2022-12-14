#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ******* LISTA DUPLMENTE LIGADA ******** */


// Estrutura usada para salvar as linhas do arquivo
struct linha{

    struct linha *prox;
    struct linha *ant;
    int tam; // tamanho da linha
    char * lin;

};

//linha inicial
struct linha * cabeca;


struct linha * criaLinha(){

    struct linha * L = (struct linha *)malloc(sizeof(struct linha));
    L->lin= NULL;
    L->ant = NULL;
    L->prox = NULL;
    L->tam = 0;

   return L;
}

void insereLinhaCabeca(char * string){

    struct linha * novaLinha = criaLinha();
    novaLinha->lin = string;
    novaLinha->tam = strlen(string);

    if(cabeca == NULL){
        cabeca = novaLinha;
        return;
    }

    cabeca->ant = novaLinha;
    novaLinha->prox = cabeca;
    cabeca = novaLinha;

}

void insereLinha(struct linha * L, char * string){

    if(L == NULL){
        return;
    }

    struct linha * novaLinha = criaLinha();
    novaLinha->lin = string;
    novaLinha->tam = strlen(string);

    novaLinha->prox = L->prox;
    L->prox = novaLinha;
    novaLinha->ant = L;

    if(L->prox != NULL){
        novaLinha->prox->ant = novaLinha;
    }
}

void insereLinhaFim(char * string){

    struct linha * novaLinha = criaLinha();
    novaLinha->lin = string;
    novaLinha->tam = strlen(string);
    

    struct linha * fim = cabeca;

    novaLinha->prox = NULL;

    if(cabeca == NULL){
        novaLinha->ant = NULL;
        cabeca = novaLinha;
        return;
    }

    while(fim->prox != NULL){
        fim = fim->prox;
    }

    fim->prox = novaLinha;
    novaLinha->ant = fim;
    
    return;
}

void liberaLinha(struct linha * L){

    free(L->lin);
    free(L);
}

void removeLinha(struct linha * L){

    if(cabeca == NULL || L == NULL){
        return;
    }
    if(cabeca == L){
        cabeca = L->prox;
    }
    
    if(L->prox != NULL){
        L->prox->ant = L->prox;
    }

    if(L->ant != NULL){
        L->ant->prox = L->prox;
    }

    liberaLinha(L);
    return;

}


void imprimeLinha(struct linha * L){

    printf("%s\n", L->lin);

}

void imprimeTexto(){

    struct linha * aux = cabeca;

    while (aux != NULL){
        imprimeLinha(aux);
        aux = aux->prox;
    }
    

}
/* *********************************** */


/*********** PILHA DE COMANDO ***********/




/* *********************************** */

/*********** INFORMACAO PROGRAMA ***********/

struct info{

    int lin;
    int col;
    int n_linhas;
    int col_M;
    int lin_M;
    char * nome_arquivo;
    struct linha * linha_atual;


};

struct info * iniciaINFO(){

    struct info * Info = (struct info *)malloc(sizeof(struct info));
    Info->lin = 0;
    Info->col = 0;
    Info->col_M = 0;
    Info->lin_M = 0;
    Info->linha_atual = cabeca;
    Info->nome_arquivo = NULL;
    Info->n_linhas = 0;

    return Info;
    
}

void liberaINFO(struct info * I){

    free(I);
    return;
}


/* ************************************** */

