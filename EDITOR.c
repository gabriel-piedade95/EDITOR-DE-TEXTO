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


void Iteracao_do_Programa(){


    char * s;
    char comando = '0';
    int fecha = 0;
    struct info * INFO = iniciaINFO();
    printf("%d,%d>", INFO->lin, INFO->col);

    while(!fecha){

        
        s = le_Entrada();
       

        do{

            comando  = s[0];
            s = &s[1];
            

            switch (comando)
            {
            case '!': //fecha o arquivo
                fecha = 1;
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
        printf("%s\n", INFO->linha_atual->lin);
        printf("^\n\n");
        printf("%d,%d>", INFO->lin, INFO->col);


        }while(strlen(s) > 0);
   
    }
    
    
    

}

/******************************************/

int main(){

    
    fazabertura();
    Iteracao_do_Programa();

    


    return 0;
}