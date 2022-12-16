#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ESTRUTURAS.h"
#include "FUNCOES_PROGRAMA.h"


void fazabertura() {

	printf("****************************************************************\n");
    printf("*                                                              *\n");
	printf("*            ***      *EDITOR DE TEXTO*      ***               *\n");
    printf("*                                                              *\n");
	printf("****************************************************************\n");
    printf("by GABRIEL PIEDADE - nUSP8927356\nAperte ? para ver a lista de comandos\n");
	printf("\n");
}


void imprimeLinhaAtual(struct info * I){
    
    int i;
    if(I->linha_atual == NULL){

        printf("\n");
        printf("^\n\n");

    }
    else{

        printf("%s\n", I->linha_atual->lin);
        char s[I->linha_atual->tam+2];
        for(i = 0; i < I->linha_atual->tam+2; i++){
            s[i] = ' ';
        }
        s[I->linha_atual->tam+2] = '\0';
        s[I->col_M] = 'M';
        s[I->col] = '^';
        printf("%s\n\n", s);
    }
    
        
}
void fechaPrograma(struct info * I){
    
    liberaINFO(I);
    apagaPilha();
    apagaTexto();

}



void Iteracao_do_Programa(){


    char * s; char * s_aux_1; char * s_aux_2; char * s_aux_3;
    char comando = '0';
    int fecha = 0; int aux_1, aux_2, aux_3;
    struct info * INFO = iniciaINFO();
    
    INFO->linha_atual = cabeca;

    while(!fecha){

        printf("%d,%d>", INFO->lin, INFO->col);
        s = le_Entrada();
       

        do{

            comando  = s[0];
            s = &s[1];
            

            switch (comando){

                case '!': //FECHA ARQUIVO

                    fecha = 1;
                    break;

                case 'I'://INSERE LINHA...terminar

                    if(INFO->nome_arquivo == NULL){
                        insereLinhaFim(s);
                        INFO->linha_atual = cabeca;
                    }
                    else{
                        strcpy(INFO->linha_atual->lin, insereString(INFO, s));
                        INFO->linha_atual->tam = INFO->linha_atual->tam + strlen(s) - 1;
                        
                    }

                    s = "";
                    break;

                case 'A'://ABRE ARQUIVO TXT

                    apagaTexto();
                    INFO->n_linhas = abreArquivo(s);
                    INFO->linha_atual = cabeca;
                    INFO->nome_arquivo = s;

                    s = "";
                    break;

                case 'E'://ESCREVE ARQUIVO TXT (SALVAR)

                    escreveArquivo(s);

                    s = "";
                    break;

                case 'F':// MOVE CURSOR PARA A PROXIMA COLUNA

                    if(INFO->linha_atual->tam > INFO->col){
                        INFO->col++;
                    }

                    break;

                case 'T':// MOVE CURSOR PARA A COLUNA ANTERIOR

                    if(INFO->col == 0){
                        
                        break;
                    }
                    INFO->col--;

                    break;

                case 'O':// MOVE CURSOR PARA O INICIO DA LINHA (COLUNA 0)

                    INFO->col = 0;

                    break;

                case 'P':// MOVE CURSOR PARA O INICIO DA PROXIMA PALAVRA
                    
                    INFO->col = proximaPalavra(INFO);

                    break;
                
                case 'Q':// MOVE O CURSOR O INICIO DA PALAVRA ATUAL
                    
                    INFO->col = inicioPalavra(INFO);

                    break;

                case '$':// MOVE O CURSOR O FIM DA LINHA ATUAL

                    INFO->col = INFO->linha_atual->tam;

                    break;

                case ':':// MOVE O CURSOR PARA UMA LINHA ESPECIFICA (OU ULTIMA LINHA 'F')
                   
                    if(s[0] == 'F'){
                        
                        if(INFO->lin == INFO->n_linhas -1){
                            break;
                        }
                        
                        while(INFO->lin < INFO->n_linhas-1){
                            INFO->linha_atual = INFO->linha_atual->prox;
                            INFO->lin++;
                           
                        }
                        
                    }

                    else{

                        aux_1 = atoi(s);
                        
                        if(aux_1 > INFO->lin){

                            while(INFO->lin < aux_1){

                                
                                INFO->linha_atual = INFO->linha_atual->prox;
                                INFO->lin++;
                                if(INFO->lin == INFO->n_linhas -1){
                                    break;
                                }
                            }

                        }
                        else{

                            while(INFO->lin > aux_1){
                                INFO->linha_atual = INFO->linha_atual->ant;
                                INFO->lin--;
                           
                            }

                        }

                    }

                    INFO->col = 0;

                    comando  = s[0];
                    s = &s[1];

                    break;

                case 'D'://DELETA UM CARACTERE

                    strcpy(INFO->linha_atual->lin, revomeCarectere(INFO));
                    INFO->linha_atual->tam--;

                    break;
                
                case 'M': //SALVA A POSICAO ATUAL

                    INFO->col_M = INFO->col;
                    INFO->lin_M = INFO->lin;

                    break;

                
                case 'V'://DESEMPILHA

                    if(topo != NULL){

                        s_aux_3 = Desempilha();
                        if(s_aux_3 != NULL){

                            strcpy(INFO->linha_atual->lin, insereString(INFO, s_aux_3));
                            INFO->linha_atual->tam = INFO->linha_atual->tam + strlen(s_aux_3) - 1;
                        }
                        
                    }
                    
                    s = "";
                    break;

                case 'C'://EMPILHA

                    if(INFO->col_M > INFO->col){
                        Empilha(copiaString(INFO->col_M, INFO->linha_atual->tam ,INFO->linha_atual->lin));
                    }
                    else{
                        Empilha(copiaString(INFO->col_M, INFO->col ,INFO->linha_atual->lin));
                    }
                    
                    s = "";
                    break;

                case 'X'://terminar...

                    if(INFO->col_M > INFO->col){
                        Empilha(copiaString(INFO->col_M, INFO->linha_atual->tam ,INFO->linha_atual->lin));
                        removeString(INFO->col_M, INFO->linha_atual->tam ,INFO->linha_atual->lin);
                        INFO->linha_atual->tam -= (INFO->linha_atual->tam - INFO->col_M);
                    }
                    else{
                        Empilha(copiaString(INFO->col_M, INFO->col ,INFO->linha_atual->lin));
                        removeString(INFO->col_M, INFO->col ,INFO->linha_atual->lin);
                        INFO->linha_atual->tam -= (INFO->col_M - INFO->col);
                    }
                    
                    s = "";
                    break;

                /**********/

                case 'B'://BUSCA PALAVRA NO TEXTO
    
                    aux_3 = -1;
                    aux_2 = buscaTexto(INFO, s, &aux_3);
                    
                    
                    if(aux_3 >=  INFO->col && aux_2 >= INFO->lin){

                        INFO->col = aux_3;

                        while(INFO->lin < aux_2){
                            INFO->linha_atual = INFO->linha_atual->prox;
                            INFO->lin++;
                            if(INFO->lin == INFO->n_linhas -1){
                                    break;
                                }
                        }
                    }
                    
                    
                    s = "";
                    break;

                case 'S'://terminar

                    s_aux_1 = " ";
                    s_aux_2 = " ";
                    s_aux_3 = "\0";
                    s_aux_3 =  realloc(s_aux_3, sizeof(char)*INFO->linha_atual->tam);
                    separaString(s, &s_aux_1, &s_aux_2);
                    strcpy(s_aux_3, substituiStringLinha(INFO, s_aux_1, s_aux_2));
                    printf("%s || oo \n", s_aux_3);
                    strcpy(INFO->linha_atual->lin,substituiStringLinha(INFO, s_aux_1, s_aux_2));
                    

                    /*
                    while(INFO->lin < INFO->n_linhas-1){

                        

                        strcpy(INFO->linha_atual->lin, substituiStringLinha(INFO, s_aux_1, s_aux_2));
                        INFO->linha_atual = INFO->linha_atual->prox;
                        INFO->lin++;
                           
                    }
                    
                    */
                    
                    s = "";
                    break;
                
                
                case 'N'://SEPARA A LINHA

                    insereLinha(INFO->linha_atual, copiaString(INFO->col + 1, INFO->linha_atual->tam, INFO->linha_atual->lin));
                    strcpy(INFO->linha_atual->lin, copiaString(0, INFO->col + 1, INFO->linha_atual->lin));
                    INFO->linha_atual->tam = (INFO->linha_atual->tam - INFO->col + 1);
                    INFO->n_linhas++;

                    break;

                case 'U'://UNE LINHA ATUAL COM A PROXIMA

                    strcpy(INFO->linha_atual->lin, somaStrings(INFO->linha_atual->lin, INFO->linha_atual->prox->lin));
                    removeLinha(INFO->linha_atual->prox);
                    INFO->n_linhas--;

                    break;
                

                case 'J':// MOVE CURSOR PARA A PROXIMA LINHA
                    
                    if(INFO->lin == INFO->n_linhas - 1){

                        break;
                    }

                    INFO->linha_atual = INFO->linha_atual->prox;
                    INFO->lin = INFO->lin + 1;

                    if(INFO->col > INFO->linha_atual->tam){
                        INFO->col = INFO->linha_atual->tam;
                    }
                    
                    break;

                case 'H'://MOVE CURSOR PARA LINHA ANTERIOR

                    if(INFO->lin == 0){

                        break;

                    }

                    INFO->linha_atual = INFO->linha_atual->ant;
                    INFO->lin = INFO->lin - 1;

                    if(INFO->col > INFO->linha_atual->tam){
                        INFO->col = INFO->linha_atual->tam;
                    }

                    break;

                case 'Z'://MOSTRA PILHA

                    mostraPilha();

                    s = "";
                    break;

                case 'W'://IMPRIME A VERSAO ATUAL DO TEXTO

                    printf("\n");
                    imprimeTexto();
                    printf("\n\n");

                    break;

                case '?':

                    informacao();

                    s = "";
                    break;

                case 'K':// IMPRIME INFORMACAO DO TEXTO
                    
                    if(INFO->nome_arquivo == NULL) INFO->nome_arquivo = " "; 
                    printf("nome do arquivo: %s\n", INFO->nome_arquivo);
                    printf("linha: %d; coluna: %d\n", INFO->lin, INFO->col);
                    printf("posicao salva - linha: %d; coluna: %d\n", INFO->lin_M, INFO->col_M);
                    printf("numero de linhas: %d\n\n", INFO->n_linhas);

                    s = "";
                    break;
                
                default:

                    break;
            }

            if(fecha == 1){
                printf("^\n");
                return;
            }

        }while(strlen(s) > 0);
        imprimeLinhaAtual(INFO);

    }
    
    fechaPrograma(INFO);
    
}

/******************************************/

int main(){

    
    fazabertura();
    Iteracao_do_Programa();
    
    


    return 0;
}