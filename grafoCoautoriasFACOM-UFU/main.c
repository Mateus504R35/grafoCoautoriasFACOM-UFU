//MATEUS EURIPEDES MALAQUIAS SOARES
//MARCELLA SILVA FIGUEREDO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"

#define MAX 100

int main() {
    char opcao;
    FILE *arqProfesores;
    char conteudo_linha[MAX];
    char mn[3][50], *pt, nome[MAX];
    int p, colabs;
    int linha = 1;
    grafo *g = criagrafo();

    arqProfesores = fopen("dados.txt", "r");
    if(arqProfesores == NULL){
      printf("Erro ao abrir o arquivo de professores.");
      return 0;
    }

    while (fgets(conteudo_linha, MAX, arqProfesores) != NULL) {
      pt = strtok(conteudo_linha, "   ");
      p = 0;
      
      while (pt) {
        strcpy(mn[p], pt);
        pt = strtok(NULL, "   ");
        p++;
      }
      colabs = atoi(mn[2]);
      criaAresta(g, mn[0], mn[1], colabs);
      linha++;
  }
  fflush(stdin);
  
  do { 
    printf("-------------------------------------------------------------\n");
    printf("<<<Colaboracao cientifica entre professores da FACOM(UFU)>>>\n");
    printf("\n***Escolha uma opcao para ser executada: \n\n");
    printf("(1) - Imprimir grafo 'Professores e Coautores'\n");
    printf("(2) - Exibir coautorias de um professor com até D passos de distancia\n");
    printf("(3) - Exibir professores colaboradores por quantidade minima de artigos\n");
    printf("(4) - Exibir professores fortemente conectados a outro\n");
    printf("(5) - Exibir caminho de custo minimo entre dois professores\n");
    printf("(6) - Sair\n");
    printf("-: ");
    scanf(" %c", &opcao);
    fflush(stdin);
    
    switch (opcao) { 
      case '1': 
        printf("------Você escolheu a Opção 1------\n\n"); 
        imprimegrafo(g);
        break; 

      case '2':
        printf("------Você escolheu a Opção 2------\n\n"); 
        char nomeProfessor[MAX]; 
        int distancia;
        printf("Digite o nome do professor: "); 
        scanf(" %[^\n]", nomeProfessor); 
        printf("Digite a distância máxima de passos a ser percorrida: "); 
        scanf("%d", &distancia);
        fflush(stdin);
        mostraCoautores(g, nomeProfessor, distancia);  
        break; 

      case '3': 
        printf("------Você escolheu a Opção 3------\n\n"); 
        char nomeProfessorC[MAX]; 
        int coautorias; 
        printf("Digite o nome do professor: "); 
        scanf(" %[^\n]", nomeProfessorC);  
        fflush(stdin);
        printf("Digite um número de coautorias: "); 
        scanf("%d", &coautorias); 
        fflush(stdin);
        exibirCoautores(g, nomeProfessorC, coautorias);  
        break; 
        
      case '4': 
        printf("------Você escolheu a Opção 4------\n\n"); 
        char nomeProfessorD[MAX]; 
        printf("Digite o nome do professor: "); 
        scanf(" %[^\n]", nomeProfessorD);
        fflush(stdin);
        fortementeConectados(g, nomeProfessorD); 
        break; 
        
      case '5': 
        printf("------Você escolheu a Opção 5------\n\n"); 
        char nomeProfessor1E[MAX]; 
        char nomeProfessor2E[MAX]; 
        printf("Digite o nome do primeiro professor: "); 
        scanf(" %[^\n]", nomeProfessor1E); 
        fflush(stdin);
        printf("Digite o nome do segundo professor: "); 
        scanf(" %[^\n]", nomeProfessor2E);
        fflush(stdin);
        encontrarCaminhoMinimo(g, nomeProfessor1E, nomeProfessor2E);  
        break; 

      case '6': 
        printf("------Saindo... Muito Obrigado!------\n"); 
        printf("\n-------------------------------------------------------------\n");
         break; 
      
      default: 
        printf("Opção inválida. Tente novamente.\n"); 
    } 
  } while (opcao != '6'); 
  return 0;
}



