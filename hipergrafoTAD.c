#include "hipergrafoTAD.h"


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


int verificaDependencias(Grafo **G, int *prim, int* prox, int vertice1, int vertice2){
        int inicio, fim;
        int depV1[3], depV2[3];
        /*depV1=malloc(3*sizeof(int));
        depV2=malloc(3*sizeof(int));*/
        int dp=0;
        inicio = prim[vertice1];
        //printf ("%d %d Vertice %d %d", prox[prim[i]], prox[prox[prim[i]]], i, inicio%27);
        fim = prox[prim[vertice1]];
        depV1[dp] = inicio%27;
        dp++;
        while(fim != -1){
            //printf(" %d ", fim%27);
            depV1[dp] = fim%27;
            fim = prox[fim];
            dp++;
        }
        dp=0;
        inicio = prim[vertice2];
        //printf ("%d %d Vertice %d %d", prox[prim[i]], prox[prox[prim[i]]], i, inicio%27);
        fim = prox[prim[vertice2]];
        depV2[dp] = inicio%27;
        dp++;
        while(fim != -1){
            //printf(" %d ", fim%27);
            depV2[dp] = fim%27;
            fim = prox[fim];
            dp++;
        }

        for(int i=0; i<3;i++){
            for(int j=0;j<3;j++){
                if(depV1[i] == depV2[j]){
                    return 1;
                }
            }
        }

        return 0;
}

int eh_solucao(Grafo *G, int *tabela, int *prim, int *prox){

    for(int i=0;i<G->numVertice;i++){
        for(int j=0;j<G->numVertice;j++){
            if((verificaDependencias(&G, prim, prox, i, j)) == 1){
                if(tabela[i] == tabela[j]){
                    printf("\n");
                    for(int i=0;i<G->numVertice;i++) printf("%d", tabela[i]);
                    return 0;
                }
            }
        }
    }
    printf("\n solution ");
    for(int i=0;i<G->numVertice;i++) printf("%d", tabela[i]);

    return 1;
}


void backtracking(Grafo *G, int *prim, int *prox){

    int i=0, flag=1, k=0;
    int *tabela = malloc(sizeof(int) * G->numVertice );
    int cont=0;
    for(i=0;i<G->numVertice;i++){
        
        tabela[i]= 0;
    }
    i=G->numVertice - 1;
    //j=G->numVertice - 2;
    while(flag == 1){
        cont++;
            if(tabela[i]< 9){
                tabela[i]++;
                if(i!=( G->numVertice-1)) i++;
            }else {
                tabela[i]= 0;
                i--;
            }
            if(eh_solucao(G, tabela, prim, prox)) {
                break;
            }
    }
    //printf("cont %d %d " , cont, k);
    getchar();
    free(tabela);
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

int main (){
    Grafo *G;
    int *prim, *prox;

    prim = malloc(81*sizeof(int));
    prox = malloc(9*27*sizeof(int));
    inicia_grafo(&G, 27);

    criar_grafo(&G);
    getPrimProx(G, 9, 27, prim, prox);

    int aux, inicio, fim;
    for(int i=0;i<81;i++){
        inicio = prim[i];
        //printf ("%d %d Vertice %d %d", prox[prim[i]], prox[prox[prim[i]]], i, inicio%27);
        fim = prox[prim[i]];
        while(fim != -1){
            //printf(" %d ", fim%27);
            fim = prox[fim];
        }
        //printf("\n");

    }

    backtracking(G, prim, prox);
    free(prim);
    free(prox);
    destroi_grafo(G);
    return 1;
}
