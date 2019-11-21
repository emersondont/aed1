#ifndef QUEUE_H
#define QUEUE_H

typedef struct info{
	char nomeAviao[10];
    int capacidade;
}Info;

typedef struct nodo{
	Info conteudo;
    struct nodo *next;
	struct nodo *previus;
}Nodo;

typedef struct queue{
	Nodo *first;
    Nodo *last;
}Queue;

Queue *inicializa(void);
void push(Queue *fila, Nodo *new);
Nodo *pop(Queue *fila);
Nodo *primeiro(Queue *fila);
int empty(Queue *fila);
void clean(Queue *fila);

#endif