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
  D->hash_table = calloc(n, sizeof(node_t));
  for (int i = 0; i < n; i++) {
    D->hash_table[i].value = NULL;
    D->hash_table[i].next = NULL;
    D->hash_table[i].prev = NULL;
    memcpy(D->hash_table[i].key, "", 5);
  }
}

// inserts element e->key:e->value into the dictoinary
// First, make sure that e->key does not exiest in *D yet
// If it does, return an error code of -1
// Otherwise, update the size of *D, and return 0.

int insert(dictionary* D, element* e) {
  if (find(D, e->key) == NULL) {
    node_t* new_node = malloc(sizeof(node_t));
    new_node->prev = NULL;
    new_node->next = NULL;
    memcpy(new_node->key, e->key, 5); 
    new_node->value = e->value;

    int index = hash(e->key, D->slots);
    node_t* head = malloc(sizeof(node_t));
    head = D->hash_table[index].next;
    while(head->next != NULL) {
      head = head->next;
    }
    head->next = new_node;
    new_node->prev = head;
    D->size++;
    return 0;
  } else {
    return -1;
  }
}

node_t* find(dictionary* D, char* k) {
  int index = hash(k, D->slots);
  node_t* temp = malloc(sizeof(node_t));
  temp = D->hash_table[index].next;
  while(temp != NULL) {
    if(strcmp(temp->key, k) == 0) {
      return temp;
    } else {
      temp = temp->next;
    }
  }
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
