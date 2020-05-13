/*Author: Kelvin Lehrback Guilherme
Disciplina: Estrutuda de Dados
Professor: Flavio Lamas
Curso: BSI - IFES Campus Serra*/

#include <stdio.h>
#include <stdlib.h>
#include "matrizEsparsa.h"

//Cell
struct Celula
{
	int lin, col;
	float valor;
	//Proximo elemento da linha / coluna
	struct Celula* proxElemLin;
	struct Celula* proxElemCol;

};

//Somente matriz quadradas
//Matriz
struct MatrizEsparsa
{
	int dimensao;
	//Ponteiro de ponteiros, (Meu vetor de ponteiros)
	struct Celula** cabLinha;
	struct Celula** cabColuna;
};

Matriz* criaMatriz(int nxn)
{
	Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
	matriz->dimensao = nxn;
	matriz->cabLinha = (Cell**) malloc(nxn * sizeof(Cell));
	matriz->cabColuna = (Cell**) malloc(nxn * sizeof(Cell));

	//Atribuindo NULL a todas as posicoes do meu vetor
	for(int i = 0; i < nxn; i++)
	{
		matriz->cabLinha[i] = NULL;
		matriz->cabColuna[i] = NULL;
	}
	return matriz;
}

Cell* criaCelula(float valor, int lin, int col)
{
	Cell* novaCelula = (Cell*) malloc(sizeof(Cell));
	novaCelula->lin = lin;
	novaCelula->col = col;
	novaCelula->valor = valor;
	novaCelula->proxElemLin = NULL;
	novaCelula->proxElemCol = NULL;

	return novaCelula;
}


void freeCell(Cell* celula)
{	
	free(celula);
}

Matriz* insereNovaCelula(Matriz* matriz, float valor, int lin, int col)
{
	//Decremento em um / no arquivo comeca em 1
	lin--;
	col--;

	Cell* novaCelula = criaCelula(valor, lin, col);
	//Verificando se a linha esta vazia
	if(matriz->cabLinha[lin] == NULL)
	{
		matriz->cabLinha[lin] = novaCelula;
	}

	//Operacoes envolvendo a linha
	else
	{
		Cell* celulaAtual = matriz->cabLinha[lin];
		Cell* celulaTopo = celulaAtual;
		Cell* celulaEsquerda = celulaAtual;

		while(celulaAtual->proxElemLin != NULL && celulaAtual->col < col)
		{
			celulaEsquerda = celulaAtual;
			celulaAtual = celulaAtual->proxElemLin;
		}

		//Se a coluna atual for menor que a coluna desejada
		if(celulaAtual->col < col)
		{
			//novaCelula->proxElemLin = celulaAtual->proxElemLin;
			celulaAtual->proxElemLin = novaCelula;
		}

		//Se a coluna atual for maior que a coluna desejada
		else if(celulaAtual->col > col)
		{
			if(celulaAtual != celulaEsquerda)
			{
				celulaEsquerda->proxElemLin = novaCelula;
				novaCelula->proxElemLin = celulaAtual;
			}
			//Unico elemento da linha
			else
			{
				novaCelula->proxElemLin = celulaAtual;
			}
		}

		//Verificando se a minha novaCelula tem a menor coluna
		if(novaCelula->col < celulaTopo->col)
			matriz->cabLinha[lin] = novaCelula;
		
	}
	//Operacoes envolvendo colunas
	if(matriz->cabColuna[col] == NULL)
		matriz->cabColuna[col] = novaCelula;

	else
	{
		Cell* celulaTopo = matriz->cabColuna[col];
		Cell* celulaAtual = celulaTopo;
		Cell* celulaCima = celulaTopo;

		while(celulaAtual->proxElemCol != NULL && celulaAtual->lin < lin)
		{
			celulaCima = celulaAtual;
			celulaAtual = celulaAtual->proxElemCol;
		}

		//Caso tenha apenas um elemento na coluna
		if(celulaAtual->lin < lin)
		{
			celulaAtual->proxElemCol = novaCelula;
		}

		else if(celulaAtual->lin > lin)
		{
			if(celulaAtual != celulaCima)
			{
				celulaCima->proxElemCol = novaCelula;
				novaCelula->proxElemCol = celulaAtual;
			}
			//Unico elemento da coluna
			else
			{
				novaCelula->proxElemLin = celulaAtual;
			}
		}

		//Verificando se a minha novaCelula tem a menor linha
		if(novaCelula->lin < celulaTopo->lin)
			matriz->cabColuna[col] = novaCelula;

	}

	return matriz;

}

