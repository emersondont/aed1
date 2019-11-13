#ifndef STACK_H
#define STACK_H

typedef struct info{
	char nome[20];
	int idade;
}SInfo;

typedef struct nodo{
	SInfo dado;
	struct nodo *pPrevious;
}SNodo;

typedef struct lista{
	SNodo *pLast;
}SStack;

SStack *criarStack();
void menu(int *opcao);
void lerString(char *c);
SNodo *lerDados();
void push(SNodo *new, SStack *pStack);
SNodo *pop(SStack *pStack);
void clean(SStack *pStack);



#endif
