#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main(){
	int opcao;
	SFila *pFila;
	pFila = criarFila();
	
	SNodo *aux;

	do{
		menu(&opcao);
		switch(opcao){
			case 1:
				push(lerDados(), pFila);
				break;
			case 2:
				aux = pop(pFila);
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

	clean(pFila);
	free(pFila);
	return 0;
}
