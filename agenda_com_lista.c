#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nome[30];
	int idade;
}SDado;

typedef struct {
	SDado info;
	struct SNodo *next;
}SNodo;

typedef struct {
	SNodo *pFist;
}SLista;

void inserir(SLista *lista);

int main(){
	SLista *lista = NULL;

	inserir(lista);

	return 0;
}

void inserir(SLista *lista){
	if(lista == NULL){
		lista = (SLista *)malloc(sizeof(SLista));
		lista->pFist = (SNodo *)malloc(sizeof(SNodo));
		lista->pFist->next = NULL;

		scanf("%s", lista->pFist->info.nome);
		scanf("%d", &lista->pFist->info.idade);
	}



}
