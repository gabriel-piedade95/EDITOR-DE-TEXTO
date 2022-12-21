#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ******* LISTA DUPLMENTE LIGADA ******** */


// Estrutura usada para salvar as linhas do arquivo
struct linha{

    struct linha *prox;// proxima linha
    struct linha *ant;// linha anterior
    int tam; // tamanho da linha
    char * lin;// string representando a linha

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

// insere uma nova linha apos a linha atual
void insereLinha(struct linha * L, char * string){

    if(L == NULL){// se a linha a ser inserida estiver vaizia nao faz nada
        return;
    }

    // caso contrario insere a linha
    struct linha * novaLinha = criaLinha();// cria estrutura
    novaLinha->lin = string;
    novaLinha->tam = strlen(string);

    novaLinha->prox = L->prox;
    L->prox = novaLinha;
    novaLinha->ant = L;

    if(L->prox != NULL){
        novaLinha->prox->ant = novaLinha;
    }
}

// insere uma linha no fim do texto
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


// remove a linha atual
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

    free(L);
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

void apagaTexto(){

    struct linha * aux = cabeca;

    while(aux != NULL){
        
        struct linha * prox = aux->prox;
        free(aux);
        aux = prox;
    }

    cabeca = NULL;
    
}
/* *********************************** */


/*********** PILHA  ***********/

struct noh
{
    char * lin;
    struct noh * prox;
    
};

struct noh * topo = NULL;


void Empilha(char * s){

    struct noh * N = (struct noh *) malloc(sizeof (struct noh));
    N->lin = s;

    if(topo == NULL){
        N->prox = NULL;
    }
    else{
        N->prox = topo;
    }
    topo = N;
    
}

char * Desempilha(){
    
    char * s = NULL;
    if(topo != NULL){
        struct noh * aux = topo;
        s = topo->lin;
        topo = topo->prox;
        free(aux);
    }
    return s;
}

void mostraPilha(){

    
    if(topo != NULL){

        struct noh * aux = topo;
        while(aux != NULL){

            printf("%s\n", aux->lin);
            aux = aux->prox;

        }
        
    }
}

void apagaPilha(){

    while(topo != NULL){
        Desempilha();
    }
}

/* *********************************** */

