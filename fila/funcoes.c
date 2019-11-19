#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void push(SNodo *new, SFila *pFila){
    if(!pFila->pFirst){     //fila vazia
        pFila->pFirst = new;
        pFila->pLast = new;
        return;
    }
    SNodo *ultimo;
    ultimo = pFila->pLast;
    ultimo->pNext = new;
    pFila->pLast = new;
}

SNodo *pop(SFila *pFila){
    if(!pFila->pFirst){
        return NULL;
    }

    SNodo *primeiro;
    primeiro = pFila->pFirst;
    pFila->pFirst = primeiro->pNext;

    return primeiro;
}


SFila *criarFila(){
    SFila *new;
    new = (SFila *)malloc(sizeof(SFila));
    new->pFirst = NULL;
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
	new->pNext = NULL;

	//ler os dados
	getchar();
	printf("Nome: ");
	lerString(new->dado.nome);

	printf("Idade: ");
	scanf("%d", &new->dado.idade);
	puts("");
	return new;
}


void clean(SFila *pFila){
    SNodo *clear;
    while(clear = pop(pFila))
        free(clear);
}
