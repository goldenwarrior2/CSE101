#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Heap.c"
#include "PriorityQueue.h"

// returns largest element in heap/hightest priority
int get_max(Heap* h) {
  return h->arr[0];
}

// extracts and returns max element in heap
// note that heap property must be maintained after extraction
// also check for valid input (cannot extract from empty heap)
// referenced chapter 6 in the book
int extract_max(Heap* h) {
  int max;
  if (h->size < 1) {
    fprintf(stderr, "heap underflow");
    return -1;
  } else {
    max = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size = h->size - 1;
    heapify(h, 0);
    return max;
  }
}

// This function increases priority/value of element at index i to 'new_value'
// referenced chapter 6 in the book
void increase_priority(Heap* h, int i, int new_value){
  if ((new_value) < h->arr[i]) {
    fprintf(stderr, "new key smaller than current key");
  } else {
    h->arr[i] = new_value;
    while (i > 0 && h->arr[parent(i)] < h->arr[i]) {
      swap(h->arr, i, parent(i));
      i = parent(i);
    }
  }
}

// This function inserts priority 'value' into heap
// referenced chapter 6 in the book
void insert(Heap* h, int value) {
  h->size = h->size + 1;
  h->arr[h->size - 1] = -1;
  increase_priority(h, h->size - 1, value);
}
