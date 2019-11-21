/*
Escreva um programa que simule o controle de uma pista de decolagem de aviões de em um aeroporto.
Neste programa, o usuario deve ser capaz de realizar as seguintes tarefas:
a) Listar o número de aviões aguardando na fila de decolagem;
b) Autorizar a decolagem do primeiro avião da fila;
c) Adicionar um avião à fila de espera;
d) Listar todos os aviões na fila de espera;
e) Listar as características do primeiro avião da fila
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void lerString(char *c);
Nodo *lerDados(void);

int main(){
    Queue *fila = NULL;
    fila = inicializa();

    push(fila, lerDados());
    push(fila, lerDados());

    printf("%s \n", pop(fila)->conteudo.nomeAviao);
    printf("%s \n", pop(fila)->conteudo.nomeAviao);


    clean(fila);
    free(fila);
    return 0;
}

void lerString(char *c){
    while((*c = getchar()) != '\n')
        c++;
}

Nodo *lerDados(void){
    Nodo *new = NULL;
    new = (Nodo *)malloc(sizeof(Nodo));
    new->next = NULL;
    new->previus = NULL;

    printf("Nome do aviao: ");
    lerString(new->conteudo.nomeAviao);
    printf("Capacidade: ");
    scanf("%d", &new->conteudo.capacidade);

    return new;
}


//FUNCOES QUEUE
Queue *inicializa(void){
    Queue *fila = NULL;

    if((fila = (Queue *)malloc(sizeof(Queue))) == NULL){
        printf("ERRO AO CRIAR FILA\n");
        exit(1);
    }
    fila->first = NULL;
    fila->last = NULL;

    return fila;
}

void push(Queue *fila, Nodo *new){
    if(!empty(fila)){    //fila vazia
        new->next = NULL;
        new->previus = NULL;
        fila->first = new;
        fila->last = new;
        return;
    }

    Nodo *ultimo = NULL;
    ultimo = fila->last;
    ultimo->next = new;
    new->previus = ultimo;
    new->next = NULL;

    fila->last = new;
}

Nodo *pop(Queue *fila){
    if(!empty(fila)){
        printf("Fila vazia\n");
        return NULL;
    }

    Nodo *primeiro = NULL;
    Nodo *newPrimeiro = NULL;

    primeiro = fila->first;
    newPrimeiro = primeiro->next;
    newPrimeiro->previus = NULL;
    fila->first = newPrimeiro;

    primeiro->next = NULL; //limpa pra quem o primeiro apontava

    return primeiro;
}

Nodo *primeiro(Queue *fila){
    if(!empty(fila)){
        printf("Fila vazia\n");
        return NULL;
    }

    return fila->first;
}

int empty(Queue *fila){
    if(!fila->first && !fila->last){
        return 1;
    }

    if(!fila->first || !fila->last){
        printf("ERRO!\n");
        exit(1);
    }

    return 0;
}

void clean(Queue *fila){
    while(!empty(fila))
        free(pop(fila));
}

