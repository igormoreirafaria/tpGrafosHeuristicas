#include "heuristica.h"

int coloracaoSequencial(Grafo *G, int* tabela, int** matriz, int* prim, int* prox) {
    int conjuntos =9;
    for(int i=0; i<G->numVertice; i++){
        printf("%d \n", i);
        if(tabela[i] != -1){ // verifia se o vertice ja se encontra na matriz
            for(int j=0; j<conjuntos; j++){ // precorre os conjuntos
                if(verificaConflitos(G, i, matriz[j], prim, prox)){   //verifica a disponibilidade do conjunto de receber vértices
                    for(int k=1; k<10 ; k++){ // percorre a matriz verificando um espaço disponivel para acomodar o vertice dentro do conjunto
                        if(matriz[j][k] == -1){
                            matriz[j][k] = i;
                            //printf("Adicionando o vertice %d ao conjunto %d.\n", i, j);
                            tabela[i] = -1;
                            j=conjuntos;
                            break;
                        }
                    }
                }
            }
            if(tabela[i]!=-1){
                conjuntos++;
                matriz[conjuntos-1] = (int*)malloc(sizeof(int)* 10);
                for(int i=1; i<10; i++){
                    matriz[conjuntos-1][i] = -1;
                }
                matriz[conjuntos-1][0] = conjuntos;
                 matriz[conjuntos-1][1] = i;
                 printf(" %d %d\n", matriz[conjuntos-1][0], matriz[conjuntos-1][1]);
                 tabela[i] = -1;

            }
    }
    printf("\n\n");
    //printf("\n\n saindo com classe\n");
    for(int p=0;p<conjuntos;p++) {
                      for(int l=0;l<10;l++) {
                        printf("%d ", matriz[p][l]);
                      }
                      printf("\n");
                  }
        }
        return conjuntos;
}
/* Verifica Conflitos  */
int verificaConflitos(Grafo *G, int vertice, int* matriz, int *prim, int *prox) {

        for(int i=1;i<9;i++){
            //printf("Verificando %d %d\n", matriz[i], vertice);
            if(matriz[i] == -1){
                break;
            }
            if((verificaDependencias(&G, prim, prox, vertice, matriz[i])) == 1){
                    return 0;
                }
        }

        return 1;
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