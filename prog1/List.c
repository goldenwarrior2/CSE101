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
  int biggest = 0;
  Node *curr_node = L->head;
  while (curr_node != NULL) {
    if (curr_node->data > biggest) {
      biggest = curr_node->data;
    }
    curr_node = curr_node->next;
  }
  return biggest;
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
    Node *next_node =
        L->head->next;   // set a node* to the head->next of the linked list
    L->head = next_node; // set the head of the linked list to the head->next of
                         // the linked list
    int data = curr_node->data;
    free(curr_node); // free the memory of the previous head node
    return data;
  }

  // if node is the end node
  else if (i == L->length - 1) {
    Node *curr_node = L->head; // set a node* to the head of the linked list
    Node *next_node =
        L->head->next; // set a node* to the head->next of the linked list
    while (next_node->next != NULL) {
      curr_node = curr_node->next; // set curr node to the next node
      next_node = next_node->next; // set next node to the next node
    }
    curr_node->next = NULL; // set the second last node's next to NULL
    int data = next_node->data;
    free(next_node); // delete the last node
    return data;
  }

  // if node is in the middle
  else {
    Node *curr_node = L->head; // set a node* to the head of the linked list
    Node *next_node =
        L->head->next; // set a node* to the head->next of the linked list
    for (int node = 0; node < L->length; node++) {
      if (node == i - 1) { // because we want to delete the node when next_node
                           // is at index i not when curr_node is at index i
        curr_node->next =
            next_node->next; // set the curr_node's next to next_node's next
        int data =
            next_node->data; // save the data of the node we are going to delete
        free(next_node);     // delete the node
        return data;
      }
      curr_node = curr_node->next;
      next_node = next_node->next;
    }
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
