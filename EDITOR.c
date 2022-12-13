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
                    //insereLinhaFim(" ");
                    break;

                case 'I':
                    insereLinhaFim(s);
                    imprimeTexto();
                    break;

                case 'A':
                    abreArquivo(s);
                    INFO->linha_atual = cabeca;
                    //INFO->n_linhas = conta_linha();
                    INFO->nome_arquivo = s;
                    s = "";
                    break;

                case 'F':
                    INFO->col++;
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
                    //proxima palavra
                    break;
                
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

                
                default:
                    break;
            }

            if(fecha == 1){
                printf("^\n");
                return;
            }

            printf("%s\n", INFO->linha_atual->lin);
            printf("^\n\n");


        }while(strlen(s) > 0);
   
    }
    
    //fechaPrograma(INFO);
    

}

/******************************************/

int main(){

    
    fazabertura();
    Iteracao_do_Programa();

    


    return 0;
}