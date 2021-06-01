#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "List.h"

node* createList(int n)
{
	node* new = (node*)malloc(sizeof(node));
	new->next = NULL;
	new->prev = NULL;
	new->value = n;
	return new;
}

node *findList( node *head, int val ) {
  node *ptr;
  ptr = head;
  while( ptr != NULL) {
    if (ptr->value == val) {
      return ptr;
    } else {
      ptr = ptr->next;
    }
  }
  return (NULL);
}

void insertList(node **head, node *new) {
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

void deleteList(node **head, node *del) {
  if (*head == del) {
    *head = del->next;
  } else {
    del->prev->next = del->next;
    if (del->next != NULL) {
      del->next->prev = del->prev;
    }
    free(del);
  }
}

void printList(node *head) {
  if (head == NULL) {
    return;
  }
  node* cue = head;
  printf("\n\t>>PRINTING LIST>>");
  while (cue != NULL) {
    printf("%d\t", cue->value);
    cue = cue->next;
  }
  printf("\n");
}

int getValue (node* x) {
  return x->value;
}
