#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

int main(void) {
  int* array = (int *)calloc(100, sizeof(int));
  Queue* new_queue = initializeQueue(100, array);
  int num;
  while (scanf("%d", &num) != -100) {
    if (num > 0) {
      enQueue(new_queue, num);
    }
    else if (num == -1) {
      deQueue(new_queue);
    }
    else if (num == 0) {
      printQueue(new_queue);
    }
    else if(num == -100) {
      break;
    }
  } 
  printQueue(new_queue); 
  destructQueue(new_queue);
  return 0;
}
