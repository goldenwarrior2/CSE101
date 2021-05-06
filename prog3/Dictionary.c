// -------------------------
// Dictionary ADT:
// -------------------------

#include <stdlib.h>		//for build-in malloc that returns void *
#include "Dictionary.h"
#include <string.h>
#include <stdio.h>

// creates a dictionary with n slots
// Initializes slots to n, and size to 0.
void create(dictionary *D, int n) {
  D->slots = n;
  D->size = 0;
  D->hash_table = (node_t*) calloc(n, sizeof(node_t));
  for (int i = 0; i < n; i++) {
    D->hash_table[i].value = NULL;
    D->hash_table[i].next = NULL;
    D->hash_table[i].prev = NULL;
    memcpy(D->hash_table[i].key, "", 5);
  }
}

// inserts element e->key:e->value into the dictoinary
// First, make sure that e->key does not exist in *D yet
// If it does, return an error code of -1
// Otherwise, update the size of *D, and return 0.

int insert(dictionary* D, element* e) {
  node_t* new_node = (node_t*) malloc(sizeof(node_t));
  new_node->prev = NULL;
  new_node->next = NULL;
  memcpy(new_node->key, e->key, 5); 
  new_node->value = e->value;

  int index = hash(e->key, D->slots);
  printf("%d\n", index);
  node_t* head = &(D->hash_table[index]);
  while(head->next != NULL) {
    printf("%s\n", head->key);
    head = head->next;
  }
  head->next = new_node;
  new_node->prev = head;
  D->size++;
  return 0;
}

node_t* find(dictionary* D, char* k) {
  int index = hash(k, D->slots);
  node_t* head = &(D->hash_table[index]); // set head equal to the address of the sentinel node at the hash table index
  while(head->next != NULL) {		// start at head->next so that we skip the sentinel node
    if(strncmp(head->next->key, k, 5) == 0) {
      return head->next;
    }
    head = head->next; 
  }
  printf("No %s in the index %d\n", k, index);
  return NULL;
}

void print(dictionary* D) {
  node_t* ptr = malloc(sizeof(node_t));
  for (int i = 0; i < D->slots; i++) {
    if (strcmp(D->hash_table[i].next->key, "     ") != 0) {
      ptr = D->hash_table[i].next;
      while (ptr != NULL) {
   	printf("%s ", ptr->key);
	ptr = ptr->next;
      }
    }
  }
}
