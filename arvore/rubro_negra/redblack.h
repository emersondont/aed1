#ifndef REDBLACK_H
#define REDBLACK_H

#include <stdio.h>
#include <stdlib.h>

#define RED "\033[31m"
#define BLACK "\033[30m"
#define RESET "\x1B[0m"

/*
Uma árvore rubro-negra estará sempre balanceada, pois segue o
seguinte conjunto de regras:

o nó raiz é sempre preto.

nós vermelhos que não sejam folhas possuem apenas filhos
pretos.

para cada nó, todos os caminhos do nó até qualquer folha
passa pelo mesmo número de nós pretos.
*/

#define keyType int
#define byte char

typedef struct info{
	keyType key;
	//
}Info;

typedef struct no{
	Info content;
    byte color;         //'r' : red / 'b' : black
	struct no *left;
	struct no *right;
	struct no *parent;
}No;

Info readInfo(void);
No *createNo(Info content);
void add(No **root, No *new);

No *grandParent(No *root);
No *uncle(No *root);
/*
Existem três casos para corrigir as cores após uma inserção:

Caso 1: O tio do elemento inserido é VERMELHO.

Caso 2: O tio do elemento inserido é PRETO e o elemento
inserido é um filho da direita.

Caso 3: O tio do elemento inserido é PRETO e o elemento
inserido é um filho da esquerda.
*/
void insertCase1(No *root);
void insertCase2(No *root);
void insertCase3(No *root);
void insertCase4(No *root);
void insertCase5(No *root);

void print(No *root, int l);
void clean(No *root);



#endif
