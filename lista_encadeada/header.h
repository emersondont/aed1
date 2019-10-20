#ifndef HEADER_H
#define HEADER_H

typedef struct info{
	char nome[20];
	int idade;
}SInfo;

typedef struct nodo{
	SInfo dado;
	struct nodo *pPrevious;
	struct nodo *pNext;
}SNodo;

typedef struct lista{
	SNodo *pFirst;
	SNodo *pLast;
}SLista;

SLista *criarLista();
void menu(int *opcao);
void lerString(char *c);
SNodo *lerDados();
void push(SLista *pLista, SNodo *pNodo);
void imprimir(SLista *pLista);
void imprimirDados(SInfo *dado);
void clean(SLista *pLista);

void quickSort(SNodo *left, SNodo *right);

#endif
