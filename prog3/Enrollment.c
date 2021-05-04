#include <string.h>
#include <stdio.h>
#include <stdlib.h>		// For built-in malloc that returns void *

#include "Dictionary.h"
#include "Enrollment.h"
// create global dictionaries
dictionary CourseDict;
dictionary StudentDict;

int main() {
  create(&CourseDict, 20);
  element* new_element = malloc(sizeof(element));
  scanf("%s", new_element->key);
  insert(&CourseDict, new_element);
  printf("%s", find(&CourseDict, "12345")->key);
  return 0;
}
