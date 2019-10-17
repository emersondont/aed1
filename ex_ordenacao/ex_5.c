//merge sort, decrescente
#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *vetor, int comeco, int fim);
void merge(int *vetor, int comeco, int meio, int fim);

int main(){
	int *vetor, i, n = 1;
	vetor = (int *)malloc(sizeof(int));

	//le os numeros
	printf("Digite os numeros, -1 p sair\n");
	for(i = 0;;i++, n++){
		vetor = (int *)realloc(vetor, n * sizeof(int));
		scanf("%d", &vetor[i]);
		if(vetor[i] == -1){
			n--;
			vetor = (int *)realloc(vetor, n * sizeof(int));
			break;
		}
	}

	mergeSort(vetor, 0, n-1);

	//imprime os numeros
	for(i = 0; i < n; i++)
		printf("%d ", vetor[i]);

	printf("\n");

	free(vetor);
	return 0;
}

void mergeSort(int *vetor, int comeco, int fim){
	if(comeco < fim){
		int meio = (comeco + fim)/2;
		mergeSort(vetor, comeco, meio);
		mergeSort(vetor, meio+1, fim);
		merge(vetor, comeco, meio, fim);
	}
}

void merge(int *vetor, int comeco, int meio, int fim){
	int i, j, tam, *vetorAux, indexAux;
	i = comeco;
	j = meio + 1;
	indexAux = 0;
	tam = fim - comeco + 1;

	vetorAux = (int *)malloc(tam * sizeof(int));

	while((i <= meio) && (j <= fim)){
		if(vetor[i] > vetor[j])
			vetorAux[indexAux++] = vetor[i++];
		else
			vetorAux[indexAux++] = vetor[j++];
	}

	while(i <= meio)					//caso ainda haja na elementos na primeira parte
		vetorAux[indexAux++] = vetor[i++];

	while(j <= fim)						//caso ainda haja na elementos na segunda parte
		vetorAux[indexAux++] = vetor[j++];

	for(i = comeco; i <= fim; i++)		//move os elementos de volta para o vetor original
        vetor[i] = vetorAux[i - comeco];
    
	free(vetorAux);
}
