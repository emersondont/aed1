
#ifndef BIB_H
#define BIB_H

typedef struct sd{
	char name[30];
	int age;
}SDado;

typedef struct sn{
	SDado info;
	struct sn *next;
}SNodo;

typedef struct sl{
	SNodo *pFirst;
}SLista;

int menu();
void lerString(char *c);
void inserir(SLista *lista);
void push(SDado *new);
void imprimir(SLista *lista);
void printfDados(SDado *aux);

#endif
