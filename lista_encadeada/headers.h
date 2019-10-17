#ifndef HEADERS_H
#define HEADERS_H

typedef struct info{
	int cod;
	char nome[20];
	double valor;
}SInfo;

typedef struct nodo{
	SInfo dado;
	struct nodo *pPrevius;
	struct nodo *pNext;
}SNodo;

typedef struct lista{
	unsigned int nCount;
	SNodo *pLast;
	SNodo *pFirst;
}SLista;

#endif
