#include <stdbool.h>

typedef struct stack_node_st {
  int ifelse;
  int num;
  struct stack_node_st *next;
} stack_node;

typedef struct Stack_st {
  stack_node *first, *second;
} Stack;

void stack_init(Stack *s);

void addToStack(Stack *s, int iforelse, int decimal);

stack_node peek(Stack *s);

bool drop(Stack *s);

void clear(Stack *s);
