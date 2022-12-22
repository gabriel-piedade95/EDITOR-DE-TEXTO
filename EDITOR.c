#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ESTRUTURAS.h"
#include "FUNCOES_PROGRAMA.h"


void fazabertura() {// faz abertura do programa com algumas informacoes

	printf("****************************************************************\n");
    printf("*                                                              *\n");
	printf("*            ***      ~EDITOR DE TEXTO~      ***               *\n");
    printf("*                                                              *\n");
	printf("****************************************************************\n");
    printf("> GABRIEL PIEDADE - nUSP8927356 <\n");
    printf("> Aperte ? para ver a lista de comandos< \n\n");

}

//IMPRIME LINHA ATUAL 
void imprimeLinhaAtual(struct linha * linha_atual, int col, int col_M, int lin, int lin_M, int salva){
    
    int i;
    if(linha_atual == NULL){// se a linha for nula pular linha

        printf("\n");
        printf("^\n\n");

    }
    else{// caso contrario imprime a linha

        printf("%s\n", linha_atual->lin);
        char s[linha_atual->tam+2];
        for(i = 0; i < linha_atual->tam+2; i++){
            s[i] = ' ';// cria uma string com espacos ' '
        }
        s[linha_atual->tam+2] = '\0';
        if (salva == 1 && lin == lin_M) s[col_M] = 'M';// coloca M na posicao anterior
        s[col] = '^';// coloca ^ na posica do ponteiro
        printf("%s\n\n", s);// imprime a linha de baixo com o ponteiro e a posicao anterior
    }
    
        
}

void fechaPrograma(){// libera a memoria alocada pelo texto e pela pilha
    
    apagaTexto();
    apagaPilha();
    

}


