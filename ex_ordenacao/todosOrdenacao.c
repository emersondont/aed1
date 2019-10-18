/**
*	CASO DE TESTES
* para 10000 numeros
*
* insertionSort :	0.185527
* selectSort :		0.241906 
* bubbleSort :		0.529248
* quickSort :		0.005730
* mergeSort :		0.005041
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencherVetor(int *vetor, int n);
void swap(int *n1, int *n2);

void insertionSort(int *vetor, int n);
void selectSort(int *vetor, int n);				//sem variavel
void bubbleSort(int *vetor, int n);				//sem variavel
void quickSort(int *left, int *right);			//sem variavel
void mergeSort(int *comeco, int *fim);			//sem variavel
void merge(int *comeco, int *meio, int *fim);	//sem variavel

int main(){
	clock_t tempo = clock();
	int n = 10000;
	int vetor[10000];

	preencherVetor(vetor, n);

	//insertionSort(vetor, n);
	//selectSort(vetor, n);
	//bubbleSort(vetor, n);
	//quickSort(vetor, &vetor[n-1]);
	mergeSort(vetor, &vetor[n-1]);

	//imprimir numeros
/*
	for(int i = 0; i < n; i++)
		printf("%d ", vetor[i]);
	puts("");
*/
	printf("Tempo: %f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);

	return 0;
}

void preencherVetor(int *vetor, int n){
	int i;
	for(i = 0; i < n; i++)
		vetor[i] = rand() % n;
}

void swap(int *n1, int *n2){
	if(*n1 != *n2){
		*n1 ^= *n2;
		*n2 ^= *n1;
		*n1 ^= *n2;
	}
}

void insertionSort(int *vetor, int n){
	int i, j, aux;

	for(j = 1; j < n; j++){
		i = j - 1;
		aux = vetor[j];
		while((i >= 0) && (vetor[i] > aux)){
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = aux;
	}
}

void selectSort(int *vetor, int n){
	int *i, *j, *menor;

	for(i = vetor; i < &vetor[n-1]; i++){
		menor = i;
		for(j = i+1; j < &vetor[n]; j++){
			if(*j < *menor)
				menor = j;
		}
		swap(i, menor);
	}	
}

void bubbleSort(int *vetor, int n){
	int *i, *j;

	for(i = vetor; i < &vetor[n-1]; i++){
		for(j = i+1; j < &vetor[n]; j++){
			if(*i > *j)
				swap(i, j);
		}
	}
}

void quickSort(int *left, int *right){
	int *i, *j;
	int *meio = (left + (right-left)/2);	//p pegar o do meio, porem poderia pegar qualquer um

	i = left;
	j = right;
	do{
		while(*i < *meio)
			i++;

		while(*j > *meio)
			j--;

		if(j >= i){
			swap(i, j);
			i++;
			j--;
		}
	}while(i <= j);

	if(left < j)
		quickSort(left, j);

	if(i < right)
		quickSort(i, right);
}

void mergeSort(int *comeco, int *fim){
	if(comeco < fim){
		int *meio = (comeco + (fim - comeco)/2);
		mergeSort(comeco, meio);
		mergeSort(meio+1, fim);
		merge(comeco, meio, fim);
	}
}
void merge(int *comeco, int *meio, int *fim){
	int *i, *j, *vetorAux, *auxId;
	i = comeco;
	j = meio + 1;

	vetorAux = (int *)malloc((fim - comeco + 1) * sizeof(int));
	auxId = vetorAux;		//aponta pro inicio do vetor aux

	while((i <= meio) && (j <= fim)){
		if(*i < *j){
			*auxId = *i;
			i++;
		}else{
			*auxId = *j;
			j++;
		}
		auxId++;
	}

	while(i <= meio){		//caso ainda haja elementos na primeira parte
		*auxId = *i;
		auxId++;
		i++;
	}

	while(j <= fim){		//caso ainda haja elementos na segunda parte
		*auxId = *j;
		auxId++;
		j++;
	}

	auxId = vetorAux;		//aponta pro inicio do vetor aux dnv

	for(i = comeco; i <= fim; i++){		//move os elementos de volta para o vetor original
		*i = *auxId;
		auxId++;
	}

	free(vetorAux);
}
