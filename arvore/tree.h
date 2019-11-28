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

typedef struct tree{
	No *root;
}Tree;

void insere(No **root, No *new);
void imprimir(No *root);
void clean(No *root);
void excluir(No **root);
int isLeaf(No *root);
No *createNo(int n);
No *search(No *root, int num);
No *minimo(No *root);
No *sucessor(No *root);

#endif
