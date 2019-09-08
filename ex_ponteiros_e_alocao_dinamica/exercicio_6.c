#include <stdio.h>
#include <stdlib.h>

struct dadosPessoais{
	char nome[21];
	char dataNascimento[11];
	char cpf[12];
};

typedef struct dadosPessoais TAD;

void lerDados(TAD *pessoa);
void imprimirDados(TAD pessoa);

int main(){
	TAD pessoa;

	lerDados(&pessoa);
	imprimirDados(pessoa);


	return 0;
}

void lerDados(TAD *pessoa){
	printf("Nome: ");
	fgets(pessoa->nome, 21, stdin);
	printf("Data de nascimento: ");
	fgets(pessoa->dataNascimento, 12, stdin);
	printf("Cpf: ");
	fgets(pessoa->cpf, 13, stdin);
}

void imprimirDados(TAD pessoa){
	printf("Nome: %sData de nascimento: %sCpf: %s", pessoa.nome, pessoa.dataNascimento, pessoa.cpf);
}