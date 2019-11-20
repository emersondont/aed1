/*
Escreva um programa solicite ao usuário uma sequência de caracteres sem limite máximo 
de tamanho e realize as seguintes operações usando uma pilha:
a) Imprimir o texto na ordem inversa;
b) Verificar se o texto é um palíndromo
*/

//ATENCAO, ESTE CODIGO ESTÁ UMA BAGUNÇA
//super desorganizado, e não funciona com frases

#include <stdio.h>
#include <stdlib.h>

typedef struct info{
    char c;
}SInfo;

typedef struct nodo{
    SInfo conteudo;
    struct nodo *previus;
}SNodo;

typedef struct stack{
    SNodo *topo;
} SStack;

void push(SStack *pilha, char c);
int empty(SStack *pilha);
SNodo *pop(SStack *pilha);
void clean(SStack *pilha);
void lerString(SStack *pilha, int *tam);
void imprimirAoContrario(SStack *pilha);
int verificador(SStack *pilha, int *tam);

int main(){
    int tam = 0;
    //inicializa a pilha
    SStack *pilha;
    pilha = (SStack *)malloc(sizeof(SStack));
    pilha->topo = NULL;
    //
    printf("Palavra.....: ");
    lerString(pilha, &tam);
    printf("Ao contrario: ");
    imprimirAoContrario(pilha);

    if(verificador(pilha, &tam))
        printf("\tEh palindromo\n");
    else
        printf("\tNao eh palindromo\n");

    
    clean(pilha);
    free(pilha);
    return 0;
}

void lerString(SStack *pilha, int *tam){
    char c;
    while((c = getchar()) != '\n'){
        *tam += 1;
        push(pilha, c);
    }
}

void push(SStack *pilha, char c){
    SNodo *new;
    new = (SNodo *)malloc(sizeof(SNodo));
    new->conteudo.c = c;

    if(!pilha->topo){       //pilha vazia
        new->previus = NULL;
        pilha->topo = new;
    }
    else{
        SNodo *ult;
        ult = pilha->topo;
        new->previus = ult;

        pilha->topo = new;
    }
}

int empty(SStack *pilha){
    if(!pilha->topo)
        return 1;
    else
        return 0;
}

SNodo *pop(SStack *pilha){
    if(!pilha->topo){       //pilha vazia
        return NULL;
    }
    SNodo *ult, *newUlt;

    ult = pilha->topo;
    newUlt = ult->previus;
    pilha->topo = newUlt;

    return ult;
}

void clean(SStack *pilha){
    SNodo *clear;
    while(clear = pop(pilha))
        free(clear);
}

void imprimirAoContrario(SStack *pilha){
    SStack *pilhaAux;
    pilhaAux = (SStack *)malloc(sizeof(SStack));
    pilhaAux->topo = NULL;

    SNodo *aux;
    while(!empty(pilha)){
        aux = pop(pilha);
        printf("%c", aux->conteudo.c);
        push(pilhaAux, aux->conteudo.c);
        free(aux);
    }
    printf("\n");

    while(!empty(pilhaAux)){
        aux = pop(pilhaAux);
        push(pilha, aux->conteudo.c);
        free(aux);
    }
    free(pilhaAux);
}

int verificador(SStack *pilha, int *tam){
    SStack *pilhaAux;
    pilhaAux = (SStack *)malloc(sizeof(SStack));
    pilhaAux->topo = NULL;

    SNodo *aux, *c1, *c2;
    int verif = 1;

    for(int i = 0; i < *tam / 2; i++){
        aux = pop(pilha);
        push(pilhaAux, aux->conteudo.c);
        free(aux);
    }
    if(*tam % 2 == 1){
        aux = pop(pilha);
        free(aux);
    }

    for(int i = 0; i < *tam / 2; i++){
        c1 = pop(pilha);
        c2 = pop(pilhaAux);
        if((c1->conteudo.c != c2->conteudo.c)){
            verif = 0;
            break;
        }
        free(c1);
        free(c2);
    }

    free(pilhaAux);

    return verif;
}
