#include <string.h>
#include <stdio.h>
#include <stdlib.h>		// For built-in malloc that returns void *

#include "Dictionary.h"
#include "Enrollment.h"
// create global dictionaries

int main() {
  dictionary* CourseDict = malloc(sizeof(dictionary));
  create(CourseDict, 20);
  element* el = malloc(sizeof(element));
  el->value = NULL;
  scanf("%s", el->key);
  insert(CourseDict, el);
  return 0;
}
