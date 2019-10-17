#include <stdio.h>
#include <stdlib.h>

void insert(int *vetor, int n, int num);

int main(){
	int num, n = 5;
	int vetor[6] = {1, 2, 4, 5, 6};

	scanf("%d", &num);

	insert(vetor, n, num);

	for(int i = 0; i < n+1; i++)
		printf("%d ", vetor[i]);

	printf("\n");

	return 0;
}

void insert(int *vetor, int n, int num){
	if(num <= vetor[0]){
		for(int i = n; i > 0; i--)
			vetor[i] = vetor[i-1];

		vetor[0] = num;
		return;
	}

	else if(num >= vetor[n-1]){
		vetor[n] = num;
		return;
	}

	//se tem que colocar no meio
	int i;
	for(i = 1; i < n-1; i++){
		if(num <= vetor[i])
			break;		
	}

	for(int j = n; j > i; j--)
		vetor[j] = vetor[j-1];

	vetor[i] = num;

}
