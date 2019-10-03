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
void salvaArq(void *pBuffer);
void leArq(void *pBuffer, FILE *entrada);

void insertionSort(void *pBuffer);
void selectSort(void *pBuffer);
void bubbleSort(void *pBuffer);

typedef struct pessoa{
	char nome[30];
	unsigned short int idade;
	char telefone[15];
}TAD;

int main(){
	void *pBuffer = NULL;	//ponteiro void onde fica tudo armazenado
	int *opcao, *qtd, *tam;
	FILE *entrada;
	
	pBuffer = (void *)malloc(3 * sizeof(int));		//aloca os 3 inteiros iniciais
	opcao = (int *)pBuffer;
	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//numero de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); 	//tamanho do pBuffer
	
	*qtd = 0;
	*tam = (3 * sizeof(int));
	//ler arq
		entrada = fopen("dados.txt", "r");
		fscanf(entrada,"%d", qtd);
		*tam += (*qtd * sizeof(TAD));
		pBuffer = realloc(pBuffer, *tam + sizeof(int) + sizeof(char));
			
		leArq(pBuffer, entrada);
		fclose(entrada);
	//

	do{
		menu(opcao);

		switch(*opcao){
			case 1:
				*tam += sizeof(TAD);	//aumenta tamanho p/ mais um registro
				pBuffer = realloc(pBuffer, *tam);
				inserir(pBuffer);
				break;
			case 2:
				pBuffer = realloc(pBuffer, *tam + sizeof(int));	//int p controle do for
				imprimir(pBuffer);
				break;
			case 3:
			case 4:
				pBuffer = realloc(pBuffer, *tam + sizeof(TAD) + sizeof(int));		//aumenta mais 1 TAD e 1 int p for
				procurar(pBuffer);
				break;
		/*
			case 5:
				entrada = fopen("dados.txt", "r");
				fscanf(entrada,"%d", qtd);
				*tam += (*qtd * sizeof(TAD));
				pBuffer = realloc(pBuffer, *tam + sizeof(int) + sizeof(char));
			
				leArq(pBuffer, entrada);
				fclose(entrada);
				break;

			case 6:
				pBuffer = realloc(pBuffer, *tam + sizeof(int));
				salvaArq(pBuffer);
				break;
		*/
			case 5:
				pBuffer = realloc(pBuffer, *tam + sizeof(TAD) + 2*sizeof(int));
				insertionSort(pBuffer);
				break;
			case 6:
				pBuffer = realloc(pBuffer, *tam + 2*sizeof(TAD) + 3*sizeof(int));
				selectSort(pBuffer);
				break;
			case 7:
				pBuffer = realloc(pBuffer, *tam + sizeof(TAD) + 2*sizeof(int));
				bubbleSort(pBuffer);
				break;
			case 8:
				printf("saindo...\n");
				break;
			default:
				printf("opcao invalida\n");
				break;
		}

		opcao = (int *)pBuffer;
		tam = (int *)(pBuffer + (2 * sizeof(int)));
	}while(*opcao != 8);

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
		/*
		printf("\t5 - read data from file\n");
		printf("\t6 - write data to file\n");
		*/
		printf("\t5 - insertionSort\n");
		printf("\t6 - selectSort\n");
		printf("\t7 - bubbleSort\n");
		printf("\t8 - exit\n");
		printf("option: ");
		scanf("%d", opcao);
	}while((*opcao < 0) || (*opcao > 8));
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
		printf("Registro apagado\n");
	}

	pBuffer = realloc(pBuffer, *tam);
}

void salvaArq(void *pBuffer){
	int *qtd, *tam, *i;
	FILE *saida;
	TAD *pessoa;
	
	saida = fopen("dados-1.txt", "w");
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

void leArq(void *pBuffer, FILE *entrada){
	char *lixo;
	int *qtd, *tam, *i;
	TAD *pessoa;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + *tam);
	lixo = (char *)(i + sizeof(int));

	for(*i = 0; *i < *qtd; *i += 1){
		pessoa = (TAD *)(pBuffer + 3 * sizeof(int) + *i * sizeof(TAD));	

		fscanf(entrada,"%c", lixo);
		fscanf(entrada,"%[^\n]s", pessoa->nome);
		fscanf(entrada,"%c", lixo);
		fscanf(entrada,"%hu", &pessoa->idade);
		fscanf(entrada,"%c", lixo);
		fscanf(entrada,"%[^\n]s", pessoa->telefone);
	}
	pBuffer = realloc(pBuffer, *tam);
}

