#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

int main() {
  node_t *new_node = malloc(sizeof(node_t));
  node_t *second_node = malloc(sizeof(node_t));
  scanf("%s", new_node->key);
  new_node->next = second_node;
  new_node->prev = NULL;
  scanf("%s", second_node->key);
  printList(new_node);
  deleteList(&new_node, second_node);
  printList(new_node);
  return 0;
}
