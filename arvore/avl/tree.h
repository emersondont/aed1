#ifndef TREE_H
#define TREE_H

#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

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
/*	imprime os números em ordem		*/
void imprimir(No *root);
/*	imprime a arvore com os nós		*/
void print(No *root, int l);
void clean(No *root);
void excluir(No **root, int num);
No *createNo(int n);
No *search(No *root, int num);
No *minimo(No *root);
int isLeaf(No *root);


#endif