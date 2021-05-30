#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "List.h"


node* createList(int n)
{
	node* new = (node*)malloc(sizeof(node));
	new->next = NULL;
	new->prev = NULL;
	new->value = n;
	return new;
}
