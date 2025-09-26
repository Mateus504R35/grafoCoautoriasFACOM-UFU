#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"

//----------------------------------------------
//Letra A):
int buscaVertice(grafo *g, char *Professor){
  for(int i = 0; i < g->nVertices; i++){
    if(strcmp(g->Professores[i].Professor, Professor) == 0)
      return i;
  }
  return -1;
}

int existeVertice(grafo *g, char *Professor){
  for(int i = 0; i < g->nVertices; i++){
    if(strcmp(g->Professores[i].Professor, Professor) == 0) return 0;
  }
  return -1;
}

void criaVertice(grafo *g, char *Professor) {
  if(existeVertice(g, Professor) != 0){
    int p;
    p = g->nVertices;
    strcpy(g->Professores[p].Professor, Professor);
    g->Professores[p].nADJ = 0;
    g->nVertices++;
  }
}

int existeAresta(grafo *g, char *Professor1, char *Professor2){
    int i, j;
    for (int l = 0; l < g->nVertices; l++) {
        if (strcmp(g->Professores[l].Professor, Professor1) == 0) {
            i = l;
        }
        if (strcmp(g->Professores[l].Professor, Professor2) == 0) {
            j = l;
        }
    }
  if(i == -1 || j == -1) return -1;
  int vp1, vp2;
  vp1 = vp2 = -1;

  for(int k = 0; k < g->Professores[i].nADJ; k++){
    if(g->Professores[i].ListaADJ[k].ProfessorCoautor == j){
      vp1 = 0;
      break;
    }
  }
    for(int k = 0; k < g->Professores[j].nADJ; k++){
    if(g->Professores[j].ListaADJ[k].ProfessorCoautor == i){
      vp2 = 0;
      break;
    }
  }

  if(vp1 == 0 && vp1 == vp2) return 0;
  else return -1;
  
}

void criaAresta(grafo *g, char *Professor1, char *Professor2, int colabs) {
    int i, pProfessor1, pProfessor2;
    
    if(existeVertice(g, Professor1) == -1) criaVertice(g, Professor1);
    if(existeVertice(g, Professor2) == -1) criaVertice(g, Professor2);

    for (i = 0; i < g->nVertices; i++) {
        if (strcmp(g->Professores[i].Professor, Professor1) == 0) {
            pProfessor1 = i;
        }
        if (strcmp(g->Professores[i].Professor, Professor2) == 0) {
            pProfessor2 = i;
        }
    }

  if(existeAresta(g, Professor1, Professor2) != 0){
    g->Professores[pProfessor1].ListaADJ = (aresta*) realloc(g->Professores[pProfessor1].ListaADJ, (g->Professores[pProfessor1].nADJ + 1)*sizeof(aresta));
    g->Professores[pProfessor1].ListaADJ[g->Professores[pProfessor1].nADJ].ProfessorCoautor = pProfessor2;
    g->Professores[pProfessor1].ListaADJ[g->Professores[pProfessor1].nADJ].Coautorias = colabs;
    g->Professores[pProfessor1].nADJ++;   
  
    g->Professores[pProfessor2].ListaADJ = (aresta*) realloc(g->Professores[pProfessor2].ListaADJ, (g->Professores[pProfessor2].nADJ + 1)*sizeof(aresta));
    g->Professores[pProfessor2].ListaADJ[g->Professores[pProfessor2].nADJ].ProfessorCoautor = pProfessor1;
    g->Professores[pProfessor2].ListaADJ[g->Professores[pProfessor2].nADJ].Coautorias = colabs;
    g->Professores[pProfessor2].nADJ++;
  }
}

grafo *criagrafo() {
    grafo *G = (grafo *) malloc(sizeof(grafo));
    G->nVertices = 0;
    return G;
}

void imprimegrafo(grafo *g) {
  int i, j;
  for (i = 0; i < g->nVertices; i++) {
    if(i != 1){
      printf("Professor: %s \n",g->Professores[i].Professor);
      for (j = 0; j < g->Professores[i].nADJ; j++) {
        printf("->%s (Artigos: %d)\n", g->Professores[g->Professores[i].ListaADJ[j].ProfessorCoautor].Professor, g->Professores[i].ListaADJ[j].Coautorias);
      }
    printf("\n");
    }
  }
}

void imprimeOrigem(grafo *g, int Professor){
  for(int i = 0; i < g->nVertices; i++){
    for(int j = 0; j < g->Professores[i].nADJ; j++){
      if(g->Professores[i].ListaADJ[j].ProfessorCoautor == Professor){
        printf("%s ->", g->Professores[i].Professor);
        break;
      }
    }
  }
  printf("\n");
}

