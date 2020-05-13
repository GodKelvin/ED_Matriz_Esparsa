/*Author: Kelvin Lehrback Guilherme
Disciplina: Estrutuda de Dados
Professor: Flavio Lamas
Curso: BSI - IFES Campus Serra*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrizEsparsa.h"

int main(int argc, char *argv[])
{
	//Declaracao de variaveis
	int dimensaoM1, dimensaoM2, lin, col; 
	float valor;

	//Abrindo o primeiro arquivo da matriz
	FILE* arquivoM1 = fopen(argv[1], "rt");
	FILE* arquivoM2 = fopen(argv[2], "rt");

	//Primeira linha do arquivo: dimensao da matriz
	fscanf(arquivoM1, "%d" , &dimensaoM1);
	fscanf(arquivoM2, "%d" , &dimensaoM2);

	//Criando as matrizes
	Matriz* matriz1 = criaMatriz(dimensaoM1);
	Matriz* matriz2 = criaMatriz(dimensaoM2);

	//Lendo e guardando informacoes do arquivo 1
	while((fscanf(arquivoM1, "%d;%d;%f" , &lin, &col, &valor)) != EOF)
	{
		matriz1 = insereElemento(matriz1, valor, lin, col);
	}
	fclose(arquivoM1);

	//Lendo e guardando informacoes do arquivo 2
	while((fscanf(arquivoM2, "%d;%d;%f" , &lin, &col, &valor)) != EOF)
	{
		matriz2 = insereElemento(matriz2, valor, lin, col);
	}
	fclose(arquivoM2);

	//Somando as duas matrizes
	somaMatriz(matriz1, matriz2);

	freeMatriz(matriz1);
	freeMatriz(matriz2);

	return 0;
}

