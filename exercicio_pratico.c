//Implemente a seguinte função.
//A função deve imprimir os valores que estão no buffer passado por parâmetro.
//Os valores estão intercalados na seguinte ordem: int, float, double. 
//A variável nTotal indica o total de trios (int, float e double) no buffer.

#include <stdio.h>
#include <stdlib.h>

int menu();
void insereBuffer(void *pBuffer, unsigned int *nTotal);
void imprimeBuffer(void *pBuffer, unsigned int nTotal);

int main(){
	void *pBuffer;
	unsigned int nTotal;
	int opcao;

	nTotal = 0;
	pBuffer = malloc((sizeof(int)) + (sizeof(float)) + (sizeof(double)));

	do{
		opcao = menu();
		switch(opcao){
			case 1:
				insereBuffer(pBuffer, &nTotal);
				break;
			case 2:
				imprimeBuffer(pBuffer, nTotal);
				break;
			case 0:
				printf("saindo...\n");
				break;
		}
	}while(opcao != 0);

	free(pBuffer);
	return 0;
}

int menu(){
	int op;
	printf("\nmenu:\n");
	do{
		printf("\t1 - inserir\n");
		printf("\t2 - imprimir\n");
		printf("\t0 - sair\n");
		printf("opcao: ");
		scanf("%d", &op);
	}while((op < 0) || (op > 2));

	return op;
}

void insereBuffer(void *pBuffer, unsigned int *nTotal){
	int tam;
	int *indexInteiro;
	float *indexFloat;
	double *indexDouble;

	tam = (sizeof(int) + sizeof(float) + sizeof(double));
	*nTotal += 1;
	pBuffer = realloc(pBuffer, (*nTotal * tam));

	indexInteiro = (int *)(pBuffer + ((*nTotal - 1) * tam));
	indexFloat = (float *)(pBuffer + ((*nTotal -1) * tam) + sizeof(int));
	indexDouble = (double *)(pBuffer + ((*nTotal -1) * tam) + sizeof(int) + sizeof(float));

	printf("digite um inteiro: ");
	scanf("%d", indexInteiro);
	printf("digite um float: ");
	scanf("%f", indexFloat);
	printf("digite um double: ");
	scanf("%lf", indexDouble);

	//printf("int: %d\n", *(int *)(pBuffer + ((*nTotal - 1) * tam)));
	//printf("float: %f\n", *(float *)(pBuffer + ((*nTotal -1) * tam) + sizeof(int)));
	//printf("double: %lf\n", *(double *)(pBuffer + ((*nTotal -1) * tam) + sizeof(int) + sizeof(float)));
}

void imprimeBuffer(void *pBuffer, unsigned int nTotal){
	unsigned int i;
	int tam;

	tam = (sizeof(int) + sizeof(float) + sizeof(double));
	for(i = 0; i < nTotal; i++){
		printf("%d\n", i);
		printf("int: %d\n", *(int *)(pBuffer + (i * tam)));
		printf("float: %f\n", *(float *)(pBuffer + (i * tam) + sizeof(int)));
		printf("double: %lf\n", *(double *)(pBuffer + (i * tam) + sizeof(int) + sizeof(float)));
	}
}
//TA ERRADOOOO