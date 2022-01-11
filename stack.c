#include <stdio.h> 
#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *s) {
  s->first = NULL;
  s->second = NULL;
}

void addToStack(Stack *s, int iforelse, int decimal) {
  stack_node *node = malloc(sizeof(stack_node));
  
  if (node == NULL) {
    printf("Couldn't allocate space for a new stack node\n");
    exit(EXIT_FAILURE);
  }
  
  node->next = NULL;
  node->ifelse = iforelse;
  node->num = decimal;
  
  if (!s->first) {
    s->first = node;
  } else {
    s->second = s->first;
    s->first = node;
    s->first->next = s->second;
  }
}

stack_node peek(Stack *s){
  return *s -> first;
}

bool drop(Stack *s) {
  if (!s->first) {
    return false;
  }
  stack_node* newFirst;
  stack_node* newSec;
  if (!s->second) {
    newFirst = NULL;
    newSec = NULL;
  } else {
    newFirst = s->second;
    newSec = s->second->next;
  }
  free(s->first);
  s->first=newFirst;
  s->second=newSec;
  return true;
}

void clear(Stack *s) {
  while(drop(s));
}