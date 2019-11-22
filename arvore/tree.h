#ifndef TREE_H
#define TREE_H

typedef struct item{
	int num;
	//
}Item;

typedef struct no{
	Item conteudo;
	struct no *childLeft;	//filho a esquerda
	struct no *childRight;	//filho a direita
}No;

typedef struct tree{
	No *root;		//raiz
}Tree;

Tree *inicializaTree(void);
No *createNo(int n);
No *push(No *root, No *new);
int isLeaf(No *nodo);
void print(No *root);
void clean(No *root);
void remove(No *root, int n);

#endif
