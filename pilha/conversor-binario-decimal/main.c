#include <stdio.h>
#include <stdlib.h>

typedef struct info{
    char c;
}SInfo;

typedef struct nodo{
    SInfo conteudo;
    struct nodo *pPrevius;
}SNodo;

typedef struct stack{
    SNodo *topo;
} SStack;

void lerString(SStack *pilha);
void push(SStack *pilha, char c);
int empty(SStack *pilha);
int pop(SStack *pilha);

int main(){
    //inicializa a pilha
    SStack *pilha;
    pilha = (SStack *)malloc(sizeof(SStack));
    pilha->topo = NULL;
    //
    int resul = 0;

    printf("NUmero: ");
    lerString(pilha);

    //calcula
    for(int i = 1; !empty(pilha); i *= 2){
        if(pop(pilha))
            resul += i;
    }
    //
    printf("Resultado: %d\n", resul);

    free(pilha);
    return 0;
}

void lerString(SStack *pilha){
    char c;
    while((c = getchar()) != '\n'){
        if(c == '0' || c == '1')
            push(pilha, c);
    }
}

void push(SStack *pilha, char c){
    SNodo *new;
    new = (SNodo *)malloc(sizeof(SNodo));
    new->conteudo.c = c;

    if(!pilha->topo){       //pilha vazia
        new->pPrevius = NULL;
        pilha->topo = new;
    }
    else{
        SNodo *ult;
        ult = pilha->topo;
        new->pPrevius = ult;

        pilha->topo = new;
    }
}

int empty(SStack *pilha){
    if(!pilha->topo)
        return 1;
    else
        return 0;
}

int pop(SStack *pilha){
    SNodo *ult, *newUlt;

    ult = pilha->topo;
    newUlt = ult->pPrevius;
    pilha->topo = newUlt;

    if(ult->conteudo.c == '0'){
        free(ult);
        return 0;
    }
    else{
        free(ult);
        return 1;
    }

}