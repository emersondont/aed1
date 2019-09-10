/*
AGENDA SOMENTE COM PONTEIROS / DISCIPLINA DE ALGORITMOS E ESTRUTURA DE DADOS

Registro:
{
 	char nome[30];
	unsigned short int idade;	//pq ningém vai ter mais de 65.535 anos
	char telefone[15];
} 	

tamanho de cada registro: (30*sizeof(char) + sizeof(unsigned short int) + sizeof(unsigned long int)

void *pBuffer:
{
	1ª posição do pBuffer é um inteiro para a opcao / tambem como uma variavel para o controle do for
	2ª posição do pBuffer é um inteiro que guarda a quantidade de registros
	3ª posição do pBuffer é um inteiro que guarda o tamanho do pBuffer
}

*/


#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
void lerString(char *c);
void imprimirString(char *c);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);
void salvaArq(void *pBuffer);
void lerArq(void *pBuffer);

int main(){
	void *pBuffer = NULL;	//ponteiro void onde fica tudo armazenado
	int *opcao, *qtd, *tam;
	
	pBuffer = (void *)malloc(3 * sizeof(int));		//aloca os 3 inteiros iniciais
	opcao = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//numero de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); 	//tamanho do pBuffer
	
	*qtd = 0;
	*tam = (3 * sizeof(int));

	//lerArq(pBuffer);

	do{
		menu(opcao);
		switch(*opcao){
			case 1:
				*tam += (45*sizeof(char) + sizeof(unsigned short int));	//aumenta tamanho p mais um registro
				pBuffer = (void *)realloc(pBuffer, *tam);
				inserir(pBuffer);
				break;
			case 2:
				imprimir(pBuffer);
				break;
			case 3:
				//salvaArq(pBuffer);
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
	char *cNome, *cTelefone;
	unsigned short int *idade;
	int *qtd;
	
	//posiciona os ponteiros
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	cNome = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int)));	//1º caracter do nome
	idade = (unsigned short int *)(cNome + 30 * sizeof(char));
	cTelefone = (char *)(idade + sizeof(unsigned short int));

	*qtd += 1;
	
	//ler os dados
	getchar();
	printf("nome: ");
	lerString(cNome);
	printf("idade: ");
	scanf("%hu", idade);
	getchar();
	printf("telefone: ");
	lerString(cTelefone);
}

void imprimir(void *pBuffer){
	char *cNome, *cTelefone;
	unsigned short int *idade;
	int *qtd, *i;
	
	i = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	
	for(*i = 0; *i < *qtd; *i += 1){
		cNome = (char *)(pBuffer + 3 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));	//1º caracter do nome
		idade = (unsigned short int *)(cNome + 30 * sizeof(char));
		cTelefone = (char *)(idade + sizeof(unsigned short int));
	
		printf("Registro %d\n", *i);
		printf("\tNome....: ");
		imprimirString(cNome);
		printf("\tidade...: %hu\n", *idade);
		printf("\tTelefone: ");
		imprimirString(cTelefone);
		printf("----------------------------------\n");
	}
	*i = 0;
}

void salvaArq(void *pBuffer){
	char *cNome, *cData;
	int *qtd, *i;
	FILE *saida;

	i = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));

	if((saida = fopen("backup.txt", "w")) == NULL){
		printf("erro ao salvar o arquivo!");
		return;
	}

	fprintf(saida, "%d\n", *qtd);

	for(*i = 0; *i < *qtd; *i += 1){
		cNome = (char *)(pBuffer + (3 * sizeof(int)) + *i*(20*sizeof(char) + 11*sizeof(char)));
		cData = (char *)(cNome + 20*sizeof(char));

		do{
			fprintf(saida, "%c", *cNome);
			cNome += sizeof(char);
		}while(*cNome != '\0');

		fprintf(saida, "\n");

		do{
			fprintf(saida, "%c", *cData);
			cData += sizeof(char);
		}while(*cData != '\0');

		fprintf(saida, "\n");
	}

	*i = 3;

	fclose(saida);
}

void lerArq(void *pBuffer){
	char *cNome, *cData;
	int *op, *i, *qtd, *tam;
	FILE *entrada;

	op = (int *)pBuffer;
	printf("press 1 to read from file ");
	scanf("%d", op);
	if(*op != 1)
		return;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));

	if((entrada = fopen("backup.txt", "r")) == NULL){
		printf("erro ao abrir o arquivo!");
		return;
	}

	fscanf(entrada, "%d", qtd);
	*tam += *qtd * ((20*sizeof(char) + 11*sizeof(char)));
	pBuffer = (void *)realloc(pBuffer, *tam);

	i = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));

	//
	fgetc(entrada);
	for(*i = 0; *i < *qtd; *i += 1){
		cNome = (char *)(pBuffer + (3 * sizeof(int)) + *i*(20*sizeof(char) + 11*sizeof(char)));
		cData = (char *)(cNome + 20*sizeof(char));

		while((*cNome = fgetc(entrada)) != '\n'){
			cNome += 1*sizeof(char);
		}
		*cNome = '\0';

		while((*cData = fgetc(entrada)) != '\n'){
			cData += 1*sizeof(char);
		}
		*cData = '\0';
	}
	
	fclose(entrada);
}