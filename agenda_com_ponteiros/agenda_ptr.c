#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
void lerString(char *c);
void imprimirString(char *c);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);

int main(){
	void *pBuffer = NULL;
	int *opcao,*qtd, *tam;
	
	pBuffer = (void *)malloc(3*sizeof(int) + 0*(20*sizeof(char) + 11*sizeof(char)));
	opcao = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));	//num de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); //tamanho do pBuffer
	
	*qtd = 0;
	*tam = (3 * sizeof(int));
	
	do{
		menu(opcao);
		switch(*opcao){
			case 1:
				*tam += ((20*sizeof(char) + 11*sizeof(char)));
				pBuffer = (void *)realloc(pBuffer, *tam);
				inserir(pBuffer);
				break;
			case 2:
				imprimir(pBuffer);
				break;
			case 3:
				printf("saindo...\n");
				break;
		}
	}while(*opcao != 3);
	
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

void lerString(char *c){
	while((*c = getchar()) != '\n'){
		c += sizeof(char);
	}
	*c = '\0';
}
void imprimirString(char *c){
	do{
		putchar(*c);
		c += sizeof(char);
	}while(*c != '\0');
	putchar('\n');
}

void inserir(void *pBuffer){
	char *cNome, *cData;
	int *qtd, *tam;
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	cNome = (char *)(pBuffer + (3 * sizeof(int)) + *qtd*(20*sizeof(char) + 11*sizeof(char)));
	cData = (char *)(cNome + 20*sizeof(char));
	
	*qtd += 1;
	
	getchar();
	printf("nome: ");
	lerString(cNome);
	printf("data de nascimento: ");
	lerString(cData);
}

void imprimir(void *pBuffer){
	int *i, *qtd;
	char *cNome, *cData;
	
	i = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	
	for(*i = 0; *i < *qtd; *i += 1){
		cNome = (char *)(pBuffer + (3 * sizeof(int)) + *i*(20*sizeof(char) + 11*sizeof(char)));
		cData = (char *)(cNome + 20*sizeof(char));
	
		printf("Registro %d\n\tNome: ", *i);
		imprimirString(cNome);
		printf("\tData de nascimento: ");
		imprimirString(cData);
	}
	*i = 0;
}