//---------------------------------------------------------------------------------
//Letra C):
void exibirCoautores(grafo *g, char professor[], int K) {
    int i, j;
    int professorIndice = -1;

    for (i = 0; i < g->nVertices; i++) {
        if (strcmp(g->Professores[i].Professor, professor) == 0) {
            professorIndice = i;
            break;
        }
    }

    if (professorIndice == -1) {
        printf("Professor %s nao encontrado no grafo.\n", professor);
        return;
    }

    printf("Professores que colaboraram diretamente com %s(com pelo menos %d coautorias):\n", professor, K);
    for (i = 0; i < g->nVertices; i++) {
        if (i != professorIndice) {
            for (j = 0; j < g->Professores[i].nADJ; j++) {
                if ((g->Professores[i].ListaADJ[j].ProfessorCoautor == professorIndice) &&
                    (g->Professores[i].ListaADJ[j].Coautorias >= K)) {
                    printf("-> %s (%d coautorias totais)\n", g->Professores[i].Professor, g->Professores[i].ListaADJ[j].Coautorias);
                    break;
                }
            }
        }
    }
    printf("\n");
}
//---------------------------------------------------
//letra D)
void buscaDFS(grafo *g, int u, int *visitados, int *componente){
    visitados[u] = 1;
    componente[u] = 1;
    for(int i = 0; i < g->Professores[u].nADJ; i++){
        int v = g->Professores[u].ListaADJ[i].Coautorias;
        if(!visitados[v]){
            buscaDFS(g, v, visitados, componente);
        }
    }
}

void buscaDFStransposto(grafo *g, int u, int *visitados, int *componente){
    visitados[u] = 1;
    for(int i = 0; i < g->nVertices; i++){
        if(componente[i] && !visitados[i]){
            buscaDFStransposto(g, i, visitados, componente);
        }
    }
}

void fortementeConectados(grafo *g, char *Professor){
    int visitados[MAXVERTICES] = {0};
    int componente[MAXVERTICES] = {0};
    int u = -1;
    for(int i=0; i<g->nVertices; i++){
        if(strcmp(g->Professores[i].Professor, Professor) == 0){
            u = i;
            break;
        }
    }
    if(u == -1){
        printf("Professor nao encontrado no grafo.\n");
        return;
    }
    buscaDFS(g, u, visitados, componente);
    for(int i=0; i<g->nVertices; i++){
        visitados[i] = 0;
    }
    grafo gTransposto;
    gTransposto.nVertices = g->nVertices;
    for(int i=0; i<g->nVertices; i++){
        gTransposto.Professores[i] = g->Professores[i];
        gTransposto.Professores[i].nADJ = 0;
    }
    for(int i=0; i<g->nVertices; i++){
        for(int j=0; j<g->Professores[i].nADJ; j++){
            int v = g->Professores[i].ListaADJ[j].ProfessorCoautor;
            aresta a = g->Professores[i].ListaADJ[j];
            aresta aTransposta;
            aTransposta.ProfessorCoautor = i;
            aTransposta.Coautorias = a.Coautorias;
            gTransposto.Professores[v].ListaADJ[gTransposto.Professores[v].nADJ++] = aTransposta;
        }
    }
    for(int i=0; i<g->nVertices; i++){
        if(componente[i]){
            buscaDFStransposto(&gTransposto, i, visitados, componente);
        }
    }
    
    printf("Componente fortemente conectado:\n");
    printf("-> ");
    for(int j=0; j<g->nVertices; j++){
      if(j!=1){
        if(componente[j]){
          for(int l = 0; l < g->Professores[j].nADJ; l++){
            if(g->Professores[j].ListaADJ[l].ProfessorCoautor != 1){
              printf("*%s\n", g->Professores[j].Professor);
              break;
          }
        }
      }
    }
  }
  printf("\n");
}

//-------------------------------------------------------------------------------------------------------------------
//Letra B):
void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
}

void enfileirar(Fila *fila, int valor) {
    fila->elementos[fila->fim++] = valor;
}

int desenfileirar(Fila *fila) {
    return fila->elementos[fila->inicio++];
}

int filaVazia(Fila *fila) {
    return fila->inicio == fila->fim;
}

void BFS(grafo *g, int inicio, int distanciaLimite) {
    Fila fila;
    int visitados[MAXVERTICES] = {0};
    int distancia[MAXVERTICES] = {0};

    inicializarFila(&fila);
    enfileirar(&fila, inicio);
    visitados[inicio] = 1;

    while (!filaVazia(&fila)) {
        int atual = desenfileirar(&fila);
        int i;

        if (distancia[atual] > distanciaLimite) {
            break; 
        }

            if(atual != inicio){
              
              if (atual >= 0 && atual < g->nVertices) {
                printf(" -> %s(%d de distancia)\n", g->Professores[atual].Professor, distancia[atual]);

              }
              else{
               for(int i = 0; i < g->nVertices; i++){
                for(int j = 0; j < g->Professores[i].nADJ; j++){
                  if(g->Professores[i].ListaADJ[j].ProfessorCoautor == atual){
                    printf("%s -> ", g->Professores[i].Professor);
                    break;
                  }
                }
              }
                printf(" -> ");
                printf("%s(%d de distancia)\n", g->Professores[atual].Professor, distancia[atual]);
              }
            }

        for (i = 0; i < g->Professores[atual].nADJ; i++) {
            int vizinho = g->Professores[atual].ListaADJ[i].ProfessorCoautor;
            if (!visitados[vizinho]) {
                enfileirar(&fila, vizinho);
                visitados[vizinho] = 1;
                distancia[vizinho] = distancia[atual] + 1;
            }
        }
    }
    printf("\n");
}

