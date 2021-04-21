#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct Queue {
  int head;
  int tail;
  int length;
  int count;
  int* arr;
} Queue;

Queue* initializeQueue(int n, int* arr) {
  Queue* new_queue = (Queue *) malloc(sizeof(Queue));
  if (new_queue) {
    new_queue->head = 0;
    new_queue->tail = 0;
    new_queue->length = n;
    new_queue->count = 0;
    new_queue->arr = arr;
  }
  return new_queue;
}

void destructQueue(Queue* q) {
  if (q) {
    free(q->arr);
    free(q);
    q = NULL;
  }
}

void enQueue(Queue* q, int x) {
  q->arr[q->tail] = x;
  q->count++; // increases the count of the queue
  if (q->tail != q->length - 1) {
    q->tail++; // increases the tail because an element was added
  } else {
    q->tail = (q->tail + 1) % q->length; // wrap tail to front if it's currenly at the end
  }
}

int deQueue(Queue* q) {
  if (q->length != 0) {
    q->count--;
    int curr = q->arr[q->head];
    q->head++;
    return curr;
  }
  return -1;
}

void printQueue(Queue *q) {
  printf("Queue: ");
  for (int i = q->head; i < q->tail; i++) {
    printf("%d ", q->arr[i]);
  }
  printf("\n");
}

int count(Queue* q) {
  return q->count;
}
