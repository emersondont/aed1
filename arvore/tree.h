#ifndef TREE_H
#define TREE_H

typedef struct info{
	int num;
	//
}Info;

typedef struct no{
	Info conteudo;
	struct no *left;
	struct no *right;
}No;


void insere(No **root, No *new);
/*	imprime os ńúmeros em ordem		*/
void imprimir(No *root);
/*	imprime a arvore com os nós		*/
void print(No *root, int l);
void clean(No *root);
void excluir(No **root, int num);
No *createNo(int n);
No *search(No *root, int num);
No *minimo(No *root);
No *sucessor(No *root);
int isLeaf(No *root);


#endif