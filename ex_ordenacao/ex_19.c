//ler n nomes e ordenar por tamanho
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerString(char *string);
void selectionSort(char **vetor, int n);
void limpaMem(char **vetor, int n);
void recebe(char *n1, char *n2);

int main(){
	char **vetorNomes;
	int n, i;
	
	scanf("%d", &n);
	getchar();
	vetorNomes = (char **)malloc(n * sizeof(char *));	

	for(i = 0; i < n; i++){
		vetorNomes[i] = (char *)malloc(sizeof(char));
		lerString(vetorNomes[i]);
	}

	selectionSort(vetorNomes, n);

	puts("");
	for(i = 0; i < n; i++)
		puts(vetorNomes[i]);
	

	limpaMem(vetorNomes, n);

	return 0;
}

void selectionSort(char **vetor, int n){
	int i, j;
	char *aux;

	aux = (char *)malloc(sizeof(char));

	for(j = 1; j < n; j++){
		i = j - 1;

		recebe(aux, vetor[j]);
		while((i >= 0) && (strlen(aux) < strlen(vetor[i]))){
			recebe(vetor[i+1], vetor[i]);
			i--;
		}

		recebe(vetor[i+1], aux);
	}

	free(aux);
}

void recebe(char *n1, char *n2){
	int i;
	n1 = (char *)realloc(n1, strlen(n2) * sizeof(char));
	strcpy(n1, n2);
}

void lerString(char *string){
	char c;
	int cont = 0;

	while((c = getchar()) != '\n'){
		string[cont++] = c;
		string = (char *)realloc(string, (cont + 1) * sizeof(char));
	}
	string[cont] = '\0';
}

void limpaMem(char **vetor, int n){
	int i;
	for(i = 0; i < n; i++)
		free(vetor[i]);

	free(vetor);
}