int celulaExiste(Matriz* matriz, int lin, int col)
{
	//Decremento em um / no arquivo comeca em 1
	lin--;
	col--;
	//0 = nao existe / 1 = existe
	int i = 0;
	Cell* celulaAtual = matriz->cabLinha[lin];
	while(celulaAtual != NULL)
	{
		if(celulaAtual->col == col)
		{
			i = 1;
			break;
		}
		else
		{
			celulaAtual = celulaAtual->proxElemLin;
		}
	}

	return  i;
}

Matriz* insereElemento(Matriz* matriz, float valor, int lin, int col)
{
	//Se o valor igual a 0, eu removo o elemento
	if(valor == 0)
	{
		matriz = removeElemento(matriz, lin, col);
		return matriz;
	}

	//Verificando se a celula jah existe
	int existe = celulaExiste(matriz, lin, col);
	if(existe == 1)
	{
		//Decremento em um / no arquivo comeca em 1
		lin--;
		col--;

		Cell* celulaAtual = matriz->cabLinha[lin];
		while(celulaAtual->col != col)
		{
			celulaAtual = celulaAtual->proxElemLin;
		}
		celulaAtual->valor = valor;
		return matriz;
	}

	//se a celula nao existe
	matriz = insereNovaCelula(matriz, valor, lin, col);
	return matriz;

}


void printMatriz(Matriz* matriz)
{
	Cell* celulaAtual;
	int lin, col;
	float valor;
	for(int i = 0; i < matriz->dimensao; i++)
	{
		celulaAtual = matriz->cabColuna[i];
		while(celulaAtual != NULL)
		{
			lin = celulaAtual->lin;
			col = celulaAtual->col;
			valor = celulaAtual->valor;

			printf("%d;%d;%.2f,",lin+1, col+1, valor);
			celulaAtual = celulaAtual->proxElemCol;
			printf("\n");
		}
		
	}
}

Matriz* removeElemento(Matriz* matriz, int lin, int col)
{
	//Decremento em um / no arquivo comeca em 1
	lin--;
	col--;

	//Se nao tiver nem um elemento na respectiva linha e coluna
	if(matriz->cabLinha[lin] == NULL)
		return matriz;

	if(matriz->cabColuna[col] == NULL)
		return matriz;


	//else / Coluna e linha tem valores
	Cell* celulaTopoLinha = matriz->cabLinha[lin];
	Cell* celulaTopoColuna = matriz->cabColuna[col];

	Cell* celulaAtualLinha = celulaTopoLinha;
	Cell* celulaEsquerdaLinha = celulaTopoLinha;

	Cell* celulaAtualColuna = celulaTopoColuna;
	Cell* celulaCimaColuna = celulaTopoColuna;

	//Verificando se existe valor na respectiva lin e col
	while(celulaAtualLinha->col != col)
	{
		celulaEsquerdaLinha = celulaAtualLinha;
		celulaAtualLinha = celulaAtualLinha->proxElemLin;

		if(celulaAtualLinha == NULL)
			return matriz;

		if(celulaAtualLinha->col > col)
			return matriz;
	}

	while(celulaAtualColuna->lin != lin)
	{
		celulaCimaColuna = celulaAtualColuna;
		celulaAtualColuna = celulaAtualColuna->proxElemCol;
	}

	//Primeiro elemento lin == topoLinha
	if(celulaAtualLinha == celulaTopoLinha)
	{
		celulaTopoLinha = celulaAtualLinha->proxElemLin;
		matriz->cabLinha[lin] = celulaTopoLinha;
	}
	else
	{
		celulaEsquerdaLinha->proxElemLin = celulaAtualLinha->proxElemLin;
	}

	//Primeiro elemento col == topoCol
	if(celulaAtualColuna == celulaTopoColuna)
	{
		celulaTopoColuna = celulaAtualColuna->proxElemCol;
		matriz->cabColuna[col] = celulaTopoColuna;
	}
	else
	{
		celulaCimaColuna->proxElemCol = celulaAtualColuna->proxElemCol;
	}

	//Que eh a mesma da celulaAtualColuna
	freeCell(celulaAtualLinha);

	return matriz;

}

