#include "List.h"
#include <stdio.h>

int main(void) {
  struct ListObj *new_list = newList();
  appendList(new_list, 5);
  appendList(new_list, 6);
  appendList(new_list, 7);
  printList(new_list);
  printf("The biggest element is: %d\n", max(new_list));
  printf("The element %d is at index %d\n", 8, find(new_list, 8));
  // printList(new_list);
  // printf("element deleted: %d\n", delElement(new_list, 1));
  // printList(new_list);
  freeList(&new_list);
  return 0;
}
