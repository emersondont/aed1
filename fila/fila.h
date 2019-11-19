#ifndef FILA_H
#define FILA_H

typedef struct info{
	char nome[20];
	int idade;
}SInfo;

typedef struct nodo{
	SInfo dado;
	struct nodo *pNext;
}SNodo;

typedef struct lista{
	SNodo *pFirst;
	SNodo *pLast;
}SFila;

SFila *criarFila();
void menu(int *opcao);
void lerString(char *c);
SNodo *lerDados();
void push(SNodo *new, SFila *pFila);
SNodo *pop(SFila *pFila);
void clean(SFila *pFila);



#endif