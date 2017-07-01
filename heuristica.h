#include "main.h"

/*--------------------METODOS------------------------------*/

int verificaConflitos(Grafo*, int, int*,int*, int*);
int verificaDependencias(Grafo**, int*, int*, int, int);
int coloracaoSequencial(Grafo *G, int* tabela, int** matriz, int* prim, int* prox);