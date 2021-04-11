#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct ListObj {
  Node *head;
  int length;
} ListObj;

List newList(void) {
  List new_list = (List)malloc(sizeof(ListObj));
  if (new_list) {
    new_list->head = NULL;
    new_list->length = 0;
  }
  return new_list;
}

Node *newNode(int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node) {
    new_node->data = data;
    new_node->next = NULL;
  }
  return new_node;
}

void freeNode(Node *n) {
  if (n != NULL) {
    free(n);
    n = NULL;
  }
}

void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    Node *curr_node = (*pL)->head;
    while (curr_node != NULL) {
      Node *store = curr_node->next;
      freeNode(curr_node);
      curr_node = store;
    }
    free(*pL);
    *pL = NULL;
  }
}

int length(List L) { return L->length; }

int max(List L) {
  if (L->length == 0 || L == NULL) {
    fprintf(stderr, "L is empty or does not exist.");
    return -1;
  } else {
    int biggest = 0;
    Node *curr_node = L->head;
    while (curr_node != NULL) {
      if (curr_node->data > biggest) {
        biggest = curr_node->data;
      }
      curr_node = curr_node->next;
    }
    return find(L, biggest);
  }
}

int find(List L, int i) {
  Node *curr_node = L->head;
  int index = 0;
  while (curr_node != NULL) {
    if (curr_node->data == i) {
      return index;
    }
    curr_node = curr_node->next;
    index++;
  }
  return -1;
}

void appendList(List L, int i) {
  if (L == NULL) {
    fprintf(stderr, "List does not exist.\n");
  } else {
    if (L->length == 0) {
      Node *new_node = newNode(i);
      L->head = new_node;
    } else {
      Node *curr_node = L->head;
      while (curr_node->next != NULL) {
        curr_node = curr_node->next;
      }
      Node *new_node = newNode(i);
      curr_node->next = new_node;
    }
    L->length += 1;
  }
}

int delElement(List L, int i) {
  if (L->length < i + 1) {
    fprintf(stderr, "Not enough elements in the list.\n");
    return 0;
  }
  // if node is the head node
  if (i == 0) {
    Node *curr_node = L->head; // set a node* to the head of the linked list
    Node *next_node = L->head->next;   // set a node* to the head->next of the linked list
    L->head = next_node; // set the head of the linked list to the head->next of
                         // the linked list
    int data = curr_node->data;
    free(curr_node); // free the memory of the previous head node
    L->length -= 1;
    return data;
  }

  // if node is the end node
  else if (i == L->length - 1) {
    Node *curr_node = L->head; // set a node* to the head of the linked list
    Node *next_node = L->head->next; // set a node* to the head->next of the linked list
    while (next_node->next != NULL) {
      curr_node = curr_node->next; // set curr node to the next node
      next_node = next_node->next; // set next node to the next node
    }
    curr_node->next = NULL; // set the second last node's next to NULL
    int data = next_node->data;
    free(next_node); // delete the last node
    L->length -= 1;
    return data;
  }

  // if node is in the middle
  else {
    Node *curr_node = L->head; // set a node* to the head of the linked list
    Node *next_node = L->head->next; // set a node* to the head->next of the linked list
    int node_counter = 1;
    while (node_counter < i) {
	next_node = next_node->next;
	curr_node = curr_node->next;
	node_counter++;
    }
    curr_node->next = next_node->next;
    int data = next_node->data;
    free(next_node);
    L->length -= 1;
    return data;
  }
  return 1;
}

void printList(List L) {
  Node *curr_node = L->head;
  while (curr_node != NULL) {
    if (curr_node->next == NULL) {
      printf("%d", curr_node->data);
      curr_node = curr_node->next;
    } else {
      printf("%d, ", curr_node->data);
      curr_node = curr_node->next;
    }
  }
  printf("\n");
}
