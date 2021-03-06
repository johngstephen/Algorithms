// QuickSort.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define numListas 50

// Fun��o para trocar dois elementos
void exchange(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* Esta fun��o utiliza o �ltimo elemento como pivot, colocando
o mesmo na sua posi��o correcta na lista organizado, sendo que,
todos os elementos mais pequenos que o pivot, s�o colocados �
esquerda do mesmo e os maiores � direita */
int partition(int lista[], int low, int high)
{
	int pivot = lista[high];    // pivot
	int i = (low - 1);  // �ndice do elemento mais pequeno

	for (int j = low; j <= high - 1; j++)
	{
		// Se o elemento actual � igual ou inferior ao pivot
		if (lista[j] <= pivot)
		{
			i++;
			exchange(&lista[i], &lista[j]);
		}
	}
	exchange(&lista[i + 1], &lista[high]);
	return (i + 1);
}

void quickSort(int lista[], int low, int high)
{
	if (low < high)
	{
		int indice = partition(lista, low, high);

		// Organizar os elementos separadamente
		// antes e ap�s a parti��o
		quickSort(lista, low, indice - 1);
		quickSort(lista, indice + 1, high);
	}
}

int main()
{
	int tamanho = 0;
	int iteracoes = 31;
	int incremento = 4000;
	FILE *f;
	f = fopen("C:\\Algoritmos\\C\\QuickSortOp.txt", "w+");

	for (int j = 0; j < iteracoes; j++) {
		int ciclo = 1;
		int num;
		/* Vari�veis usadadas no c�lculo da m�dia e desvio padr�o */
		float soma = 0;
		float variancia;
		float somaVar = 0;
		float somaTempos = 0;
		float tempos[numListas];

		printf("\nITERACAO n.%d", j + 1);

		for (int k = 0; k < numListas; k++) {
			srand(time(NULL));
			int *lista;
			lista = malloc(sizeof(int) * tamanho);

			for (int i = 0; i < tamanho; i++) {
				num = rand() % 1000;
				lista[i] = num;
			}
			/*
			printf("\n\nLista nao-organizada de tamanho %d ::\n", tamanho);
			printArray(lista, tamanho);
			*/
			printf("\n");
			clock_t inicio = clock();
			quickSort(lista, 0, tamanho - 1);
			clock_t fim = clock();

			printf("Lista n.%d de tamanho %d ::", ciclo, tamanho);
			/*
			printf("\n");
			printArray(lista, tamanho);
			printf("\n");
			*/
			float tempo = ((float)(fim - inicio) / CLOCKS_PER_SEC);
			somaTempos += tempo;
			tempos[k] = tempo;
			printf(" %f s", tempo);
			ciclo++;
		}
		float media = somaTempos / (float)numListas;

		for (int i = 0; i < numListas; i++)
		{
			somaVar = somaVar + pow((tempos[i] - media), 2);
		}

		variancia = somaVar / (float)numListas;
		float desvioP = sqrt(variancia);

		printf("\n\nMedia para %d listas de %d elementos :: %f s\n", numListas, tamanho, media);
		printf("Desvio para %d listas de %d elementos :: %f s\n", numListas, tamanho, desvioP);
		fprintf(f, "%d %f %f\n", tamanho, media, desvioP);
		tamanho += incremento;
	}
	fclose(f);
	printf("\nPrograma terminado. Pressione qualquer tecla para fechar a janela.\n");
	getchar();
	return 0;
}

