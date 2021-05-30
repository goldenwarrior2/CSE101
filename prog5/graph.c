#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

graph createGraph(int num) {
  graph g = (graph) malloc(sizeof(graphObj));
  g->n = num;
  g->matrix = (int**) calloc(num, sizeof(int*));
  for (int i = 0; i < num; i++) {
    g->matrix[i] = calloc((num / 2), sizeof(int));
  }
  return g;
}

void addEdge(graph g, int i, int j) {
  g->matrix[i][j] = 1;
}

void removeEdge(graph g, int i, int j) {
  g->matrix[i][j] = 0;
}

int hasEdge(graph g, int i, int j) {
  return (g->matrix[i][j] == 1);
}

void printGraph(graph g) {
  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < (g->n) / 2; j++) {
      printf("%d ", g->matrix[i][j]);
    }
    printf("\n");
  }
}
