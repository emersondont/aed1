#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Agenda{
	char nome[50];
	double numero_celular;
	struct Agenda *prox;
}agenda;

agenda *cria_lista();
int menu();
void insere(agenda *ini);
void listar_todos(agenda *ini);
void imprime_dados(agenda *alguem);
void excluir(agenda *ini);
void listar_um(agenda *ini);
void ler_string(char string[50]);

int main(){
	int opcao;
	agenda *ini;
	ini = cria_lista();

	do{
		opcao = menu();
		switch(opcao){
			case 1:
				insere(ini);
				break;
			case 2:
				excluir(ini);
				break;
			case 3:
				listar_um(ini);
				break;
			case 4:
				listar_todos(ini);
				break;
			case 5:
			    printf("ate mais");
				break;
		}
	}while(opcao != 5);

	return 0;
}
agenda *cria_lista(){
	agenda *cabeca;
	cabeca = (agenda *)malloc(sizeof(agenda));
	cabeca->prox = NULL;

	return cabeca;
}

int menu(){
	int op;
	do{
		printf("#########_AGENDA_#########\n");
		printf("\t1- inserir\n");
		printf("\t2- excluir\n");
		printf("\t3- listar um\n");
		printf("\t4- listar todos\n");
		printf("\t5- sair\n");
		printf("opcao: ");
		scanf("%d", &op);
	}while((0 > op) || (op > 6));

	return op;
}

void insere(agenda *ini){
	char c;
	int i = 0;
	agenda *novo, *fim;
	novo = (agenda *)malloc(sizeof(agenda));

	for(fim = ini; fim -> prox != NULL; fim = fim->prox);

	novo->prox = NULL;
	fim->prox = novo;
    getchar();    //tava com problema, tive que colocar esse getchar
	printf("digite o nome: ");
    //scanf("%s", novo->nome);
    ler_string(novo->nome);
	printf("digite o numero: ");
	scanf("%lf", &novo->numero_celular);
}

void listar_todos(agenda *ini){
	agenda *aux;

	for(aux = ini->prox; aux != NULL; aux = aux->prox)
		imprime_dados(aux);
}

void imprime_dados(agenda *alguem){
	printf("\tNome: %s\n", alguem->nome);
	printf("\tNumero: %.0lf\n\n", alguem->numero_celular);
}

void excluir(agenda *ini){
    char nome[50];
	agenda *retirar, *aux;
    
    getchar();
	printf("nome: ");
	//scanf("%s", nome);
	ler_string(nome);
	

	for(retirar = ini->prox; retirar != NULL; retirar = retirar->prox){
		if(strcmp(nome, retirar->nome) == 0){
			for(aux = ini; aux->prox != retirar; aux = aux->prox);

			aux->prox = retirar->prox;
			free(retirar);
			break;
		}
	}

}

void listar_um(agenda *ini){
	char nome[50];
	int i = 0;
	char c;

	agenda *imprimir;
	
	getchar();
	printf("nome: ");
	//scanf("%s", nome);
	ler_string(nome);
	
	for(imprimir = ini->prox; imprimir != NULL; imprimir = imprimir->prox){
		if(strcmp(nome, imprimir->nome) == 0)
		    imprime_dados(imprimir);
	}
}

void ler_string(char string[50]){
    int i = 0;
    char c;
    
    while((c = getchar()) != '\n'){
      string[i] = c;
      i++;
    }
    string[i] = '\0';
}