void insertionSort(void *pBuffer){
	int *qtd, *tam, *i, *j;
	TAD *tmp, *vI, *vIProx, *vJ;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));

	tmp = (TAD *)(pBuffer + *tam);
	i = (int *)(tmp + sizeof(TAD));
	j = (int *)(i + sizeof(int));

	for(*j = 1; *j < *qtd; *j += 1){
		*i = *j - 1;

		vJ = (TAD *)(pBuffer + 3*sizeof(int) + *j * sizeof(TAD));				//v[j]
		vI = (TAD *)(pBuffer + 3*sizeof(int) + *i * sizeof(TAD));				//v[i]
		vIProx = (TAD *)(pBuffer + 3*sizeof(int) + (*i+1) * sizeof(TAD));		//v[i+1]
		*tmp = *vJ;		//tmp = v[j]

		while( (*i >= 0) && (strcmp(vI->nome, tmp->nome) == 1) ){				//vI > tmp
			*vIProx = *vI;
			(*i)--;

			vI = (TAD *)(pBuffer + 3*sizeof(int) + *i * sizeof(TAD));			//v[i]	
			vIProx = (TAD *)(pBuffer + 3*sizeof(int) + (*i+1) * sizeof(TAD));	//v[i+1]
		}

		*vIProx = *tmp;		//v[i+1] = tmp
	}

	pBuffer = realloc(pBuffer, *tam);	//volta pro tamanho
}

void selectSort(void *pBuffer){
	int *qtd, *tam, *i, *j, *min_id;
	TAD *min, *tmp, *vJ, *vI, *vMin_id;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));

	tmp = (TAD *)(pBuffer + *tam);
	min = (TAD *)(tmp + sizeof(TAD));	
	i = (int *)(min + sizeof(TAD));
	j = (int *)(i + sizeof(int));
	min_id = (int *)(j + sizeof(int));

	for(*i = 0; *i < (*qtd -1); *i += 1){
		vI = (TAD *)(pBuffer + 3*sizeof(int) + *i * sizeof(TAD));	//v[i]
		*min = *vI;			//min = v[i]
		*min_id = *i;
		
		for(*j = (*i + 1); *j < *qtd; *j += 1){
			vJ = (TAD *)(pBuffer + 3*sizeof(int) + *j * sizeof(TAD));	//v[j]

			if(strcmp(min->nome, vJ->nome) == 1){	//min > v[j]
				*min = *vJ;
				*min_id = *j;
			}
		}

		vMin_id = (TAD *)(pBuffer + 3*sizeof(int) + *min_id * sizeof(TAD));	//v[min_id]

		*tmp = *vI;
		*vI = *vMin_id;
		*vMin_id = *tmp;
	}

	pBuffer = realloc(pBuffer, *tam);	//volta pro tamanho
}

void bubbleSort(void *pBuffer){
	int *qtd, *tam, *i, *j;
	TAD *vI, *vJ, *aux;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));

	aux = (TAD *)(pBuffer + *tam);
	i = (int *)(aux + sizeof(TAD));
	j = (int *)(i + sizeof(int));

	for(*i = 0; *i < (*qtd - 1); *i += 1){
		vI = (TAD *)(pBuffer + 3*sizeof(int) + *i * sizeof(TAD));
		for(*j = *i + 1; *j < *qtd; *j += 1){
			vJ = (TAD *)(pBuffer + 3*sizeof(int) + *j * sizeof(TAD));

			if(strcmp(vI->nome, vJ->nome) == 1){	//v[i] > v[j]
				*aux = *vI;
				*vI = *vJ;
				*vJ = *aux;
			}
		}
	}
	pBuffer = realloc(pBuffer, *tam);
}