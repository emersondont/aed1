/*
AGENDA SOMENTE COM PONTEIROS / DISCIPLINA DE ALGORITMOS E ESTRUTURA DE DADOS

Registro:
{
 	char nome[30];
	unsigned short int idade;	//pq ningém vai ter mais de 65.535 anos
	char telefone[15];
} 	

tamanho de cada registro: (35*sizeof(char) + sizeof(unsigned short int)

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
void imprimirString(char *c);
void inserir(void *pBuffer);
void imprimir(void *pBuffer);
void procurar(void *pBuffer);
void trocarRegistros(char *c1, char *c2, char *cA);

int main(){
	void *pBuffer = NULL;	//ponteiro void onde fica tudo armazenado
	int *opcao, *qtd, *tam;
	
	pBuffer = (void *)malloc(4 * sizeof(int));		//aloca os 3 inteiros iniciais
	qtd = (int *)(pBuffer + (1 * sizeof(int)));		//numero de elementos
	tam = (int *)(pBuffer + (2 * sizeof(int))); 	//tamanho do pBuffer
	
	*qtd = 0;
	*tam = (4 * sizeof(int));

	//lerArq(pBuffer);

	do{
		opcao = (int *)pBuffer;
		tam = (int *)(pBuffer + (2 * sizeof(int)));

		menu(opcao);
		switch(*opcao){
			case 1:
				*tam += (45*sizeof(char) + sizeof(unsigned short int));	//aumenta tamanho p/ mais um registro
				pBuffer = (void *)realloc(pBuffer, *tam);
				inserir(pBuffer);
				break;
			case 2:
				imprimir(pBuffer);
				break;
			case 3:
			case 4:
				pBuffer = realloc(pBuffer, *tam + 30*sizeof(char));		//aumenta mais um tam nome
				opcao = (int *)pBuffer;
				procurar(pBuffer);
				break;
			case 5:
				//salvaArq(pBuffer);
				printf("saindo...\n");
				break;
		}
	}while(*opcao != 5);

	free(pBuffer);

	return 0;
}

void menu(int *opcao){
	printf("\n# MENU DE OPCOES #\n");
	do{
		printf("\t1 - insert\n");
		printf("\t2 - print\n");
		printf("\t3 - search for\n");
		printf("\t4 - delete\n");
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
	cNome = (char *)(pBuffer + 4 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int)));	//1º caracter do nome
	idade = (unsigned short int *)(cNome + 30 * sizeof(char));
	cTelefone = (char *)(idade + sizeof(unsigned short int));

	*qtd += 1;
	
	//lê os dados
	getchar();
	printf("Nome: ");
	lerString(cNome);
	printf("Idade: ");
	scanf("%hu", idade);
	getchar();
	printf("Telefone: ");
	lerString(cTelefone);
}

void imprimir(void *pBuffer){
	char *cNome, *cTelefone;
	unsigned short int *idade;
	int *qtd, *i;
	
	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	i = (int *)(pBuffer + (3 * sizeof(int)));
	
	for(*i = 0; *i < *qtd; *i += 1){
		//posiciona os ponteiros
		cNome = (char *)(pBuffer + 4 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));	//1º caracter do nome
		idade = (unsigned short int *)(cNome + 30 * sizeof(char));
		cTelefone = (char *)(idade + sizeof(unsigned short int));
		
		//imprime os dados
		printf("Registro %d\n", *i);
		printf("\tNome....: ");
		imprimirString(cNome);
		printf("\tidade...: %hu\n", *idade);
		printf("\tTelefone: ");
		imprimirString(cTelefone);
		printf("----------------------------------\n");
	}
}

void procurar(void *pBuffer){
	int *opcao, *qtd, *tam, *i;
	char *cNome, *cNomeDigitado, *cTelefone;
	unsigned short int *idade;

	qtd = (int *)(pBuffer + (1 * sizeof(int)));
	tam = (int *)(pBuffer + (2 * sizeof(int)));
	i = (int *)(pBuffer + (3 * sizeof(int)));

	if(*qtd == 0){
		printf("A agenda esta vazia");
		return;
	}

	cNomeDigitado = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int))); //aponta pro inicio do campo vazio que recem foi realocado
	
	getchar();
	printf("Nome: ");
	lerString(cNomeDigitado);

	cNomeDigitado = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int))); //aponta pro inicio dnv

	for(*i = 0; *i < *qtd; *i += 1){
		cNome = (char *)(pBuffer + 4 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));
		
		while((*cNome == *cNomeDigitado) && (*cNome  != '\0') && (*cNomeDigitado != '\0')){
			cNome += sizeof(char);
			cNomeDigitado += sizeof(char);
		}
		//se sair do while é porque: 1 - os caracter comparados são diferentes, então não é este o registro que estamos procurando
		//2 - chegou ao fim de um dos nomes ou dos dois
		if(*cNome == *cNomeDigitado){			//se chegar aqui e for verdadeiro o if, quer dizer que os nomes são iguais
			//pBuffer = realloc(pBuffer, *tam);	//volta para o tamanho original
			cNome = (char *)(pBuffer + 4 * sizeof(int) + *i * (45*sizeof(char) + sizeof(unsigned short int)));	//aponta pro ini de novo
			idade = (unsigned short int *)(cNome + 30 * sizeof(char));
			cTelefone = (char *)(idade + sizeof(unsigned short int));
			break;	//sai do for
		}
		else if(*i == (*qtd -1)){
			printf("Registro não encontrado ");
			printf("%c %c", *cNome, *cNomeDigitado);
			pBuffer = realloc(pBuffer, *tam);	//volta para o tamanho original
			return;
		}
	}

	opcao = (int *)pBuffer;
	char *c2;

	if(*opcao == 3){
		printf("Registro %d\n", *i);
		printf("\tNome....: ");
		imprimirString(cNome);
		printf("\tidade...: %hu\n", *idade);
		printf("\tTelefone: ");
		imprimirString(cTelefone);
	}
	else if(*opcao == 4){
		printf("remover o cara");
		c2 = (cNome + 45*sizeof(char) + sizeof(unsigned short int));
		//cNomeDigitado = (char *)(pBuffer + 3 * sizeof(int) + *qtd * (45*sizeof(char) + sizeof(unsigned short int)));
		//trocarRegistros(cNome, cNomeDigitado, c2);
		imprimirString(cNome);
		imprimirString(c2);
	}
	

}

void trocarRegistros(char *c1, char *c2, char *cA){

	do{
		*cA =  *c1;
		*c1 = *c2;
		*c2 = *cA;

		c1 += sizeof(char);
		c2 += sizeof(char);
		printf("\n%c %c", *c1, *c2);
	}while( ((*c2 - sizeof(char)) != '\0') && (*(c1 -  sizeof(char)) != '\0') );




}