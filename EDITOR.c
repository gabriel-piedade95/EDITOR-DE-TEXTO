#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ESTRUTURAS.h"
#include "FUNCOES_PROGRAMA.h"



void fazabertura() {

	printf("****************************\n");
	printf("*      EDITOR DE TEXTO     *\n");
	printf("****************************\n");
	printf("\n");
}


void imprimeLinhaAtual(struct info * I){
    
    int i;
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

void fechaPrograma(struct info * I){
    
    liberaINFO(I);
}


void Iteracao_do_Programa(){


    char * s;
    char comando = '0';
    int fecha = 0;
    struct info * INFO = iniciaINFO();
    INFO->linha_atual = cabeca;
    int aux_1 = 0;

    while(!fecha){

        printf("%d,%d>", INFO->lin, INFO->col);
        s = le_Entrada();
       

        do{

            comando  = s[0];
            s = &s[1];
            

            switch (comando){

                case '!': 

                    fecha = 1;
                    break;

                case 'I':
                    insereLinhaFim(s);// fazer ainda!!!
                    INFO->linha_atual = cabeca;
                    s = "";

                    break;

                case 'A':

                    INFO->n_linhas = abreArquivo(s);
                    INFO->linha_atual = cabeca;
                    INFO->nome_arquivo = s;
                    s = "";
                    break;

                case 'F':

                    if(INFO->linha_atual->tam > INFO->col){
                        INFO->col++;
                    }
                    break;

                case 'T':

                    if(INFO->col > 0){
                        INFO->col--;
                    }
                    break;

                case 'O':

                    INFO->col = 0;
                    break;

                case 'P':
                    
                    INFO->col = proximaPalavra(INFO);
                    break;
                
                case 'Q':
                    
                    INFO->col = inicioPalavra(INFO);
                    break;

                case '$':
                    INFO->col = INFO->linha_atual->tam;
                    break;

                case ':':
                   
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
                        if(aux_1 == INFO->lin){

                        }
                        else if(aux_1 > INFO->lin){

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

                case 'D':
                    strcpy(INFO->linha_atual->lin, revomeCarectere(INFO));
                    INFO->linha_atual->tam--;
                    break;
                
                case 'M':

                    INFO->col_M = INFO->col;
                    break;

                /*FAZER*/
                case 'V':
                    break;

                case 'C':
                    break;

                case 'X':
                    break;
                
                case 'B':
                    break;

                case 'S':
                    break;

                case 'N':
                    break;

                case 'U':
                    break;
                /********/

                case 'J':
                    
                    if(INFO->lin == INFO->n_linhas - 1){
                        break;
                    }

                    INFO->linha_atual = INFO->linha_atual->prox;
                    INFO->lin = INFO->lin + 1;

                    if(INFO->col > INFO->linha_atual->tam){
                        INFO->col = INFO->linha_atual->tam;
                    }


                    
                    break;

                case 'H':

                    if(INFO->lin == 0){
                        break;
                    }

                    INFO->linha_atual = INFO->linha_atual->ant;
                    INFO->lin = INFO->lin - 1;

                    if(INFO->col > INFO->linha_atual->tam){
                        INFO->col = INFO->linha_atual->tam;
                    }

                    break;

                case 'Z'://fazer!!!
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