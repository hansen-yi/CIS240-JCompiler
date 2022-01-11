#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "print.h"

int main(int argc, char **argv) {
    if (argc < 2) {
   		exit(EXIT_FAILURE);
  	}
    FILE *file, *outputFile;
    file = fopen(argv[1], "r");
    char *fileName;
    fileName = strtok(argv[1], ".");
    char ext[4] = ".asm"; 
    strncat(fileName, ext, 4);
    outputFile = fopen(fileName, "w");
   
    Stack *theStack = malloc(sizeof(Stack));
    stack_init(theStack);

    token t;
    while (read_token(&t, file) == 0) {
      printToken(outputFile, &t, theStack);
    }
    free(theStack);
    fclose(outputFile);
    fclose(file);
}