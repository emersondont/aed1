#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes_principais.c"

int main(){
	int op;
	SLista *lista = NULL;
	lista = (SLista *)malloc(sizeof(SLista));
	lista->pFirst = NULL;

	do{
		op = menu();
		switch(op){
			case 1:
				inserir(lista);
				break;
			case 2:
				imprimir(lista);
				break;
			case 0:
				printf("saindo....\n");
				break;	
		}
	}while(op != 0);

	return 0;
}

