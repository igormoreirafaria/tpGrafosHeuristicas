#include "main.h"

int main (){
    Grafo *G;
    int *prim, *prox, *tabela, **matriz;

    matriz = (int**)malloc(10*sizeof(int*));
    for(int i=0;i<9;i++){
        matriz[i] = (int*)malloc(9*sizeof(int));

    }
    for(int i=0;i<9;i++){
          for(int j=0;j<10;j++){
            matriz[i][j] = -1;
            if(j==0){
                matriz[i][j] = i+1;
            }
        }
    }

    tabela = (int*) malloc(sizeof(int) * 81);
    leitura(G, tabela, matriz);

    for(int i=0;i<9;i++) {
          for(int j=0;j<10;j++) {
            printf("%d ", matriz[i][j]);
          }
          printf("\n");
      }

    prim = malloc(81*sizeof(int));
    prox = malloc(9*27*sizeof(int));

    inicia_grafo(&G, 27);

    criar_grafo(&G);

    getPrimProx(G, 9, 27, prim, prox);

    int aux, inicio, fim;
    for(int i=0;i<81;i++){
        inicio = prim[i];
        fim = prox[prim[i]];
        while(fim != -1){
            fim = prox[fim];
        }

    }
    int conjuntos;
    printf("ENTRA NA COLORACAO\n");
    conjuntos = coloracaoSequencial(G, tabela, matriz, prim, prox);
    printf("SAI DA COLORACAO\n");
    

    for(int i=1;i<conjuntos;i++) {
          for(int j=0;j<10;j++) {
            printf("%d ", matriz[i][j]);
          }
          printf("\n");
      }
    //backtracking(G, prim, prox);

    free(prim);
    free(prox);
    destroi_grafo(G);

    return 0;
}

void destroi_grafo(Grafo *G){

    for(int i=0;i<27;i++){
        free((G)->lista[i].prox->vertices);
        free((G)->lista[i].prox);
    }
    free((G)->lista);
    free(G);
}



void inicia_grafo(Grafo **G, int num_arestas){

    (*G) = malloc(sizeof(Grafo));

    (*G)->lista = malloc(sizeof(Node)*num_arestas);
    (*G)->numVertice = 81;

    for(int i=0;i<27;i++){
        (*G)->lista[i].prox = malloc(sizeof(Node));
        (*G)->lista[i].prox->vertices = malloc(sizeof(int)*9);
        for (int j=0;j<9;j++){
            (*G)->lista[i].prox->vertices[j] = -1;
        }
    }
}
void criar_grafo(Grafo **G){
    int k=0;

    // dependencias das colunas
    for(int i=0; i<9;i++){
        for(int j=0;j<9;j++){
            criar_dependencias(G, k, i+(9*j));
        }
        k++;
    }

    // dependencias das linhas
    for(int i=0; i<9;i++){
        for(int j=0;j<9;j++){
            criar_dependencias(G, k, j+(i*9));
        }
        k++;
    }

    // dependencias dos blocos
    for(int i=0;i<3;i++){
       for (int p = 0; p < 3; p++){
           for(int j=0;j<3;j++){
                for(int l=0;l<3;l++){
                    criar_dependencias(G, k, (l + (j*9) +(p*3) +((i*3)*9)));
                }
            }
            k++;
        }
    }
}

void criar_dependencias(Grafo **G, int i, int vertice){ // i == aresta
    Node *list = (*G)->lista[i].prox;
    // colunas
    for(int k=0;k<9;k++){
        if(list->vertices[k] == -1){
            list->vertices[k] = vertice;
            return;
        }
    }
}

void leitura(Grafo *G, int *tabela, int **matriz){
    int i=0, j=0;
    char *leitura;
    char *aux = malloc(sizeof(char));
    FILE *arq = fopen("sudoku.txt", "r");
    leitura = malloc(sizeof(char)*81);

        fscanf(arq, "%s", leitura);

        for(int i=0; i<81 ; i++){
            *aux = leitura[i];
            tabela[i] = atoi(aux);
            printf("%d", tabela[i]);
            if(tabela[i] != 0){ //
                for(int j=1;j<10 ;j++){
                    if(matriz[tabela[i]-1][j] == -1){
                        matriz[tabela[i]-1][j] = i;
                        tabela[i] = -1;
                        break;
                    }
                }
            }
        }
        getchar();
       /* j++;
        if(j == 9){
            j=0;
            i++;
        }

        if(i==9){
            break;
        }*/

    fclose(arq);
}

int verifica_conflitos(Grafo *G){
    return 0;
}

int getPrimProx(Grafo *grafo, int r, int A, int *prim, int *prox){

    for(int i =0;i<81;i++){
         prim[i]=-1;
    }

    for(int i =0;i<9*27;i++){
        prox[i]=-1;
    }
    int i=0;
    for(int a=0; a<27;a++){
        for(int j = 0; j < 9; j++){
                i = a + ( j * A );
                prox[i] = prim[grafo->lista[a].prox->vertices[j]];
                prim[grafo->lista[a].prox->vertices[j]] = i;
        }
    }
    return 0;
}
