#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
	int opcao;
	SLista *pLista;
	pLista = criarLista();

	do{
		menu(&opcao);
		switch(opcao){
			case 1:
				push(pLista, lerDados());
				break;
			case 2:
				imprimir(pLista);
				break;
			case 3:
				quickSort(pLista->pFirst, pLista->pLast);
				break;
			case 0:
				puts("saindo...");
				break;
			default:
				puts("opcao invalida seu burro");
				break;
		}
	}while(opcao != 0);

	clean(pLista);
	free(pLista);
	return 0;
}
