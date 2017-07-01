#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _Estruturas_
#define _Estruturas_
typedef struct node {
    int cor;
    struct node *prox;
    int *vertices;
}Node;

typedef struct grafo {
    int  numVertice;
    Node *lista;
}Grafo;
#endif

void inicia_grafo(Grafo **G, int num_vertice);
void criar_dependencias(Grafo **G, int i, int vertice);
void criar_grafo(Grafo **G);
int getPrimProx(Grafo *grafo, int r, int A, int *prim, int *prox);
void destroi_grafo(Grafo *G);
void leitura(Grafo *, int *, int **);