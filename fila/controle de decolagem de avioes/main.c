/*
Escreva um programa que simule o controle de uma pista de decolagem de aviões de em um aeroporto.
Neste programa, o usuario deve ser capaz de realizar as seguintes tarefas:
a) Listar o número de aviões aguardando na fila de decolagem;
b) Autorizar a decolagem do primeiro avião da fila;
c) Adicionar um avião à fila de espera;
d) Listar todos os aviões na fila de espera;
e) Listar as características do primeiro avião da fila
*/
 
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

enum opcoes{
	SAIR = 0,
	LISTAR_QTD,
	AUTORIZAR,
	ADD,
	LISTAR_TODOS,
	LISTAR_PRIMEIRO
}opcao;

void menu(void);
Nodo *lerDados(void);
void listarDados(Nodo *dado);
void listarTodos(Queue *fila);
 
int main(){
    Queue *fila = NULL;
    fila = inicializa();
    
    do{
	    menu();
	    switch(opcao){
	    	case LISTAR_QTD:
	    		printf("%d avioes estao auardando na fila de decolagem.\n", fila->quantidade);
	    	
	    		break;
	    	case AUTORIZAR:
	    		if(!empty(fila)){
		    		printf("O aviao %s saiu para a decolagem.\nVRUUUUUUUUM\n", primeiro(fila)->conteudo.nomeAviao);
		    	
		   			free(pop(fila));
	    		}
	    		else
	    			printf("Nenhum aviao na fila\n");
	    		break;
	    	case ADD:
	    		push(fila, lerDados());
	    	
	    		break;
	    	case LISTAR_TODOS:
	    		listarTodos(fila);
	    		
	    		break;
	    	case LISTAR_PRIMEIRO:
	    		listarDados(primeiro(fila));
	    	
	    		break;
	    	case SAIR:
	    		printf("saindo...\n");
	    		break;
	    }
	    
	    if(opcao != 0)
	    	getchar();
    }while(opcao != 0);
    
    clean(fila);
    free(fila);
 	
    return 0;
}

void menu(void){
	do{
		printf("1 - Listar o numero de avioes aguardando na fila de decolagem.\n");
		printf("2 - Autorizar a decolagem do primeiro aviao da fila.\n");
		printf("3 - Adicionar um aviao a fila de espera\n");
		printf("4 - Listar todos os aviões na fila de espera.\n");
		printf("5 - Listar as caracteristicas do primeiro aviao da fila.\n");
		printf("0 - sair\n");
		printf("opcao: ");
		scanf("%d", &opcao);
		
		system("clear");
		if(opcao > 5 || opcao < 0)
			printf("\t\tOpcao invalida, tente novamente\n\n");
	}while(opcao > 5 || opcao < 0);
}
 
Nodo *lerDados(void){
    Nodo *new = NULL;
    new = (Nodo *)malloc(sizeof(Nodo));
    new->next = NULL;
    new->previus = NULL;
 
    printf("Aviao: ");
 	scanf("%s", new->conteudo.nomeAviao);
    printf("Capacidade: ");
    scanf("%d", &new->conteudo.capacidade);
 
    return new;
}

void listarDados(Nodo *dado){
	printf("\nAviao: %s\n", dado->conteudo.nomeAviao);
	printf("Capacidade: %d pessoas\n", dado->conteudo.capacidade);
}

void listarTodos(Queue *fila){
	Queue *aux = NULL;
	aux = inicializa();
	
	while(!empty(fila)){
		listarDados(primeiro(fila));
		push(aux, pop(fila));
	}
	
	while(!empty(aux))
		push(fila, pop(aux));
}
 
 
//FUNCOES QUEUE
Queue *inicializa(void){
    Queue *fila = NULL;
 
    if((fila = (Queue *)malloc(sizeof(Queue))) == NULL){
        printf("ERRO AO CRIAR FILA\n");
        exit(1);
    }
    fila->first = NULL;
    fila->last = NULL;
    fila->quantidade = 0;
 
    return fila;
}
 
void push(Queue *fila, Nodo *new){
    if(empty(fila)){    //fila vazia
        new->next = NULL;
        new->previus = NULL;
        fila->first = new;
        fila->last = new;
        fila->quantidade += 1;
        return;
    }
 	
    Nodo *ultimo = NULL;
    
    ultimo = fila->last;
    ultimo->previus = new;
    new->next = ultimo;
    new->previus = NULL;
 
    fila->last = new;
    fila->quantidade += 1;
}
 
Nodo *pop(Queue *fila){
    if(empty(fila)){
        printf("Fila vazia\n");
        return NULL;
    }
 
    Nodo *primeiro = NULL;
    Nodo *newPrimeiro = NULL;
    
    primeiro = fila->first;
    
    if(!primeiro->previus){ //só um na fila
    	fila->first = NULL;
    	fila->last = NULL;  	
    }
    else{
    	newPrimeiro = primeiro->previus;
    	newPrimeiro->next = NULL;
    	fila->first = newPrimeiro;
    }
 
    primeiro->previus = NULL; //limpa pra quem o primeiro apontava
    
    fila->quantidade -= 1;
    return primeiro;
}
 
Nodo *primeiro(Queue *fila){
    if(empty(fila)){
        printf("Fila vazia\n");
        return NULL;
    }
 
    return fila->first;
}
 
int empty(Queue *fila){
    if(!fila->first && !fila->last){
        return 1;
    }
 
    if(!fila->first || !fila->last){
        printf("ERRO!\n");
        exit(1);
    }
    
    return 0;
}
 
void clean(Queue *fila){
    while(!empty(fila))
        free(pop(fila));
}
 
