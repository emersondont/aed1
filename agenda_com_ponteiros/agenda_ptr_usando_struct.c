/*
AGENDA SOMENTE COM PONTEIROS / DISCIPLINA DE ALGORITMOS E ESTRUTURA DE DADOS

Registro:
{
 	char nome[30];
	unsigned short int idade;	//pq ningém vai ter mais de 65.535 anos
	char telefone[15];
} 	

tamanho de cada registro: (45*sizeof(char) + sizeof(unsigned short int)

void *pBuffer:
{
	1ª posição do pBuffer é um inteiro para a opcao
	2ª posição do pBuffer é um inteiro que guarda a quantidade de registros
	3ª posição do pBuffer é um inteiro que guarda o tamanho do pBuffer
	4ª posição do pBuffer é um inteiro para o controle do for
}

*/

#include <stdio.h>
#include <stdlib.h>

void menu(int *opcao);
void lerString(char *c);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);
void procurar(void *pBuffer);
void insertionSort(void *pBuffer);
void trocarRegistros(char *c1, char *c2, char *cA);
void trocarStringsDeRegistros(char *c1, char *c2, char *cA);

typedef struct pessoa{
	char nome[30];
	unsigned short int idade;
	char telefone[15];
}TAD;

int main(){
	void *pBuffer = NULL;	//ponteiro void onde fica tudo armazenado
	int *opcao, *qtd, *tam;
	
	pBuffer = (void *)malloc(4 * sizeof(int));		//aloca os 3 inteiros iniciais
	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//numero de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); 	//tamanho do pBuffer
	
	*qtd = 0;
	*tam = (4 * sizeof(int));

	do{
		opcao = (int *)pBuffer;
		tam = (int *)(pBuffer + (2 * sizeof(int)));

		menu(opcao);
		switch(*opcao){
			case 1:
				*tam += sizeof(TAD);	//aumenta tamanho p/ mais um registro
				pBuffer = realloc(pBuffer, *tam);
				inserir(pBuffer);
				break;
			case 2:
				imprimir(pBuffer);
				break;
			case 3:
			case 4:
				pBuffer = realloc(pBuffer, *tam + sizeof(TAD));		//aumenta mais um
				opcao = (int *)pBuffer;
				procurar(pBuffer);
				break;
			//case 5:
				//pBuffer = realloc(pBuffer, *tam + (45*sizeof(char) + sizeof(unsigned short int)) + sizeof(int));	//mais um registrso e mais um int
				//opcao = (int *)pBuffer;
				//insertionSort(pBuffer);
			//	break;
			case 5:
				printf("saindo...\n");
				break;
		}
	}while(*opcao != 5);

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
		//printf("\t5 - insertion sort\n");
		printf("\t5 - exit\n");
		printf("opcao: ");
		scanf("%d", opcao);
	}while((*opcao <= 0) || (*opcao > 5));
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
	novaPessoa = (TAD *)(pBuffer + 4 * sizeof(int) + *qtd * sizeof(TAD));

	*qtd += 1;
	
	//lê os dados
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
	int *qtd, *i;
	TAD *novaPessoa;
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	i = (int *)(pBuffer + (3 * sizeof(int)));
	
	for(*i = 0; *i < *qtd; *i += 1){
		novaPessoa = (TAD *)(pBuffer + 4 * sizeof(int) + *i * sizeof(TAD));		
		
		//imprime os dados
		printf("Registro %d\n", *i);
		printf("\tNome....: ");
		printf("%s\n", novaPessoa->nome);
		printf("\tidade...: %hu\n", novaPessoa->idade);
		printf("\tTelefone: ");
		printf("%s\n", novaPessoa->telefone);
		printf("----------------------------------\n");
	}
}

