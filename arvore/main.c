#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
	int opcao;
	SArvore *pArvore;
	pArvore = criarLista();

	do{
		menu(&opcao);
		switch(opcao){
			case 1:
				
				break;
			case 2:
				
				break;
			case 3:

				break;
			case 0:
				puts("saindo...");
				break;
			default:
				puts("opcao invalida seu burro");
				break;
		}
	}while(opcao != 0);

	//clean(pLista);
	free(pLista);
	return 0;
}
