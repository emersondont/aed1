#include "redblack.h"

int main(){
    No *root = NULL;
    add(&root, createNo(lerDados()));


    clean(root);
    return 0;
}

//funcoes
Info lerDados(void){
    Info conteudo;
    printf("Num: ");
    scanf("%d", &conteudo.key);

    return conteudo;
}

No *createNo(Info conteudo){
    No *new = NULL;
    new = (No *)malloc(sizeof(No));
    new->left = NULL;
    new->right = NULL;
    new->color = 'r';

    return new;
}
void add(No **root, No *new){
    if(*root == NULL){
        *root = new;
        return;
    }

    
}

void print(No *root, int l){
    if(root != NULL){
		print(root->right, l + 1);
		for(int i = 0; i < l; i++)
			printf("\t");
        if(root->color == 'e')
		    printf(RED "(%d)\n", root->conteudo.key);
        else
            printf(BLACK "(%d)\n", root->conteudo.key);
        
		printf(RESET);
		print(root->left, l + 1);
	}
}

void clean(No *root){
    if(root != NULL){
        clean(root->left);
        clean(root->right);
        free(root);       
    }
}