void procurar(void *pBuffer){
	int *opcao, *qtd, *tam, *i;
	//char *cNome,  *cTelefone;
	//char *cNomeDigitado;	//char aux para ler o nome do registro a ser excluido ou impresso
	//unsigned short int *idade;

	TAD *aux;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + (3 * sizeof(int)));

	if(*qtd == 0){
		printf("A agenda esta vazia");
		pBuffer = realloc(pBuffer, *tam);
		return;
	}

	aux = (TAD *)(pBuffer + 4 * sizeof(int) + *qtd * sizeof(TAD));
		
	getchar();
	printf("Nome: ");
	lerString(aux->nome);

	//cNomeDigitado = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int))); //aponta pro inicio dnv

	for(*i = 0; *i < *qtd; *i += 1){
		cNome = (char *)(pBuffer + 4 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));
		cNomeDigitado = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int)));

		while((*cNome == *cNomeDigitado) && (*cNome  != '\0') && (*cNomeDigitado != '\0')){
			cNome += sizeof(char);
			cNomeDigitado += sizeof(char);
		}
		//se sair do while é porque: 1 - os caracter comparados são diferentes, então não é este o registro que estamos procurando
		//2 - chegou ao fim de um dos nomes ou dos dois
		if(*cNome == *cNomeDigitado){			//se chegar aqui e for verdadeiro o if, quer dizer que os nomes são iguais
			cNome = (char *)(pBuffer + 4 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));	//aponta pro ini de novo
			idade = (unsigned short int *)(cNome + 30 * sizeof(char));
			cTelefone = (char *)(idade + sizeof(unsigned short int));
			break;	//sai do for
		}
		else if(*i == (*qtd -1)){
			printf("Registro não encontrado ");
			pBuffer = realloc(pBuffer, *tam);	//volta para o tamanho original
			return;
		}
	}

	opcao = (int *)pBuffer;
	char *c2;	//char para o nome do registro apos o que vai ser excluido

	if(*opcao == 3){
		printf("Registro %d\n", *i);
		printf("\tNome....: ");
		imprimirString(cNome);
		printf("\tidade...: %hu\n", *idade);
		printf("\tTelefone: ");
		imprimirString(cTelefone);
	}
	else if(*opcao == 4){
		c2 = (char *)(cNome + 45*sizeof(char) + sizeof(unsigned short int));
		cNomeDigitado = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int)));

		for(; *i < *qtd; *i += 1){
			cNome = (char *)(pBuffer + 4 * sizeof(int) + (*i) * (45*sizeof(char) + sizeof(unsigned short int)));
			c2 = (char *)(cNome + 45*sizeof(char) + sizeof(unsigned short int));
			trocarRegistros(cNome, c2, cNomeDigitado);
		}

		*tam -= (45*sizeof(char) + sizeof(unsigned short int));
		*qtd -= 1;
	}

	pBuffer = realloc(pBuffer, *tam);
	
}

void trocarRegistros(char *c1, char *c2, char *cA){
	char *t1, *t2, *tA;
	unsigned short int *i1, *i2, *iA;
	i1 = (unsigned short int *)(c1 + 30*sizeof(char));
	i2 = (unsigned short int *)(c2 + 30*sizeof(char));
	iA = (unsigned short int *)(cA + 30*sizeof(char));
	
	t1 = (char *)(i1 + sizeof(unsigned short int));
	t2 = (char *)(i2 + sizeof(unsigned short int));
	tA = (char *)(iA + sizeof(unsigned short int));
	
	//trocar os nomes dos registros
	trocarStringsDeRegistros(c1, c2, cA);
	
	//trocar as idades dos registros
	*iA = *i1;
	*i1 = *i2;
	*i2 = *iA;

	//trocar os telefone dos geristros
	trocarStringsDeRegistros(t1, t2, tA);
}

void trocarStringsDeRegistros(char *c1, char *c2, char *cA){
	do{
		*cA =  *c1;
		*c1 = *c2;
		*c2 = *cA;

		c1 += sizeof(char);
		c2 += sizeof(char);
	}while( (*(c2 - sizeof(char)) != '\0') && (*(c1 -  sizeof(char)) != '\0') );

	if(*(c2 - sizeof(char)) == '\0'){
		while(*(c1 -  sizeof(char)) != '\0'){
		*cA =  *c1;
		*c1 = *c2;
		*c2 = *cA;

		c1 += sizeof(char);
		c2 += sizeof(char);
		}
	}

	else if(*(c1 - sizeof(char)) == '\0'){
		while(*(c2 -  sizeof(char)) != '\0'){
		*cA =  *c1;
		*c1 = *c2;
		*c2 = *cA;

		c1 += sizeof(char);
		c2 += sizeof(char);
		}
	}
}

void insertionSort(void *pBuffer){
	/*//primeirompor idade
	int *qtd, *i, *j, *tam;
	unsigned short int *iTemp, *iDataI, *iDataJ, *iDataIMaisUm;	//idade 
	char *cTemp, *cDataI, *cDataJ, *cDataIMaisUm, *cAux;				//nome


	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + (3 * sizeof(int)));
	j = (int *)(pBuffer + 3 * sizeof(int) + (*qtd + 1) * (45*sizeof(char) + sizeof(unsigned short int)));
	

	for(*j = 1; *j < *qtd; *j += 1){
		cDataJ = (char *)(pBuffer + 4 * sizeof(int) + *j * (45*sizeof(char) + sizeof(unsigned short int)));	//data[j]
		*i = *j - 1;
		cDataI = (char *)(pBuffer + 4 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));	//data[j]
		iDataI = (unsigned short int *)(cDataJ + 30 * sizeof(char));
		iDataJ = (unsigned short int *)(cDataI + 30 * sizeof(char));

		cTemp = (char *)cDataJ;
		temp = (unsigned short int *)iDataJ;

		while((*i >= 0) && (*temp < *iDataI)){
			cDataIMaisUm = (char *)(pBuffer + 4 * sizeof(int) + (*i + 1) * (45*sizeof(char) + sizeof(unsigned short int)));
			trocarRegistros(cDataIMaisUm, cDataI, ); //cDataIMaisUm = cDataI;

			*i -= 1;
		}

	}


	pBuffer = realloc(pBuffer, *tam);*/
}