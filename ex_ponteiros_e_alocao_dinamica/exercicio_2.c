#include <stdio.h>
#include <stdlib.h>

int *criar(int n);
void imprimir(int *vetor, int n);
void liberar(int *vetor);

int main(){
	int n, i;
	int *vetor;
	scanf("%d", &n);
	vetor = criar(n);

	for(i = 0; i < n; i++)
		scanf("%d", &vetor[i]);

	imprimir(vetor, n);
	liberar(vetor);
	return 0;
}

int *criar(int n){
	int *vetor;
	vetor = (int *)malloc(n*sizeof(int));
	return vetor;
}
void imprimir(int *vetor, int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", vetor[i]);

	printf("\n");
}
void liberar(int *vetor){
	free(vetor);
}
