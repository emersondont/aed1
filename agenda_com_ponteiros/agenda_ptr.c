#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);

int main(){
	void *pBuffer = NULL;
	int *opcao,*qtd, *tam;
	
	pBuffer = (void *)malloc(3*sizeof(int) /*+ 11*sizeof(char)*/);
	opcao = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//num de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int)));		//tamanho do pBuffer
	
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

	tam = (int *)(pBuffer + (2 * sizeof(int)));
	*tam += (11*sizeof(char));

	pBuffer = realloc(pBuffer,*tam);		//eu odeio o relloc
	if(pBuffer == NULL){
		printf("ERRO AO TENTAR REALOCAR");
		exit(1);
	}
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	c = (char *)(pBuffer + (3 * sizeof(int)) + *qtd*11*sizeof(char));

	//printf("%d %d %p %p %p\n", *qtd, *tam, qtd, tam, c);
	*qtd += 1;
	printf("%d %d %p %p %p\n", *qtd, *tam, qtd, tam, c);
	
	/*getchar();
	printf("nome: ");
	while((*c = getchar()) != '\n'){
		c += sizeof(char);
	}
	*c = '\0';
	*/
}

void imprimir(void *pBuffer){
	int *i, *qtd;
	char *c;
	
	i = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	
	for(*i = 0; *i < *qtd; *i += 1){
		c = (char *)(pBuffer + (3 * sizeof(int)) + *i*11*sizeof(char));
		
		printf("registro %d, nome: ", *i);
		do{
			putchar(*c);
			c += sizeof(char);
		}while(*c != '\0');
		
		printf("\n");
	}
	
}
