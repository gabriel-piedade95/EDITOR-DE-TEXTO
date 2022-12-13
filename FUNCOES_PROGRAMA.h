#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************/

char * le_Entrada(){

    char *string = NULL;
    int letra;
    size_t s = 0 , tam = 0;

    while ((letra=getchar()) != EOF && letra != '\n') {
        if (tam + 1 >= s)
        {
            s = s * 2 + 1;
            string = realloc(string, sizeof(char)*s);
        }
        string[tam++] = letra;
    }
    if (string != NULL) {
        string[tam] = '\0';
        return string;
    }

    return "\n";
}

/**************** ABRE ARQUIVO *************/

char * leLinhaTexto(FILE * arq){

    char *string = NULL;
    int letra;
    size_t s = 0 , tam = 0;

    while ((letra=fgetc(arq)) != EOF && letra != '\n') {
        if (tam + 1 >= s)
        {
            s = s * 2 + 1;
            string = realloc(string, sizeof(char)*s);
        }
        string[tam++] = letra;
    }
    if (string != NULL) {
        string[tam] = '\0';
        return string;
    }

    return NULL;
}
void abreArquivo(char * nomeArquivo){

    FILE * arquivo;
    char * string = NULL;


    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
        exit(1);

    while((string = leLinhaTexto(arquivo)) != NULL){
        insereLinhaFim(string);
    }
    
    fclose(arquivo);

}

/* *************************************** */