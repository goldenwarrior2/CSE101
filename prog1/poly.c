#include "List.h"
#include <stdio.h>

int main(void) {
  struct ListObj *new_list = newList();
  appendList(new_list, 1);
  appendList(new_list, 2);
  appendList(new_list, 3);
  printList(new_list);
  printf("element deleted: %d\n", delElement(new_list, 3));
  printList(new_list);
  return 0;
}
