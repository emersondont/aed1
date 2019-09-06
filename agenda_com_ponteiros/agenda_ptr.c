#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);

int main(){
	void *pBuffer = NULL;
	int *tam, *qtd;
	pBuffer = (void *)malloc(3*sizeof(int));

	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//quantidade de registros
	tam = (int *)(pBuffer + (2 * sizeof(int)));		//tamanho do pBuffer
	*qtd = 0;
	*tam = (3*sizeof(int));

	do{
		menu((int *)pBuffer);
		switch(*(int *)pBuffer){
			case 1:
				//*(int *)(pBuffer + (1 * sizeof(int))) += 1;
				inserir(pBuffer);
				break;
			case 2:
				//imprimir(pBuffer);
				printf("%d\n", *(int *)(pBuffer + sizeof(int)));
				break;
			case 3:
				printf("saindo...\n");
				break;
		}
	}while((*(int *)pBuffer) != 3);
	
	free(pBuffer);
	return 0;
}

void menu(int *opcao){
	printf("\n# MENU DE OPCOES #\n");
	do{
		printf("\t1 - insert\n");
		printf("\t2 - print\n");
		printf("\t3 - exit\n");
		printf("opcao: ");
		scanf("%d", opcao);
	}while((*opcao <= 0) || (*opcao > 3));
}

void inserir(void *pBuffer){
	char *c;
	int *tam, *qtd;

	//qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));

	*tam += 10*sizeof(char);

	pBuffer = realloc(pBuffer, *tam);
	//c = (char *)(pBuffer + *tam + 1*sizeof(char));
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));

	*qtd += 1;

	//getchar();
	//*c = getchar();
	printf("%d %d", *qtd, *tam);


}

void imprimir(void *pBuffer){
	char *c;
	int *i, *tam, *qtd;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	c = (char *)(pBuffer + (2*sizeof(int)) + (1*sizeof(char)));

	for(*i = 0; *i < *qtd; *i++){

		printf("registro %d, letra: %c", *i, *c);
		c = (char *)(pBuffer + (2*sizeof(int)) + *i*(1*sizeof(char)) + (1*sizeof(char)));
		//c += 1*sizeof(char);
		//c = (char *)(pBuffer + 3*sizeof(int) + *i*(10*sizeof(char)));

	}
}
