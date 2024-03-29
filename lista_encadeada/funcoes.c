#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

SLista *criarLista(){
	SLista *new;
	new = (SLista *)malloc(sizeof(SLista));
	new->pFirst = NULL;
	new->pLast = NULL;

	return new;
}

void clean(SLista *pLista){
	SNodo *aux;
	if(!pLista->pFirst)	return;		//se lista vazia
	
	if(!pLista->pFirst->pNext){		//se só tem um
		free(pLista->pFirst);
		return;
	}
	for(aux = pLista->pFirst->pNext; aux->pNext != NULL; aux = aux->pNext)
		free(aux->pPrevious);
	free(aux);
}

void menu(int *opcao){
	puts("---MENU---");
	puts("\t1 - inserir");
	puts("\t2 - imprimir");
	puts("\t3 - remover");
	puts("\t0 - sair");
	printf("opcao: ");
	scanf("%d", opcao);
}

void lerString(char *c){
	while((*c = getchar()) != '\n')
		c++;
	*c = '\0';
}

SNodo *lerDados(int op){
	SNodo *new;
	new = (SNodo *)malloc(sizeof(SNodo));
	new->pPrevious = NULL;
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

void push(SLista *pLista, SNodo *pNodo){
	SNodo *aux;

	if(!pLista->pFirst){	//lista vazia
		pLista->pFirst = pNodo;
		pLista->pLast = pNodo;
		return;
	}

	for(aux = pLista->pFirst; aux->pNext != NULL; aux = aux->pNext);
	
	aux->pNext = pNodo;
	pLista->pLast = pNodo;

	pNodo->pPrevious = aux;
	pNodo->pNext = NULL;
}

void imprimir(SLista *pLista){
	SNodo *aux;
	if(!pLista->pFirst){
		puts("--lista vazia--");
		return;
	}
	puts("\n\tNOME:\t\t\tIDADE:\n");
	for(aux = pLista->pFirst; aux != NULL; aux = aux->pNext)
		imprimirDados(&aux->dado);

	puts("");
}

void imprimirDados(SInfo *dado){
	int tamNome;
	tamNome = 20 - strlen(dado->nome);

	printf("\t%s",dado->nome);
	for(;tamNome > 0; tamNome--)
		printf(" ");
	printf("\t%d\n",dado->idade);
}

int remover(SLista *pLista){
	int resul = 0;
	SNodo *delete;	//nome do cara a ser excluido
	SNodo *aux;
	delete = lerDados(1);
	
	for(aux = pLista->pFirst; aux != NULL; aux = aux->pNext){
		if(!(strcmp(aux->dado.nome, delete->dado.nome))){
			resul = 1;
			break;
		}	
	}

	free(delete);
	delete = aux;

	if(!resul)	return 0;

	if(!delete->pPrevious){		//remover o primeiro
		if(!delete->pNext){		//é o unico
			pLista->pFirst = NULL;
			pLista->pLast = NULL;
			free(delete);
			return 1;
		}
			
		pLista->pFirst = delete->pNext;
		delete->pNext->pPrevious = NULL;
		free(delete);	
		return 1;
	}
	if(!delete->pNext){			//remover o ultimo
		pLista->pLast = delete->pPrevious;
		delete->pPrevious = NULL;
		free(delete);
		return 1;
	}

	aux = delete->pPrevious;
	aux->pNext = delete->pNext;
	delete->pNext->pPrevious = aux;

	free(delete);
	return 1;
}
