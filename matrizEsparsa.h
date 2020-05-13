/*Author: Kelvin Lehrback Guilherme
Disciplina: Estrutuda de Dados
Professor: Flavio Lamas
Curso: BSI - IFES Campus Serra*/

#ifndef MATRIZ_ESPARSA
#define MATRIZ_ESPARSA

typedef struct Celula Cell;
typedef struct MatrizEsparsa Matriz;

void freeMatriz(Matriz* matriz);
void printMatriz(Matriz* matriz);
void somaMatriz(Matriz* matriz1, Matriz* matriz2);

Matriz* criaMatriz(int nxn);
Matriz* removeElemento(Matriz* matriz, int lin, int col);
Matriz* insereElemento(Matriz* matriz, float valor, int lin, int col);

#endif