void mostraCoautores(grafo *g, char *professor, int K) {
    int inicio = buscaVertice(g, professor);

    if (inicio != -1) {
        printf("Coautores de %s com até %d passos de distância:\n", professor, K);
        BFS(g, inicio, K);
    } else {
        printf("Professor %s não encontrado no grafo.\n", professor);
    }
}


//----------------------------------------------------
//Letra E):

HeapNo criarNo(int vertice, int custo) {
    HeapNo No;
    No.vertice = vertice;
    No.custo = custo;
    return No;
}

MinHeap criarMinHeap(int capacidade) {
    MinHeap minHeap;
    minHeap.tamanho = 0;
    minHeap.capacidade = capacidade;
    minHeap.arr = (HeapNo *)malloc(capacidade * sizeof(HeapNo));
    return minHeap;
}

void trocarNos(HeapNo *a, HeapNo *b) {
    HeapNo temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int indice) {
    int menor = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;

    if (esquerda < minHeap->tamanho && minHeap->arr[esquerda].custo < minHeap->arr[menor].custo)
        menor = esquerda;

    if (direita < minHeap->tamanho && minHeap->arr[direita].custo < minHeap->arr[menor].custo)
        menor = direita;

    if (menor != indice) {
        trocarNos(&minHeap->arr[indice], &minHeap->arr[menor]);
        minHeapify(minHeap, menor);
    }
}

int isEmpty(MinHeap *minHeap) {
    return minHeap->tamanho == 0;
}

HeapNo extrairMinimo(MinHeap *minHeap) {
    if (isEmpty(minHeap))
        return criarNo(-1, -1);

    HeapNo min = minHeap->arr[0];
    HeapNo ultimo = minHeap->arr[minHeap->tamanho - 1];
    minHeap->tamanho--;
    minHeap->arr[0] = ultimo;
    minHeapify(minHeap, 0);
    return min;
}


void diminuirChave(MinHeap *minHeap, int vertice, int custo) {
    int i;
    for (i = 0; i < minHeap->tamanho; i++) {
        if (minHeap->arr[i].vertice == vertice) {
            minHeap->arr[i].custo = custo;
            break;
        }
    }

    while (i && minHeap->arr[i].custo < minHeap->arr[(i - 1) / 2].custo) {
        trocarNos(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void encontrarCaminhoMinimo(grafo *g, char P1[], char P2[]) {
    int distancias[MAXVERTICES];
    int pais[MAXVERTICES];
    int P1Indice = -1, P2Indice = -1;

    for (int i = 0; i < g->nVertices; i++) {
        distancias[i] = INF;
        pais[i] = -1;
        if (strcmp(g->Professores[i].Professor, P1) == 0) {
            P1Indice = i;
        }
        if (strcmp(g->Professores[i].Professor, P2) == 0) {
            P2Indice = i;
        }
    }

    if (P1Indice == -1 || P2Indice == -1) {
        printf("Professores nao encontrados no grafo.\n");
        return;
    }

    distancias[P1Indice] = 0;

    MinHeap minHeap = criarMinHeap(g->nVertices);
    for (int i = 0; i < g->nVertices; i++) {
        minHeap.arr[i] = criarNo(i, distancias[i]);
        minHeap.tamanho++;
    }

    diminuirChave(&minHeap, P1Indice, distancias[P1Indice]);

    while (!isEmpty(&minHeap)) {
        HeapNo minNo = extrairMinimo(&minHeap);
        int u = minNo.vertice;

        if (u == P2Indice) {
            break;
        }

        for (int i = 0; i < g->Professores[u].nADJ; i++) {
            int v = g->Professores[u].ListaADJ[i].ProfessorCoautor;
            int custo = g->Professores[u].ListaADJ[i].Coautorias;

            if (distancias[u] != INF && distancias[u] + custo < distancias[v]) {
                distancias[v] = distancias[u] + custo;
                pais[v] = u;
                diminuirChave(&minHeap, v, distancias[v]);
            }
        }
    }

    if (distancias[P2Indice] == INF) {
        printf("Nao ha caminho entre %s e %s\n\n", P1, P2);
        return;
    }

    printf("Caminho minimo entre %s e %s: %d de distancia total\n", P1, P2, distancias[P2Indice]);
    printf("->Percurso: ");
    int caminho[MAXVERTICES];
    int tamanhoCaminho = 0;
    int atual = P2Indice;
    while (atual != -1) {
        caminho[tamanhoCaminho++] = atual;
        atual = pais[atual];
    }
    for (int i = tamanhoCaminho - 1; i >= 0; i--) {
        printf("%s", g->Professores[caminho[i]].Professor);
        if (i > 0) {
            printf(" ~ ");
        }
    }
    printf("\n\n");
}
