//primeira posicao do pBuffer eh um inteiro com a opcao
//a segunda eh um int com o num de elementos
//cada nome tera no max 10 bytes

#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
int pointer_size(void *pBuffer);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);

int main(){
	void *pBuffer = NULL;
	pBuffer = (int *)malloc(2*sizeof(int));
	*(int *)(pBuffer + (1 * sizeof(int))) = 0;	//num de elementos

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

int pointer_size(void *pBuffer){
	return ( (*(int *)(pBuffer + ((1*sizeof(int)))) * (10*sizeof(char))) + (2*sizeof(int)));
}

void inserir(void *pBuffer){
	pBuffer = realloc(pBuffer, pointer_size(pBuffer)); //realoca mais 1 char
	char *c;
	
	c = (pBuffer + 1*sizeof(int) + 1*sizeof(char));

	getchar();
	printf("digite: ");

	while((*c = getchar()) != '\n'){
		c += 1*sizeof(char);
	}
	*c = '\0';
	
	c = (pBuffer + 1*sizeof(int) + 1*sizeof(char));

	while(*c != '\0'){
		printf("%c", *c);
		c += 1*sizeof(char);
	}

}

void imprimir(void *pBuffer){

}
