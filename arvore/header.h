#ifndef HEADER_H
#define HEADER_H

typedef struct info{
	//char nome[20];
	int num;
}SInfo;

typedef struct nodo{
	SInfo dado;
	struct nodo *childLeft;
	struct nodo *childRight;
}SNodo;

typedef struct arvore{
	SNodo *topo;
}SArvore;

void menu(int *op);



#endif
