#include <stdio.h>
#include <stdlib.h>

void ler(int **matriz, int m, int n);
void imprimir(int **matriz, int m, int n);
void liberarMemoria(int **matriz, int m);

int main(){
	int **matriz;
	int m, n, i, j;

	printf("M e N: ");
	scanf("%d %d", &m, &n);

	//alocando o vetor
	matriz = (int **)malloc(m * sizeof(int *));

	//alocando cada linha da matriz
	for(i = 0; i < m; i++)
		matriz[i] = (int *)malloc(n * sizeof(int));

	ler(matriz, m, n);
	imprimir(matriz, m, n);
	liberarMemoria(matriz, m);

	return 0;
}

void ler(int **matriz, int m, int n){
	int i, j;

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			//matriz[i][j] = i + j;
			scanf("%d", &matriz[i][j]);
		}
	}
}

void imprimir(int **matriz, int m, int n){
	int i, j;

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			printf("%d\t", matriz[i][j]);

		printf("\n");
	}
}

void liberarMemoria(int **matriz, int m){
	int i;

	for(i = 0; i < m; i++)
		free(matriz[i]);

	free(matriz);
}