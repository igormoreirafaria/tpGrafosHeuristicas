#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *prox;
    int *vertices;
}Node;

typedef struct grafo {
    int  numVertice;
    Node *lista;
}Grafo;

void inicia_grafo(Grafo **G, int num_vertice);
void criar_dependencias(Grafo **G, int i, int vertice);
void criar_grafo(Grafo **G);
int getPrimProx(Grafo *grafo, int r, int A, int *prim, int *prox);
void backtracking(Grafo *G, int *prim, int *prox);
int eh_solucao(Grafo *G, int *tabela, int *prim, int *prox);
int verificaDependencias(Grafo **G, int *prim, int* prox, int vertice1, int vertice2);
void destroi_grafo(Grafo *G);