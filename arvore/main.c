#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void menu(int *op);

int main(){
	No *root = NULL;
	int opcao = 0;
	int num = 0;
	
	do{
		menu(&opcao);
		switch(opcao){
			case 1:
				printf("num: ");
				scanf("%d", &num);
				insere(&root, createNo(num));
				break;
			case 2:
				imprimir(root);
				break;
			case 3:
				printf("num: ");
				scanf("%d", &num);
				//excluir(search(root, num));
				break;
			case 0:
				printf("saindo...\n");
				break;
			default:
				printf("opcao invalida\n\n");
				break;
		}
	}while(opcao != 0);
	
	clean(root);
	return 0;
}

void menu(int *op){
	printf("\t1 - push\n\t2 - print\n\t3 - excluir\n\t0 - exit\n");
	printf("opcao: ");
	scanf("%d", op);
}


//FUNCOES TREE
void insere(No **root, No *new){
	if(!(*root)){
		*root = new;
		return;
	}
	
	if(new->conteudo.num < (*root)->conteudo.num){
		insere(&(*root)->left, new);
	}
	else if(new->conteudo.num > (*root)->conteudo.num){
		insere(&(*root)->right, new);
	}
	else{
		printf("Erro : registro ja existe na arvore.\n");
	}
}

No *createNo(int n){
	No *new = NULL;
	new = (No *)malloc(sizeof(No));
	
	if(!new){
		printf("Erro : nao foi possivel alocar memoria.\n");
		exit(1);
	}
	
	new->left = NULL;
	new->right = NULL;
	new->conteudo.num = n;
	
	return new;
}

void imprimir(No *root){
	if(root != NULL){
		imprimir(root->left);
		printf("%d\n", root->conteudo.num);
		imprimir(root->right);
	}
}

void clean(No *root){
	if(root != NULL){
		clean(root->left);
		clean(root->right);
		free(root);
	}
}

//
No *search(No *root, int num){
	if(!root){
		printf("Registro nao encontrado\n");
		return NULL;
	}
	if(num < root->conteudo.num){
		return search(root->left, num);
	}
	else if(num > root->conteudo.num){
		return search(root->right, num);
	}
	else{
		return root;
	}
}

void excluir(No **root){
	if(!(*root)){
		return;
	}
	No *aux = NULL;

	if(!(*root)->left && !(*root)->right){
		root = NULL;
		free(root);
		//*root = aux
	}

	/*
	if(!root->left || !root->right)
		aux = root;
	else
		aux = sucessor(root);
	
	
	if(aux->left != NULL)
		root = aux->left;
	else
		root = aux->right;
	*/
	
	
	
}

No *sucessor(No *root){
	if(root->right != NULL)
		return minimo(root->right);
	
	else
		return NULL;
	
	//
}

No *minimo(No *root){
	if(!root)
		return NULL;
	
	if(root->left != NULL)
		root = minimo(root->left);
	
	return root;
}

int isLeaf(No *root){
	if(!root->left && !root->right)
		return 1;
	else
		return 0;
}
