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
int abreArquivo(char * nomeArquivo){

    FILE * arquivo;
    char * string = NULL;
    int tam = 0;

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
        exit(1);

    while((string = leLinhaTexto(arquivo)) != NULL){
        insereLinhaFim(string);
        tam++;
    }
    
    fclose(arquivo);

    return tam;

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

int inicioPalavra(struct info * I){

    if(I->col == 0){
        return 0;
    }

    int posicao = I->col;
    int aux = 0;
    char * s = I->linha_atual->lin;
    char c = s[posicao];

    while(c == ' '){
        posicao--;
        c = s[posicao];
    }

    while(c != ' ' && aux != 1){

        if (c == ' '){
            aux = 1;
        }
        posicao--;
        c = s[posicao];

    }


    return posicao + 1;

}

char * revomeCarectere(struct info * I){

    char * nova_s = malloc(sizeof (char) * I->linha_atual->tam );
    int pos = 0;
    int aux = 0;
    while(pos < I->col){
        
        nova_s[pos++] = I->linha_atual->lin[aux++];
    }

    aux++;

    while(pos < I->linha_atual->tam){
        
        nova_s[pos++] = I->linha_atual->lin[aux++];   
    }

    return nova_s;

}

char * copiaString(int inicio, int fim, char * s){


    char * nova_s = malloc(sizeof (char) * (fim - inicio));
    int i;
    for (i = 0; i < (fim - inicio); i++){
        nova_s[i] = s[i + inicio];
    }
    nova_s[i] = '\0';

    return nova_s;

}

char * somaStrings(char * s1, char * s2){

    char * nova_s = malloc(sizeof (char) * (strlen(s1) + strlen(s2) - 1));
    int i = 0;
    int j = 0;

    while(s1[i] != '\0'){
        nova_s[j] = s1[i];
        i++; j++;
    }

    i = 0;

    while(s2[i] != '\0'){
        nova_s[j] = s2[i];
        i++; j++;
    }

    nova_s[j] = '\0';

    return nova_s;
}

char * insereString(struct info * I, char * s){

    
    char * aux1 = copiaString(0, I->col + 1, I->linha_atual->lin);
    char * aux2 = copiaString(I->col + 1, I->linha_atual->tam, I->linha_atual->lin);
    strcpy(aux1, somaStrings(aux1, s));
    strcpy(aux2, somaStrings(aux1, aux2));

    return aux2;
}

/******************************************/

int buscaLinha (char * p, char * t) 
{
   
   int i, k;
   int m = strlen(p);
   int n = strlen(t);
   for (k = 0; k <= n-m; ++k) {
      for (i = 0; i < m && p[i] == t[i+k]; i++); 
      if (i == m) {
        return k;
      }
   }

   return -1;
   
}

int buscaTexto(struct info * I, char * s, int * achou){

    struct linha * l_aux = cabeca;
    int l = I->lin;

    while(l_aux != NULL){
        *achou = buscaLinha(s, l_aux->lin);
        l_aux = l_aux->prox;
        
        if (*achou != -1){
            break;
        }
        l++;
    }
    

    return l;

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