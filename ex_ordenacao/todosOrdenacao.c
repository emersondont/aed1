#include <stdio.h>
#include <stdlib.h>

void swap(int *n1, int *n2);
void insertionSort(int *vetor, int n);
void selectSort(int *vetor, int n);
void bubbleSort(int *vetor, int n);
void quickSort(int *vetor, int *left, int *right);

int main(){
	int n = 5;
	int vetor[] = {444, 222, 555, 111, 333};

	//insertionSort(vetor, n);
	//selectSort(vetor, n);
	//bubbleSort(vetor, n);
	quickSort(vetor, vetor, &vetor[n-1]);

	for(int i = 0; i < n; i++)
		printf("%d ", vetor[i]);
	puts("");

	return 0;
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

void selectSort(int *vetor, int n){		//sem variavel
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

void bubbleSort(int *vetor, int n){		//sem variavel
	int *i, *j;

	for(i = vetor; i < &vetor[n-1]; i++){
		for(j = i+1; j < &vetor[n]; j++){
			if(*i > *j)
				swap(i, j);
		}
	}
}

void quickSort(int *vetor, int *left, int *right){		//sem variavel
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
		quickSort(vetor, left, j);

	if(i < right)
		quickSort(vetor, i, right);

}

void swap(int *n1, int *n2){
	if(*n1 != *n2){
		*n1 ^= *n2;
		*n2 ^= *n1;
		*n1 ^= *n2;
	}
}
