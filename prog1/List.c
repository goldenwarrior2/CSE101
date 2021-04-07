#include <stdio.h>
#include "List.h"

typedef struct NodeObj {
    int data;
    struct NodeObj *next;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
    Node head;
    int length;
} ListObj;
