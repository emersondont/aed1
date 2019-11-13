#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

SStack *criarStack(){
    SStack *new;
    new = (SStack *)malloc(sizeof(SStack));
    new->pLast = NULL;
    return new;
}

void menu(int *opcao){
	puts("---MENU---");
	puts("\t1 - push");
	puts("\t2 - pop");
	//puts("\t3 - remover");
	puts("\t0 - sair");
	printf("opcao: ");
	scanf("%d", opcao);
}

void lerString(char *c){
	while((*c = getchar()) != '\n')
		c++;
	*c = '\0';
}

SNodo *lerDados(){
	SNodo *new;
	new = (SNodo *)malloc(sizeof(SNodo));
	new->pPrevious = NULL;

	//ler os dados
	getchar();
	printf("Nome: ");
	lerString(new->dado.nome);

	printf("Idade: ");
	scanf("%d", &new->dado.idade);
	puts("");
	return new;
}

void push(SNodo *new, SStack *pStack){
    if(!pStack->pLast){      //pilha vazia
        pStack->pLast = new;
        return;
    }
    SNodo *ultimo = pStack->pLast;
    new->pPrevious = ultimo;
    pStack->pLast = new;
}

SNodo *pop(SStack *pStack){
    if(!pStack->pLast){      //pilha vazia
        return NULL;
    }
    SNodo *ultimo = pStack->pLast;
    SNodo *newUltimo = ultimo->pPrevious;

    pStack->pLast = newUltimo;
    ultimo->pPrevious = NULL;

    return ultimo;
}

void clean(SStack *pStack){
    SNodo *clear;
    while(clear = pop(pStack))
        free(clear);
}
