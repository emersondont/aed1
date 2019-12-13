#include "redblack.h"

int main(){
    No *root = NULL;
    add(&root, createNo(readInfo()));


    clean(root);
    return 0;
}

Info readInfo(void){
    Info content;
    printf("Num: ");
    scanf("%d", &content.key);
    //
    //

    return content;
}

No *createNo(Info content){
    No *new = NULL;
    if((new = (No *)malloc(sizeof(No))) == NULL){
        printf(RED "error : nao foi possivel alocar memoria\n");
        exit(1);
    }
    new->content = content;
    new->color = 'r';
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;

    return new;
}

void add(No **root, No *new){
    if(*root == NULL){
        *root = new;
        return;
    }

    
}

No *grandParent(No *root){
    if((root != NULL) && (root->parent != NULL))
        return root->parent->parent;
    else
        return NULL;
}

No *uncle(No *root){
    No *g = NULL;   //avo
    g = grandParent(root);

    if(g == NULL)
        return NULL;

    if(root->parent == g->left)
        return g->right;
    else
        return g->left;
}

void insertCase1(No *root){
    if(root->parent == NULL)    //se ele não tem pai, então ele é a raiz
        root->color = 'b';
    else
        insertCase2(root);
}

void insertCase2(No *root){
    if(root->parent->color == 'b')
        return;     //a arvore esta balanceada
    else
        insertCase3(root);
}

void insertCase3(No *root){
    No *u = NULL;   //tio
    No *g = NULL;   //avo
    u = uncle(root);

    if((u != NULL) && (u->color == 'r')){
        root->parent->color = 'b';
        u->color = 'b';
        g = grandParent(root);
        g->color = 'r';
        insertCase1(g);
    }
    else
        insertCase4(root);
}

void insertCase4(No *root){
    No *g = NULL;   //avo
    g = grandParent(root);

    if((root == root->parent->right) && (root->parent == g->left)){
        //RSE(root->parent);
        root = root->left;
    }else if((root == root->parent->left) && (root->parent == g->right)){
        //RSD(root->parent);
        root = root->right;
    }
    insertCase5(root);
}

void insertCase5(No *root){
    No *g = NULL;   //avo
    g = grandParent(root);

    root->parent->color = 'b';
    g->color = 'r';

    if((root == root->parent->left) && (root->parent == g->left)){
        //RSD(g);
    }
    else{
        //if((root == root->parent->right) && (root->parent == g->right))
        //RSE(g)
    }
}

//////////////////////////////////////////////////////////////////////////
void print(No *root, int l){
    if(root != NULL){
		print(root->right, l + 1);

		for(int i = 0; i < l; i++)
			printf("\t");

        if(root->color == 'e')
		    printf(RED "(%d)\n", root->content.key);
        else
            printf(BLACK "(%d)\n", root->content.key);
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

