#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************  LE ENTRADA  *****************/

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
/* *************************************** */


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
void abreArquivo(char * nomeArquivo, int tam){

    FILE * arquivo;
    char * string = NULL;


    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
        exit(1);

    while((string = leLinhaTexto(arquivo)) != NULL){
        insereLinhaFim(string);
        tam++;
    }
    
    fclose(arquivo);

}

/* *************************************** */


/* *********** ALTERA LINHAS  ************ */

int proximaPalavra(struct info * I){

    
    int posicao = I->col;
    int aux = 0;
    char * s = I->linha_atual->lin;
    char c = s[posicao];

    while(c != ' ' && aux != 1){

        if (c == ' '){
            aux = 1;
        }
        posicao++;
        c = s[posicao];

    }

    if(posicao >= I->linha_atual->tam){
        return I->col;
    }


    return posicao + 1;
}

void busca_em_texto (char * p, char * t) 
{
   
   int i, ocorrencias = 0;
   int m = strlen(p);
   int n = strlen(t);
   for (int k = 0; k <= n-m; ++k) {
      for (i = 0; i < m && p[i] == t[i+k]; i++); 
      if (i == m) {
        ++ocorrencias;
        printf("%d\n", k);
      }
   }
   
}

/* Recebe a string b e seu tamanho n, string a e seu tamanho m, string x e seu tamanho p, e uma string nova;
   Altere essa funcao para que ela coloque em nova o resultado de substituir em b as ocorrencias de a por x. */
void substituir(char b[], int n, char a[], int m, char x[], int p, char* nova){
    
    int pivo1, pivo2, pivo_a, pivo_nova, tam;
    
    pivo1 = 0;
    tam = 0;
    pivo_a = 0;
    pivo_nova = 0;
    
    //encontra a posicao de onde deve ser trocado
    
    while(pivo1 < n){
        
        
        for(pivo2 = pivo1, pivo_a = 0; pivo2 < (pivo1 + m); pivo2++, pivo_a++){
            
            if(b[pivo2] == a[pivo_a]){
                tam++;
                
            }
            
            
        }
        
        if(tam == m){
            
            strcpy(&nova[pivo_nova], x);
            pivo_nova += p;
            pivo1 += m;
            n += (p-m) + 1;
            
            
        }
        
        else{
            
            
            nova[pivo_nova] = b[pivo1];
            pivo_nova++;
            pivo1++;
            
        }
        tam = 0;
        
    }
    
    nova[pivo1] = '\0';
    
 
}

/* *************************************** */