#ifndef REDBLACK_H
#define REDBLACK_H

#include <stdio.h>
#include <stdlib.h>

#define tipoChave int
#define RED "\033[31m"
#define BLACK "\033[30m"
#define RESET "\x1B[0m"

typedef struct info{
	tipoChave key;
	//
}Info;

typedef struct no{
	Info conteudo;
    char color;         //'r' : red / 'b' : black
	struct no *left;
	struct no *right;
}No;

Info lerDados(void);
No *createNo(Info conteudo);
void add(No **root, No *new);

void print(No *root, int l);

void clean(No *root);



#endif
