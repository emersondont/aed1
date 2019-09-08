#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);

int main(){
	void *pBuffer = NULL;
	int *opcao,*qtd, *tam;
	
	pBuffer = (void *)malloc(3*sizeof(int) + 10*(20*sizeof(char) + sizeof(unsigned int)));
	opcao = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));	//num de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); //tamanho do pBuffer
	
	*qtd = 0;
	*tam = (3 * sizeof(int));
	
	do{
		menu(opcao);
		switch(*opcao){
			case 1:
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

void inserir(void *pBuffer){
	char *c;
	int *qtd, *tam;
	unsigned int *contato;
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	c = (char *)(pBuffer + (3 * sizeof(int)) + *qtd*(20*sizeof(char) + sizeof(unsigned int)));
	contato = (unsigned int *)(c + 20*sizeof(char));
	
	printf("%p %p %p %p\n", qtd, tam, c, contato);
	
	*tam += ((20*sizeof(char) + sizeof(unsigned int)));
	*qtd += 1;
	
	getchar();
	printf("nome: ");
	while((*c = getchar()) != '\n'){
		c += sizeof(char);
	}
	*c = '\0';
	
	printf("numero: ");
	scanf("%d", contato);
	
}

void imprimir(void *pBuffer){
	int *i, *qtd;
	char *c;
	unsigned int *contato;
	
	i = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	
	for(*i = 0; *i < *qtd; *i += 1){
		c = (char *)(pBuffer + (3 * sizeof(int)) + *i*(20*sizeof(char) + sizeof(unsigned int)));
		contato = (unsigned int *)(c + 20*sizeof(char));
	
		
		printf("registro %d, nome: ", *i);
		do{
			putchar(*c);
			c += sizeof(char);
		}while(*c != '\0');
		
		printf("\n\t\t\tnumero: %d\n", *contato);
	}
	*i = 0;
}

