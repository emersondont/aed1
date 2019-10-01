/*
AGENDA SOMENTE COM PONTEIROS / DISCIPLINA DE ALGORITMOS E ESTRUTURA DE DADOS

Registro:
{
 	char nome[30];
	unsigned short int idade;	//pq ningém vai ter mais de 65.535 anos
	char telefone[15];
}

void *pBuffer:
{
	1ª posição do pBuffer é um inteiro para a opcao
	2ª posição do pBuffer é um inteiro que guarda a quantidade de registros
	3ª posição do pBuffer é um inteiro que guarda o tamanho do pBuffer
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(int *opcao);
void lerString(char *c);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);
void procurar(void *pBuffer);
void insertionSort(void *pBuffer);
void salvaArq(void *pBuffer);
void leArq(void *pBuffer);

typedef struct pessoa{
	char nome[30];
	unsigned short int idade;
	char telefone[15];
}TAD;

int main(){
	void *pBuffer = NULL;	//ponteiro void onde fica tudo armazenado
	int *opcao, *qtd, *tam;
	
	pBuffer = (void *)malloc(3 * sizeof(int));		//aloca os 3 inteiros iniciais
	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//numero de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); 	//tamanho do pBuffer
	
	*qtd = 0;
	*tam = (3 * sizeof(int));
	pBuffer = realloc(pBuffer, *tam + sizeof(int));
	leArq(pBuffer);
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	//tam = (int *)(pBuffer + (2 * sizeof(int)));

	do{
		opcao = (int *)pBuffer;
		tam = (int *)(pBuffer + (2 * sizeof(int)));
		qtd = (int *)(pBuffer + (1 * sizeof(int)));
		printf("chegou %d %d\n", *tam, *qtd);

		menu(opcao);
		switch(*opcao){
			case 1:
				*tam += sizeof(TAD);	//aumenta tamanho p/ mais um registro
				pBuffer = realloc(pBuffer, *tam);
				inserir(pBuffer);
				break;
			case 2:
				printf("QTD: %d\n", *qtd);
				//pBuffer = realloc(pBuffer, *tam + sizeof(int));	//int p controle do for
				//imprimir(pBuffer);
				break;
			case 3:
			case 4:
				pBuffer = realloc(pBuffer, *tam + sizeof(TAD) + sizeof(int));		//aumenta mais um
				opcao = (int *)pBuffer;
				procurar(pBuffer);
				break;
			case 5:
				pBuffer = realloc(pBuffer, *tam + sizeof(TAD) + 2*sizeof(int));
				insertionSort(pBuffer);
				break;
			case 6:
				//pBuffer = realloc(pBuffer, *tam + sizeof(int));
				//salvaArq(pBuffer);
				printf("saindo...\n");
				break;
		}
		opcao = (int *)pBuffer;
	}while(*opcao != 6);

	free(pBuffer);

	return 0;
}

void menu(int *opcao){
	printf("\n|------------------|");
	printf("\n|  MENU DE OPCOES  |");
	printf("\n|------------------|\n");
	do{
		printf("\t1 - insert\n");
		printf("\t2 - print\n");
		printf("\t3 - search for\n");
		printf("\t4 - delete\n");
		printf("\t5 - insertion sort\n");
		printf("\t6 - exit\n");
		printf("opcao: ");
		scanf("%d", opcao);
	}while((*opcao <= 0) || (*opcao > 6));
}

void lerString(char *c){
	while((*c = getchar()) != '\n'){
		c += sizeof(char);
	}
	*c = '\0';
}

void inserir(void *pBuffer){
	int *qtd;
	TAD *novaPessoa;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	novaPessoa = (TAD *)(pBuffer + 3 * sizeof(int) + *qtd * sizeof(TAD));

	*qtd += 1;
	
	getchar();
	printf("Nome: ");
	lerString(&novaPessoa->nome[0]);
	printf("Idade: ");
	scanf("%hu", &novaPessoa->idade);
	getchar();
	printf("Telefone: ");
	lerString(&novaPessoa->telefone[0]);
}

void imprimir(void *pBuffer){
	int *qtd, *tam, *i;
	TAD *pessoa;
	
	tam = (int *)(pBuffer + (2 * sizeof(int))); 
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	i = (int *)(pBuffer + *tam);
	
	for(*i = 0; *i < *qtd; *i += 1){
		pessoa = (TAD *)(pBuffer + 3 * sizeof(int) + *i * sizeof(TAD));		
		
		printf("Registro %d\n", *i);
		printf("\tNome....: %s\n", pessoa->nome);
		printf("\tidade...: %hu\n", pessoa->idade);
		printf("\tTelefone: %s\n", pessoa->telefone);
		printf("----------------------------------\n");
	}
	pBuffer = realloc(pBuffer, *tam);
}

void procurar(void *pBuffer){
	int *opcao, *qtd, *tam, *i;
	TAD *aux, *aux2, *digitado;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + *tam + sizeof(TAD));

	if(*qtd == 0){
		printf("A agenda esta vazia");
		pBuffer = realloc(pBuffer, *tam);
		return;
	}

	digitado = (TAD *)(pBuffer + *tam);
		
	getchar();
	printf("Nome: ");
	lerString(&digitado->nome[0]);

	for(*i = 0; *i < *qtd; *i += 1){
		aux = (TAD *)(pBuffer + 3*sizeof(int) + *i * sizeof(TAD));
		if(strcmp(aux->nome, digitado->nome) == 0)
			break;
		else if(*i == (*qtd -1)){
			printf("Registro não encontrado ");
			pBuffer = realloc(pBuffer, *tam);	//volta para o tamanho original
			return;
		}
	}

	opcao = (int *)pBuffer;

	if(*opcao == 3){
		printf("Registro %d\n", *i);
		printf("\tNome....: %s\n", aux->nome);
		printf("\tidade...: %hu\n", aux->idade);
		printf("\tTelefone: %s\n", aux->telefone);
	}
	else if(*opcao == 4){
		for(; *i < *qtd; *i += 1){
			aux2 = (TAD *)(pBuffer + 3*sizeof(int) + *i * sizeof(TAD));
			*digitado = *aux;
			*aux = *aux2;
			*aux2 = *digitado;
		}

		*tam -= sizeof(TAD);
		*qtd -= 1;
	}

	pBuffer = realloc(pBuffer, *tam);
}


void insertionSort(void *pBuffer){
	int *i, *j, *qtd, *tam;
	TAD *temp, *dataI, *dataIMaisUm;
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + *tam + sizeof(TAD));
	j = (int *)(i + sizeof(int));
	
	for(*j = 1; *j < *qtd; *j += 1){
		*i = *j - 1;
		temp = (TAD *)(pBuffer + 3 * sizeof(int) + *j * sizeof(TAD));	//temp = data[j]
		dataI = (TAD *)(pBuffer + 3 * sizeof(int) + *i * sizeof(TAD));
		
		while((*i >= 0) && (strcmp(temp->nome, dataI->nome) == -1)){
			dataIMaisUm = (TAD *)(pBuffer + 3 * sizeof(int) + (*i + 1) * sizeof(TAD));
			
			*dataIMaisUm = *dataI;
			*i -= 1;
		}
		
		*dataIMaisUm = *temp;
	}
	pBuffer = realloc(pBuffer,*tam);
}

void salvaArq(void *pBuffer){
	int *qtd, *tam, *i;
	FILE *saida;
	TAD *pessoa;
	
	saida = fopen("dados.txt", "w");
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + *tam);
	
	fprintf(saida,"%d\n", *qtd);
	for(*i = 0; *i < *qtd; *i += 1){
		pessoa = (TAD *)(pBuffer + 3 * sizeof(int) + *i * sizeof(TAD));		
		
		fprintf(saida,"%s\n", pessoa->nome);
		fprintf(saida,"%hu\n", pessoa->idade);
		fprintf(saida,"%s\n", pessoa->telefone);
	}
	
	fclose(saida);
	pBuffer = realloc(pBuffer, *tam);
}
void leArq(void *pBuffer){
	char lixo;
	int *qtd, *tam, *i;
	FILE *entrada;
	TAD *pessoa;
	entrada = fopen("dados.txt", "r");
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	
	fscanf(entrada,"%d", qtd);
	*tam += (*qtd * sizeof(TAD));
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + *tam);
	
	fscanf(entrada,"%c", &lixo);
	for(*i = 0; *i < *qtd; *i += 1){
		pessoa = (TAD *)(pBuffer + 3 * sizeof(int) + *i * sizeof(TAD));		
		
		fscanf(entrada,"%[^\n]s", &pessoa->nome);
		fscanf(entrada,"%c", &lixo);
		fscanf(entrada,"%hu", &pessoa->idade);
		fscanf(entrada,"%c", &lixo);
		fscanf(entrada,"%[^\n]s", &pessoa->telefone);
		fscanf(entrada,"%c", &lixo);
	}
	//imprimir(pBuffer);
	printf("TAM: %d QTD: %d\n", *tam, *qtd);
	pBuffer = realloc(pBuffer, *tam);
	fclose(entrada);
}
