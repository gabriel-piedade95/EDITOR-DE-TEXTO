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
    int linha= 0;
    int coluna = 0;

    while(!fecha){

        printf("<%d,%d>", linha, coluna);
        s = le_Entrada();

        do{

            comando  = s[0];
            s = &s[1];

            switch (comando)
            {
            case '!':
                fecha = 1;
                break;

            case 'I':
                insereLinhaFim(s);
                imprimeTexto();
                break;

            case 'A':
                abreArquivo(s);
                imprimeTexto();
                break;
            
            default:
                break;
            }



        }while(strlen(s) > 0);
   
    }
    
    
    

}

/******************************************/

int main(){

    
    fazabertura();
    Iteracao_do_Programa();

    


    return 0;
}