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
				printf("\n");
				print(root, 0);
				printf("\n");
				break;
			case 3:
				printf("\n");
				imprimir(root);
				printf("\n");
				break;
			case 4:
				printf("num: ");
				scanf("%d", &num);
				excluir(&root, num);
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
	printf("\t1 - push\n\t2 - print tree\n\t3 - print order\n\t4 - delete\n\t0 - exit\n");
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
void print(No *root, int l){
	if(root != NULL){
		print(root->right, l+1);
		for(int i = 0; i < l;i++)
			printf("\t");
		printf("(%d)\n", root->conteudo.num);
		print(root->left, l+1);
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

void excluir(No **root, int num){
	if(!(*root)){
		printf("Registro nao encontrado\n");
		return;
	}
	
	if(num < (*root)->conteudo.num){
		excluir(&(*root)->left, num);
		return;
	}
	
	if(num > (*root)->conteudo.num){
		excluir(&(*root)->right, num);
		return;
	}
	
	/*		encontramos o cara p remover	*/
	
	No *delete = *root;
	
	if(isLeaf(*root)){		//se é uma folha
		free(delete);
		*root = NULL;
		return;
	}
	
	if((*root)->left == NULL){		//se não tem filho a esquerda
		*root = delete->right;
		free(delete);
		return;
	}
	
	if((*root)->right == NULL){		//se não tem filho a direita
		*root = delete->left;
		free(delete);
		return;
	}
	
	/*		caso tenha os dois filhos	*/
	
	//SUCESSOR = menor elemento da sub arvore da direita
	//No *delete = *root;

	No *aux = minimo(delete->right);	//sucessor
	//aux = cara que deve ir para o lugar de quem vai ser removido
	delete->conteudo = aux->conteudo;	//faço a troca de conteudo

	excluir(&(*root)->right, aux->conteudo.num);//e agora eu removo o "aux", pq o conteudo dele já foi pro lugar certo

	//essa funcao nao ficou muito boa nao
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