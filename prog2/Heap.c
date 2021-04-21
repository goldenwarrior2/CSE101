// Implementation of (Max) Heap
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Heap.h"

int parent(int i) {
  return (i - 1) /2;
}

int left(int i) {
  return (2 * i) + 1;
}

int right(int i) {
  return (2 * i) + 2;
}

void swap (int* arr, int i, int j) {
  int temp = arr[i]; // stores arr[i] in a temp
  arr[i] = arr[j]; // makes arr[i] equal to value in arr[j]
  arr[j] = temp; // makes arr[j] equal to value of temp which is arr[i]'s prev value
}

typedef struct Heap {
  int len;
  int size;
  int* arr;
} Heap;

Heap* initializeHeap(int len, int h_size, int* arr) {
  Heap* new_heap = (Heap*) malloc(sizeof(Heap));
  if (new_heap) {
    new_heap->len = len;
    new_heap->size = h_size;
    new_heap->arr = arr;
  } else {
    fprintf(stderr, "malloc failed");
  }
  return new_heap;
}

void destructHeap(Heap* h) {
  if (h) {
    free(h->arr);
    free(h);
    h = NULL;
  }
}

void heapify(Heap* h, int i) {
  int l = left(i);
  int r = right(i);
  int largest;
  if (l <= h->size && h->arr[l] > h->arr[i]) {
    largest = l;
  } else {
    largest = i;
  }
  if (r <= h->size && h->arr[r] > h->arr[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(h->arr, i, largest);
    heapify(h, largest);
  }
}

Heap* array_to_Heap(int* A, int len, int size) {
  size = len;
  Heap* new_heap = initializeHeap(len, size, A);
  for (int i = len / 2; i >= 0; i--) {
    heapify(new_heap, i);
  }
  return new_heap;
}

int size(Heap* h) {
  return h->size;
}

int len(Heap* h) {
  return h->len;
}