void Iteracao_do_Programa(){

    //VARAIVEIS AUXILIARES USADAS NO PROGRAMA
    char * s; char * s_aux_1; char * s_aux_2; char * s_aux_3; char * s_aux_4;
    char comando = '0';
    int fecha = 0; int salva = 0;
    int aux_1, aux_2, aux_3;
    struct linha * linha_aux;
    

    //INFORMACOES DO PROGRAMA
    int lin = 0;
    int col = 0;
    int lin_M = 0;
    int n_linhas = 0;
    int col_M = 0;
    char * nome_arquivo = NULL;
    struct linha * linha_atual;

    while(!fecha){// o programa roda enquanto a variavel fecha for igual a 0


        printf("%d,%d>", lin, col); // imprime o mostrador da posicao no texto
        s = le_Entrada();// s eh uma string que recebe o comando digitado pelo usuario
       

        do{// loop que 'desenfilera' a string s e realiza os comandos digitados

            comando  = s[0];// a primeira letra da string s eh recebida como um comando
            s = &s[1];// o ponteiro de s passa para a proxima letra da string
            

            switch (comando){

                case '!': //FECHA ARQUIVO

                    fecha = 1;
                    break;

                case 'I'://INSERE LINHA

                    if(nome_arquivo == NULL){// se o arquivo for vazio insere o texto no inicio
                        insereLinhaFim(s);
                        linha_atual = cabeca;
                        linha_atual->tam = strlen(s);
                    }
                    else{// caso contrario insere o texto na posicao atual do ponteiro
                        strcpy(linha_atual->lin, insereString(col, linha_atual, s));
                        linha_atual->tam = linha_atual->tam + strlen(s);
                        
                    }

                    s = "";
                    break;

                case 'A'://ABRE ARQUIVO TXT

                    apagaTexto();// apaga o texto anterior, caso ele exista
                    n_linhas = abreArquivo(s);// essa funcao abre o arquivo (colocando ele na lista ligada) e devolve o numero de linhas do texto
                    linha_atual = cabeca;
                    nome_arquivo = s;

                    s = "";
                    break;

                case 'E'://ESCREVE ARQUIVO TXT (SALVAR)

                    escreveArquivo(s);

                    s = "";
                    break;

                case 'F':// MOVE CURSOR PARA A PROXIMA COLUNA

                    if(linha_atual->tam > col){
                        col++;
                    }

                    break;

                case 'T':// MOVE CURSOR PARA A COLUNA ANTERIOR

                    if(col == 0){
                        
                        break;
                    }
                    col--;

                    break;

                case 'O':// MOVE CURSOR PARA O INICIO DA LINHA (COLUNA 0)

                    col = 0;

                    break;

                case 'P':// MOVE CURSOR PARA O INICIO DA PROXIMA PALAVRA
                    
                    col = proximaPalavra(col, linha_atual);// ver FUNCOES_PROGRAMA.h

                    break;
                
                case 'Q':// MOVE O CURSOR O INICIO DA PALAVRA ATUAL
                    
                    col = inicioPalavra(col, linha_atual);// ver FUNCOES_PROGRAMA.h

                    break;

                case '$':// MOVE O CURSOR O FIM DA LINHA ATUAL

                    col = linha_atual->tam;

                    break;

                case ':':// MOVE O CURSOR PARA UMA LINHA ESPECIFICA (OU ULTIMA LINHA 'F')
                   
                    if(s[0] == 'F'){// se o comando for ':F' o ponteiro vai para a ultima linha do texto
                        
                        if(lin == n_linhas -1){// se ja estiver no final nao faz nada
                            break;
                        }
                        
                        while(lin < n_linhas-1){// caso contrario desce ate o fim do texto
                            linha_atual = linha_atual->prox;
                            lin++;
                           
                        }
                        
                    }

                    else{// se o comando for ':x', onde x eh um  inteiro, o ponteiro vai para a linha x

                        aux_1 = atoi(s);//transforma a string s em um inteiro  
                        
                        if(aux_1 > lin){// se x for maior que a linha atual vamos para a proxima linha ate achar x

                            while(lin < aux_1){

                                
                                linha_atual = linha_atual->prox;
                                lin++;
                                if(lin == n_linhas - 1){
                                    break;
                                }
                            }

                        }
                        else{// se x for menor que a linha atual vamos para a linha anterior ate achar x

                            while(lin > aux_1){
                                linha_atual = linha_atual->ant;
                                lin--;
                           
                            }

                        }

                    }

                    col = 0;// posicao do ponteiro para inicio da linha

                    
                    s = "";
                    break;

                case 'D'://DELETA UM CARACTERE

                    if(col == linha_atual->tam){// protege a ultima posicao da string
                        break;
                    }
                    strcpy(linha_atual->lin, revomeCarectere(linha_atual, col));// ver FUNCOES_PROGRAMA.h
                    linha_atual->tam--;

                    break;
                
                case 'M': //SALVA A POSICAO ATUAL

                    col_M = col;
                    lin_M = lin;
                    salva = 1;

                    break;

                
                case 'V'://DESEMPILHA 

                    if(topo != NULL){

                        s_aux_2 = Desempilha();// ver ESTRUTURAS.h
                        if(s_aux_2 != NULL){

                            strcpy(linha_atual->lin, insereString(col, linha_atual ,s_aux_2));// ver FUNCOES_PROGRAMA.h
                            linha_atual->tam = linha_atual->tam + strlen(s_aux_2) - 1;
                        }
                        
                    }
                    
                    s = "";
                    break;

                case 'C'://EMPILHA

                    if(col_M > col){// ver ESTRUTURAS.h e FUNCOES_PROGRAMA.h
                        Empilha(copiaString(col_M, linha_atual->tam ,linha_atual->lin));
                    }
                    else{
                        Empilha(copiaString(col_M, col, linha_atual->lin));
                    }
                    
                    s = "";
                    break;

                case 'X'://EMPILHA E EXCLUI 


                    if(col_M > col){// ver ESTRUTURAS.h e FUNCOES_PROGRAMA.h
                        Empilha(copiaString(col_M, linha_atual->tam ,linha_atual->lin));
                        removeString(col_M, linha_atual->tam ,linha_atual->lin);
                        linha_atual->tam -= (linha_atual->tam - col_M);
                    }
                    else{
                        Empilha(copiaString(col_M, col ,linha_atual->lin));
                        removeString(col_M, col ,linha_atual->lin);
                        linha_atual->tam -= (col_M - col);
                    }
                    
                    s = "";
                    break;


                case 'B'://BUSCA PALAVRA NO TEXTO

                    
                    aux_1 = buscaLinha(col, s, linha_atual->lin);
                    linha_aux = linha_atual;
                    aux_2 = lin;
                    while(aux_1 == -1 && aux_2 < n_linhas -1){

                        linha_aux = linha_aux->prox;
                        aux_2++;
                        aux_1 = buscaLinha(0, s, linha_aux->lin);
                    }

                    if(aux_1 != -1){
                        col = aux_1;
                        lin = aux_2;
                        linha_atual = linha_aux;
                    }  
                    s = "";
                    break;
                    
                    

                case 'S'://(Ss/r) SUBSTITUI A STRING s PELA STRING r EM TODO O TEXTO 

                    //separa as palavras
                    aux_3 = buscaLinha(0, "/", s);
                    s_aux_1 = copiaString(0, aux_3, s);
                    s_aux_2 = copiaString(aux_3 + 1, strlen(s), s);
                    
                    //substitui
                    linha_aux = cabeca;
                    aux_2 = 0;

                  

                    aux_1 = buscaLinha(0, s_aux_1, linha_aux->lin);
                    while(aux_1 != -1){
                        s_aux_3 = copiaString(0, aux_1, linha_atual->lin);
                        s_aux_3 = somaStrings(s_aux_3, s_aux_2);
                        s_aux_4 = copiaString(aux_1 + strlen(s_aux_1), strlen(linha_atual->lin), linha_atual->lin);
                        linha_aux->lin = somaStrings(s_aux_3, s_aux_4);
                        aux_1 = buscaLinha(0, s_aux_1, linha_aux->lin);
                    }

                    
                     


                    s = "";
                    break;
                
                
                case 'N'://SEPARA A LINHA 

                    insereLinha(linha_atual, copiaString(col + 1, linha_atual->tam, linha_atual->lin));// insere essa string em uma nova linha
                    strcpy(linha_atual->lin, copiaString(0, col + 1, linha_atual->lin)); // copia a string a partir ate o ponteiro
                    linha_atual->tam = (linha_atual->tam - col + 1);
                    n_linhas++;

                    break;

                case 'U'://UNE LINHA ATUAL COM A PROXIMA

                    if(linha_atual->prox != NULL){

                        strcpy(linha_atual->lin, somaStrings(linha_atual->lin, linha_atual->prox->lin));// une a linha atual com a linha de baixo
                        removeLinha(linha_atual->prox);// remove a linha de baixo
                        n_linhas--;

                    }
                    

                    break;
                

                case 'J':// MOVE CURSOR PARA A PROXIMA LINHA
                    
                    if(lin == n_linhas - 1){// se ja estiver no fim nao faz nada

                        break;
                    }
                    // caso contrario volta move para a proxima linha
                    linha_atual = linha_atual->prox;
                    lin++;

                    if(col > linha_atual->tam){// atualiza a coluna para a posicao possivel
                        col = linha_atual->tam;
                    }
                    
                    break;

                case 'H'://MOVE CURSOR PARA LINHA ANTERIOR

                    if(lin == 0){// se ja estiver no inicio nao faz nada

                        break;

                    }
                    // caso contrario volta move para a linha anterior
                    linha_atual = linha_atual->ant;
                    lin--;

                    if(col > linha_atual->tam){// atualiza a coluna para a posicao possivel
                        col = linha_atual->tam;
                    }

                    break;

                case 'Z'://MOSTRA PILHA 

                    mostraPilha();

                    s = "";
                    break;

                case 'W'://IMPRIME A VERSAO ATUAL DO TEXTO

                    printf("\n");
                    imprimeTexto();// ver ESTRUTURAS.h
                    printf("\n\n");

                    break;

                case '?'://IMPRIME INFORMACOES SOBRE TODOS OS COMANDOS DO EDITOR

                    informacao();// ver FUNCOES_PROGRAMA.h

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
        imprimeLinhaAtual(linha_atual, col, col_M, lin, lin_M, salva);

    }
    
    free(s);// libera a string s
    free(linha_aux);// libera linha auxiliar
    fechaPrograma();// libera a pilha e a lista lista ligada (texto)
    
}

/******************************************/

int main(){

    
    fazabertura();// chama a abertura
    Iteracao_do_Programa();// realiza o loop do programa ate ser dado o comando '!'
    
    


    return 0;
}