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

    while ((letra=fgetc(arq)) != EOF) {
        if (tam + 1 >= s)
        {
            s = s * 2 + 1;
            string = realloc(string, sizeof(char)*s);
        }
        if(letra == '\n'){
            break;
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

    if (arquivo == NULL){
        printf("ERRO:  Arquivo '%s' nao encontrado!\n", nomeArquivo);
        exit(1);
    }
        
        

    while((string = leLinhaTexto(arquivo)) != NULL){
        
        insereLinhaFim(string);
        tam++;
    }
    
    fclose(arquivo);

    return tam;

}

void escreveArquivo(char * nomeArquivo){

    FILE * arquivo;
    struct linha * aux = cabeca;

    arquivo = fopen(nomeArquivo, "w");
    

    while(aux != NULL){
        
        fprintf(arquivo, "%s\n", aux->lin);
        aux = aux->prox;
        
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

void removeString(int inicio, int fim, char * s){

    char * aux1 = copiaString(0, inicio + 1, s);
    char * aux2 = copiaString(fim, strlen(s), s);
    strcpy(s, somaStrings(aux1, aux2));
    

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

void separaString(char * s, char ** aux1, char ** aux2){

    int tam_s = strlen(s);
    int pos;

    pos = buscaLinha("/", s);
    *aux1 = copiaString(0, pos, s);
    *aux2 = copiaString(pos + 1, tam_s, s);

}


char * substituiStringLinha(struct info * I, char * a, char * b){

    char * s = I->linha_atual->lin;
    int pos = buscaLinha(a, s);

    if(pos != -1){
        char * aux1 = copiaString(0, pos, s);
        char * aux2 = copiaString(pos + strlen(a), strlen(s), s);

        

        strcpy(aux1, somaStrings(aux1, b));
        strcpy(aux2, somaStrings(aux1, aux2));
        
        return aux2;
    }

    return "\0";
    

}

void informacao(){

    printf("\n~> LISTA DE COMANDOS <~\n\n");

    printf("MANIPULACAO ARQUIVO:\n");
    printf("An -> Carrega o conteudo do arquivo de texto de nome n no editor\n");
    printf("En -> (Sobre)escreve o conteudo do editor no arquivo de texto de nome n\n\n");

    printf("MOVIMENTO CURSOR:\n");
    printf("F -> Move o cursor um caractere a frente\n");
    printf("T -> Move o cursor um caractere para tras\n");
    printf("0 -> Move o cursor para o inicio da linha atual\n");
    printf("P -> Move cursor para inicio da proxima palavra (dentro da mesma linha)\n");
    printf("Q -> Move cursor para inicio da palavra atual\n");
    printf("$ -> Move o cursor para o fim da linha atual\n");
    printf(":x -> Move o cursor para o inicio da linha x\n");
    printf(":F -> Move o cursor para a ultima linha do arquivo\n");
    printf("J -> Ir para proxima linha \n");
    printf("H -> Ir para a linha anterior\n\n");

    printf("MANIPULACAO STRING:\n");
    printf("Is -> Insere a string s na posicao atual do texto\n");
    printf("D -> Apaga o caractere da posicao atual\n");
    printf("Ss/r -> Substitui toda ocorrencia de s por r no texto a partir da posicao atual\n");
    printf("Bs -> Busca pela proxima ocorrencia do padrao s no texto\n");
    printf("N -> Separa linha atual na posicao do cursor\n");
    printf("U -> Unir linha atual e a proxima\n\n");

    printf("PILHA STRING\n");
    printf("V -> Desempilha e insere o conteudo do topo pilha na posicao atual\n");
    printf("C -> Empilha o texto entre a posicao marcada e a posicao atual \n");
    printf("X -> Empilha o texto entre a posicao marcada e a posicao atual e o deleta\n");
    printf("M -> Marca a posicao atual do cursor\n\n");


    printf("PROGRAMA:\n");
    printf("! -> Encerra o programa\n");
    printf("Z -> Exibe a pilha de memoria, comecando pelo topo\n");
    printf("W -> Imprime versao atual do texto\n");
    printf("K -> Imprime informacoes sobre o texto\n\n\n");

}
