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
    char s[I->linha_atual->tam];
    for(i = 0; i < I->linha_atual->tam; i++){
        s[i] = ' ';
    }
    s[I->linha_atual->tam] = '\0';
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
    

    while(!fecha){

        printf("%d,%d>", INFO->lin, INFO->col);
        s = le_Entrada();
       

        do{

            comando  = s[0];
            s = &s[1];
            

            switch (comando){

                case '!': //fecha o arquivo

                    fecha = 1;
                    break;

                case 'I':
                    insereLinhaFim(s);// fazer ainda!!!
                    INFO->linha_atual = cabeca;
                    s = "";

                    break;

                case 'A':

                    abreArquivo(s, INFO->n_linhas);
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
                    //break;
                
                case 'Q':
                    //inicio da palavra atual
                    break;

                case '$':
                    //fim da linha atual
                    break;

                case ':':
                    if(s[0] == 'F'){
                        //ultima linha
                    }
                    else{
                        //linha x
                    }

                    break;

                case 'D':
                    //apaga caractere
                    break;
                
                case 'M':

                    INFO->col_M = INFO->col;
                    break;

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

                case 'J':
                    break;

                case 'H':
                    break;

                case 'Z':
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