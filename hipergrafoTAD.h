#include "main.h"



void backTracking(Grafo *G, int *prim, int *prox);
int eh_solucao(Grafo *G, int *tabela, int *prim, int *prox);
int verificaDependencias(Grafo **G, int *prim, int* prox, int vertice1, int vertice2);
