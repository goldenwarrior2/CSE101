#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

graph createGraph(int num) {
  graph g = (graph) malloc(sizeof(graphObj));
  g->n = num;
  g->matrix = (int**) calloc(num, sizeof(int*));
  for (int i = 0; i < num; i++) {
    g->matrix[i] = calloc(num, sizeof(int));
  }
  return g;
}

void destructGraph(graph g) {
  if (g) {
    for (int i = 0; i < g->n; i++) {
      free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
    g = NULL;
  }
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

void outEdges(graph g, int i, node** list) {
  for (int j = 0; j < g->n; j++) {
    if (g->matrix[i][j] == 1) {
      node* n = (node*) malloc(sizeof(node));
      n->value = j;
      n->next = NULL;
      n->prev = NULL;
      insertList(list, n);
    }
  }
}

void inEdges(graph g, int j, node**list) {
  for (int i = 0; i < g->n; i++) {
    if (g->matrix[i][j] == 1) {
      node* n = (node*) malloc(sizeof(node));
      n->value = i;
      n->next = NULL;
      n->prev = NULL;
      insertList(list, n);
    }
  }
}

void printGraph(graph g) {
  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < g->n; j++) {
      printf("%d ", g->matrix[i][j]);
    }
    printf("\n");
  }
}

int getNumVer(graph g) {
  return g->n;
}
