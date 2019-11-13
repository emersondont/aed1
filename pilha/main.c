#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(){
	int opcao;
	SStack *pStack;
	pStack = criarStack();
	
	SNodo *aux;

	do{
		menu(&opcao);
		switch(opcao){
			case 1:
				push(lerDados(), pStack);
				break;
			case 2:
				aux = pop(pStack);
				if(!aux)
					printf("pilha vazia\n");
				else{
					printf("%s %d\n", aux->dado.nome, aux->dado.idade);
					free(aux);
				}
					
				break;
			case 0:
				puts("saindo...");
				break;
			default:
				puts("opcao invalida seu burro");
				break;
		}
	}while(opcao != 0);

	clean(pStack);
	free(pStack);
	return 0;
}
