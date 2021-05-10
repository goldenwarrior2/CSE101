#include <string.h>
#include <stdio.h>
#include "List.h"

node_t *findList(node_t *head, char *key) {
  node_t *ptr;
  ptr = head;
  while(ptr != NULL) {
    if (strcmp(ptr->key, key) == 0) {
      break;
    } else {
      ptr = ptr->next;
    }
  }
  return (ptr);
}

void insertList(node_t **head, node_t *new) {
  if (*head == NULL) {
    *head = new;
    (*head)->next = NULL;
    (*head)->prev = NULL;
  } else {
    new->next = *head;
    (*head)->prev = new;
    new->prev = NULL;
    *head = new;
  }
}

void deleteList(node_t **head, node_t *del) {
  del->prev->next = del->next;
  if (del->next != NULL) {
    del->next->prev = del->prev;
  }
}

void printList(node_t *head) {
  while(head != NULL) {
    printf("%s, ", head->key);
    head = head->next;
  }
}
