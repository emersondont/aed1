#ifndef STACK_H
#define STACK_H

typedef struct info{
	char c;
	//
}Info;

typedef struct nodo{
	Info conteudo;
	struct nodo *previus;
}Nodo;

typedef struct stack{
	Nodo *topo;
}Stack;

Stack *inicializa(void);
void push(Stack *pilha, Nodo *new);
Nodo *pop(Stack *pilha);
int empty(Stack *pilha);
Nodo *top(Stack *pilha);
void clean(Stack *pilha);

#endif
