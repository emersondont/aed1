#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void lerString(Stack *pilha);
Nodo *newNodo(char c);
int verificador(Stack *pilha);

int main(){
	Stack *pilha = NULL;

	for(;;){
		pilha = inicializa();
		lerString(pilha);

		if(verificador(pilha))
			printf("certo\n");
		else
			printf("errado\n");

		clean(pilha);
		free(pilha);
	}


	return 0;
}

int verificador(Stack *pilha){
	int resul = 1;
	Nodo *c;

	while(!empty(pilha)){
		c = pop(pilha);

		if(c->conteudo.c == '('){
			free(c);
			return 0;
		}else if(c->conteudo.c == ')'){
			if(verificador(pilha))
				resul = 0;
		}
		free(c);
	}

	return resul;
}


void lerString(Stack *pilha){
	char c;

	while((c = getchar()) != '\n'){
		push(pilha, newNodo(c));
	}
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
