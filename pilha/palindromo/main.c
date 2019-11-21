/*
Escreva um programa solicite ao usuário uma sequência de caracteres sem limite máximo 
de tamanho e realize as seguintes operações usando uma pilha:
a) Imprimir o texto na ordem inversa;
b) Verificar se o texto é um palíndromo
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void lerStringEDarPush(Stack *pilha);
Nodo *newNodo(char c);
void imprimirAoContrario(Stack *pilha);
int palindromo(Stack *pilha);

int main(){
	Stack pilha;
	pilha.topo = NULL;
	
	printf("string......: ");
	lerStringEDarPush(&pilha);
	
	printf("ao contrario: ");
	imprimirAoContrario(&pilha);
	
	if(palindromo(&pilha))
		printf("Eh palindromo\n");
	else
		printf("Nao eh palindromo\n");
	
	clean(&pilha);
	return 0;
}

void lerStringEDarPush(Stack *pilha){
	char c;
	
	while((c = getchar()) != '\n'){
		push(pilha, newNodo(c));
	}
}

Nodo *newNodo(char c){
	Nodo *new;
	new = (Nodo *)malloc(sizeof(Nodo));
	new->conteudo.c = c;
	new->previus = NULL;
	
	return new;
}

void imprimirAoContrario(Stack *pilha){
	Stack *pilhaAux = NULL;
	Nodo *nodoAux = NULL;
	
	pilhaAux = (Stack *)malloc(sizeof(Stack));
	pilhaAux->topo = NULL;
	
	while(!empty(pilha)){
		nodoAux = pop(pilha);
		push(pilhaAux, nodoAux);
		
		printf("%c", nodoAux->conteudo.c);
	}
	
	//devolver p pilha original
	while(!empty(pilhaAux)){
		push(pilha, pop(pilhaAux));
	}
	
	printf("\n");
	free(pilhaAux);
}

int palindromo(Stack *pilha){
	Stack *primeiraMetade, *segundaMetade;
	Nodo *aux;
	int tam = 0;
	int resul = 1;
	
	primeiraMetade = (Stack *)malloc(sizeof(Stack));
	segundaMetade = (Stack *)malloc(sizeof(Stack));
	
	primeiraMetade->topo = NULL;
	segundaMetade->topo = NULL;
	
	//passa tudo pra primeira e segunda(sem espacos)
	while(!empty(pilha)){
		aux = (Nodo *)malloc(sizeof(Nodo));
		*aux = *top(pilha);
		if(aux->conteudo.c != ' '){
			push(segundaMetade, aux);
			tam++;
		}
		
		push(primeiraMetade, pop(pilha));
	}
	
	while(!empty(primeiraMetade)){
		push(pilha, pop(primeiraMetade));
	}
	
	for(int i = 0; i < tam/2 ; i++){
		push(primeiraMetade, pop(segundaMetade));
	}
	
	if(tam % 2 == 1)
		free(pop(segundaMetade));
	
	
	while(!empty(segundaMetade)){
		
		if(
			(pop(primeiraMetade)->conteudo.c)
			!=
			(pop(segundaMetade)->conteudo.c)
		){
			resul = 0;
			break;
		}
	}
	
	clean(primeiraMetade);
	clean(segundaMetade);
	free(primeiraMetade);
	free(segundaMetade);
	
	return resul;
}


//FUNCOES STACK
void push(Stack *pilha, Nodo *new){
    if(!pilha){
        pilha = (Stack *)malloc(sizeof(Stack));
        pilha->topo = NULL;
        
        if(!pilha){
            printf("ERRO AO CRIAR PILHA\n");
            return;
        }
    }

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
