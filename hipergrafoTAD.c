#include "hipergrafoTAD.h"

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


void forcaBruta(Grafo *G, int *prim, int *prox){
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
    free(tabela);
}
