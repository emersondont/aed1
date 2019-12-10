/*
 Escreva um algoritmo, usando uma Pilha, que inverte as letras de cada palavra de um texto
 preservando a ordem das palavras.
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int lerString(Stack *pilha);
Nodo *newNodo(char c);
void verificador(Stack *pilha);

int main(){
	Stack *pilha = NULL;
	int resul = 1;

	while(resul){
		pilha = inicializa();

		if(resul = lerString(pilha) != 0){
			verificador(pilha);
			clean(pilha);
			free(pilha);
		}
	}

	clean(pilha);
	free(pilha);

	return 0;
}

void verificador(Stack *pilha){
	Stack *pilhaAux = NULL;
	Stack *pilhaAux2 = NULL;
	Nodo *nodoAux = NULL;

	pilhaAux = inicializa();
	pilhaAux2 = inicializa();
	
	while(!empty(pilha)){
		nodoAux = pop(pilha);
			
		if(nodoAux->conteudo.c != ' ' || empty(pilha))
			push(pilhaAux, nodoAux);

		if(nodoAux->conteudo.c == ' ' || empty(pilha)){
			while(!empty(pilhaAux))
				push(pilhaAux2, pop(pilhaAux));

			if(!empty(pilha))
				push(pilhaAux2, nodoAux);
		}
		
	}
	
	while(!empty(pilhaAux2)){
		nodoAux = pop(pilhaAux2);
		printf("%c", nodoAux->conteudo.c);
		free(nodoAux);
	}
	printf("\n");
	
	clean(pilhaAux);
	clean(pilhaAux2);
	free(pilhaAux);
	free(pilhaAux2);
}


int lerString(Stack *pilha){
	char c;
	int resul = 0;

	while((c = getchar()) != '\n'){
		push(pilha, newNodo(c));
		resul = 1;
	}
	return resul;
}

Nodo *newNodo(char c){
	Nodo *new = NULL;
	new = (Nodo *)malloc(sizeof(Nodo));
	new->conteudo.c = c;
	new->previus = NULL;

	return new;
}


//FUNCOES STACK
Stack *inicializa(void){
    Stack *pilha = NULL;

    pilha = (Stack *)malloc(sizeof(Stack));
    pilha->topo = NULL;

    return pilha;
}

void push(Stack *pilha, Nodo *new){
	if(empty(pilha)) {	//pilha vazia
		new->previus = NULL;
		pilha->topo = new;
		return;
	}
	
	Nodo *topo;
	topo = pilha->topo;
	new->previus = topo;
	pilha->topo = new;
}

Nodo *pop(Stack *pilha){
	if(empty(pilha))
		return NULL;
	
	Nodo *topo;
	topo = pilha->topo;
	pilha->topo = topo->previus;
	
	return topo;
}

Nodo *top(Stack *pilha){
	if(empty(pilha))
		return NULL;
	
	return pilha->topo;
}

int empty(Stack *pilha){
	if(!pilha->topo)
		return 1;
	else
		return 0;	
}

void clean(Stack *pilha){
	while(!empty(pilha))
		free(pop(pilha));
}