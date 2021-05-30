#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

int main(void) {
  graph g = createGraph(4);
  addEdge(g, 1, 1);
  printf("%d\n", hasEdge(g, 1, 1));
  printGraph(g);
  printf("\n");
  removeEdge(g, 1, 1);
  printf("%d\n", hasEdge(g, 1, 1));
  printGraph(g);
  
  return 0;
}
