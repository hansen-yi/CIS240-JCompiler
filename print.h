#include "token.h"
#include "stack.h"

void prologue(FILE *outputFile);

void epilogue(FILE *outputFile);

void printToken(FILE *outputFile, token *t, Stack *s);