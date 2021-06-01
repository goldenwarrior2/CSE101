#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

int main(void) {
  node* list = createList(0);
  graph g = createGraph(10);
  addEdge(g, 1, 2);
  addEdge(g, 2, 2);
  addEdge(g, 3, 2);
  addEdge(g, 4, 2);
  inEdges(g, 2, &list);
  printList(list);
  printGraph(g);
  destructGraph(g);
  return 0;
}
