//receber valores em um vetor e imprimir ORDENADO se o vetor estiver em ordem crescente
#include <stdio.h>
#include <stdlib.h>

int bubbleSort(int *vetor, int n);

int main(){
	int n = 5;
	int vetor[5] = {1, 2, 3, 4, 5};

	if(bubbleSort(vetor, n)){
		for(int i = 0; i < n; i++)
			printf("%d ", vetor[i]);
	}
	puts("");

	return 0;
}

int bubbleSort(int *vetor, int n){
	int i, j;
	int teste = 1;

	for(i = 0; i < n-1; i++){
		teste = 1;
		for(j = i+1; j < n; j++){
			if(vetor[i] > vetor[j]){
				teste = 0;
				break;
			}
		}
		if(!teste)
			break;
	}

	return teste;
}

