//ordenar as letras de uma string em ordem decrescente, usando o quick sort
#include <stdio.h>
#include <stdlib.h>

void quickSort(char *string, int left, int right);

int main(){
	char *string, c;
	int cont = 0;

	string = (char *)malloc(sizeof(char));
	while((c = getchar()) != '\n'){
		string[cont++] = c;
		string = (char *)realloc(string, (cont + 1) * sizeof(char));
	}
	string[cont] = '\0';

	quickSort(string, 0, cont-1);

	puts(string);
	return 0;
}

void quickSort(char *string, int left, int right){
	int i, j;
	char aux, meio = string[(left+right)/2];
	i = left;
	j = right;

	do{
		while(meio < string[i])
			i++;

		while(meio > string[j])
			j--;

		if(i <= j){
			aux = string[i];
			string[i] = string[j];
			string[j] = aux;
			i++;
			j--;
		}

	}while(i <= j);

	if(left < j)
		quickSort(string, left, j);

	if(i < right)
		quickSort(string, i, right);
	
}