void freeMatriz(Matriz* matriz)
{
	Cell* celulaDireita;
	Cell* celulaEsquerda;
	for(int i = 0; i < matriz->dimensao; i++)
	{
		celulaEsquerda = matriz->cabLinha[i];
		while(celulaEsquerda!= NULL)
		{
			celulaDireita = celulaEsquerda->proxElemLin;
			freeCell(celulaEsquerda);
			celulaEsquerda = celulaDireita;
		}
	}
	freeCell(celulaDireita);
}

void somaMatriz(Matriz* matriz1, Matriz* matriz2)
{
	int lin, col, nxn;
	float valor;
	Cell* celulaAtualM1;
	Cell* celulaAtualM2;

	nxn = matriz1->dimensao;
	printf("%d\n", nxn);
	for(int i = 0; i < matriz1->dimensao; i++)
	{
		celulaAtualM1 = matriz1->cabLinha[i];
		celulaAtualM2 = matriz2->cabLinha[i];

		while(celulaAtualM1 != NULL || celulaAtualM2 != NULL)
		{

			//As duas linhas tem celulas
			if(celulaAtualM1 != NULL && celulaAtualM2 != NULL)
			{
				//Celulas na mesma posicao, entao soma
				if(celulaAtualM1->col == celulaAtualM2->col)
				{
					valor = celulaAtualM1->valor + celulaAtualM2->valor;
					if(valor != 0)
					{
						lin = celulaAtualM1->lin;
						col = celulaAtualM1->col;
						printf("%d;%d;%.1f, ", lin+1,col+1,valor);
					}
					celulaAtualM1 = celulaAtualM1->proxElemLin;
					celulaAtualM2 = celulaAtualM2->proxElemLin;
				}
				//Celula M1 vem primeiro que M2
				else if(celulaAtualM1->col < celulaAtualM2->col)
				{
					lin = celulaAtualM1->lin;
					col = celulaAtualM1->col;
					valor = celulaAtualM1->valor;
					printf("%d;%d;%.1f, ", lin+1,col+1,valor);
					celulaAtualM1 = celulaAtualM1->proxElemLin;
				}

				///Celula M2 vem primeiro que M1
				else
				{
					lin = celulaAtualM2->lin;
					col = celulaAtualM2->col;
					valor = celulaAtualM2->valor;
					printf("%d;%d;%.1f, ", lin+1,col+1,valor);
					celulaAtualM2 = celulaAtualM2->proxElemLin;
				}
				
			}

			//Somente a linha da M1 tem celula
			else if(celulaAtualM1 != NULL)
			{
				lin = celulaAtualM1->lin;
				col = celulaAtualM1->col;
				valor = celulaAtualM1->valor;
				printf("%d;%d;%.1f, ", lin+1,col+1,valor);
				celulaAtualM1 = celulaAtualM1->proxElemLin;
			}

			//Somente a linha da M2 tem celula
			else
			{
				lin = celulaAtualM2->lin;
				col = celulaAtualM2->col;
				valor = celulaAtualM2->valor;
				printf("%d;%d;%.1f, ", lin+1,col+1,valor);
				celulaAtualM2 = celulaAtualM2->proxElemLin;
			}
			printf("\n");
		}
	}
	
}










