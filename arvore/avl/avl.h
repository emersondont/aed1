#ifndef AVL_H
#define AVL_H

#include "tree.h"

int altura(No *root);
int fb(No *root);		//fator de balanceamento, retorna: < 1 se a sub arvore da esq é maior, > 1 se a sub arvore da dir é maior
void RSE(No **root);
void RSD(No **root);
int balancaEsquerda(No **root);	//rotacao dupla
int balancaDireita(No **root);	//rotacao dupla
int balanceamento(No **root);

int insereAVL(No **root, No *new);


#endif