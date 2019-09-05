#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
int pointer_size(void *pBuffer);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);

int main(){
	void *pBuffer = NULL;
	pBuffer = (int *)malloc(3*sizeof(int));
	*(int *)(pBuffer + (1 * sizeof(int))) = 0;	//num de elementos
	*(int *)(pBuffer + (2 * sizeof(int))) = (3*sizeof(int));	//tamanho do pBuffer
	do{
		menu((int *)pBuffer);
		switch(*(int *)pBuffer){
			case 1:
				*(int *)(pBuffer + (1 * sizeof(int))) += 1;
				inserir(pBuffer);
				break;
			case 2:
				imprimir(pBuffer);
				//printf("%d\n", *(int *)(pBuffer + sizeof(int)));
				break;
			case 3:
				printf("saindo...\n");
				break;
		}
	}while((*(int *)pBuffer) != 3);
	
	//free(pBuffer);
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

	c = (char *)(pBuffer + *(int *)(pBuffer + (2 * sizeof(int))));			//faz o c apontar para o primeiro caracter a ir para a memoria
	*(int *)(pBuffer + (2 * sizeof(int))) += (10*sizeof(char));				//mais 10 char
	pBuffer = realloc(pBuffer, *(int *)(pBuffer + (2 * sizeof(int))));		//mais 10 char

	//printf("%d", *(int *)(pBuffer + (2 * sizeof(int))));

	getchar();
	printf("nome(max 10 caracter): ");

	while((*c = getchar()) != '\n'){
		c += 1*sizeof(char);
	}
	*c = '\0';
	/*printf("nome: ");
	c = (char *)(pBuffer + *(int *)(pBuffer + (2 * sizeof(int))) - (10*sizeof(char)));
	//getchar();
	while(*c != '\0'){
		printf("%c", *c);
		c += 1*sizeof(char);
	}*/

}

void imprimir(void *pBuffer){
	char *c;
	int *i, *tam;
	i = (int *)pBuffer;
	tam = (int *)(pBuffer + 1*(sizeof(int)));
	printf("i: %d  tam: %d", *i, *tam);
}
