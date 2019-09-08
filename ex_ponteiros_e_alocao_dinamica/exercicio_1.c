#include <stdio.h>
#include <stdlib.h>

void inserir(int *vetor, int n);

int main(){
	int n, i;
	int *vetor;

	scanf("%d", &n);
	vetor = (int *)malloc(n*sizeof(int));

	inserir(vetor, n);

	for(i = 0; i < n; i++)
		printf("%d ", vetor[i]);
	

	printf("\n");

	free(vetor);

	return 0;
}

void inserir(int *vetor, int n){
	int i;
	
	for(i = 0; i < n; i++)
		scanf("%d", &vetor[i]);

}