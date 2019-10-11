#include <stdio.h>
#include <stdlib.h>
#include "bib.h"

int menu(){
	int opcao;
	printf("\n|------------------|");
	printf("\n|  MENU DE OPCOES  |");
	printf("\n|------------------|\n");
	do{
		printf("\t1 - insert\n");
		printf("\t2 - print\n");
		printf("\t0 - exit\n");
		printf("opcao: ");
		scanf("%d", &opcao);
	}while((opcao < 0) || (opcao > 2));

	return opcao;
}

void lerString(char *c){
	while((*c = getchar()) != '\n'){
		c += sizeof(char);
	}
	*c = '\0';
}

void inserir(SLista *lista){
	if(lista->pFirst == NULL){		//lista vazia
		lista->pFirst = (SNodo *)malloc(sizeof(SNodo));
		lista->pFirst->next = NULL;
		push(&lista->pFirst->info);
		return;
	}

	SNodo *aux, *new;

	for(aux = lista->pFirst; aux->next != NULL; aux = aux->next);

	new = (SNodo *)malloc(sizeof(SNodo));
	aux->next = new;
	new->next = NULL;
	push(&new->info);
}

void push(SDado *new){
	getchar();
	printf("\tNome: ");
	lerString(&new->name[0]);
	printf("\tIdade: ");
	scanf("%d", &new->age);
}

void imprimir(SLista *lista){
	int i;
	SNodo *aux;

	for(aux = lista->pFirst, i = 0; aux != NULL; aux = aux->next, i++){
		printf("Registro %d\n", i);
		printfDados(&aux->info);
	}
}

void printfDados(SDado *aux){
	printf("\tNome....: %s\n", aux->name);
	printf("\tidade...: %d\n", aux->age);
}
