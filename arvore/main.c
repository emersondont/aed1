#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() {
	Tree *arvore = NULL;
	arvore = inicializaTree();

	arvore->root = push(arvore->root, createNo(10));
	arvore->root = push(arvore->root, createNo(13));
	arvore->root = push(arvore->root, createNo(4));
	arvore->root = push(arvore->root, createNo(5));
	arvore->root = push(arvore->root, createNo(3));

	print(arvore->root);
	printf("\n");

	clean(arvore->root);
	free(arvore);
	return 0;
}

Tree *inicializaTree(void){
	Tree *arvore = NULL;
	arvore = (Tree *)malloc(sizeof(arvore));
	arvore->root = NULL;

	return arvore;
}

No *createNo(int n){
	No *new = NULL;
	new = (No *)malloc(sizeof(No));

	new->childLeft = NULL;
	new->childRight = NULL;
	new->conteudo.num = n;

	return new;
}

No *push(No *root, No *new){
	if(root == NULL){	//Raiz(desta sub arvore) vazia
		root = new;
		return root;
	}

	if(new->conteudo.num < root->conteudo.num){
		root->childLeft = push(root->childLeft, new);
	}
	else if(new->conteudo.num > root->conteudo.num){
		root->childRight = push(root->childRight, new);
	}
	else
		printf("Erro : Registro ja existe na arvore\n");

	return root;
}

int isLeaf(No *nodo){
	if(!nodo->childLeft && !nodo->childRight)
		return 1;
	else
		return 0;
}

void print(No *root){
	if(root != NULL){
		printf("%d ", root->conteudo.num);
		print(root->childLeft);
		print(root->childRight);
	}
}

void clean(No *root){
	if(root != NULL){
		clean(root->childLeft);
		clean(root->childRight);
		free(root);
	}
}

void remove(No *root, int n){
	if(root == NULL)
		return;

	if(root->conteudo.num == n){


		
	}

	if(root->conteudo < n){
		remove(root->childLeft, n);
	}
	else{
		remove(root->childRight, n);
	}
}
