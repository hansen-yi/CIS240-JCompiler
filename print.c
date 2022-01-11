#include <stdio.h> 
#include <stdlib.h>
#include "print.h"

int unique = 0;
int ifcounter = 0;

void prologue(FILE *outputFile) {
    fprintf(outputFile, "\tADD R6 R6 #-3\n");
    fprintf(outputFile, "\tSTR R7 R6 #1\n");
    fprintf(outputFile, "\tSTR R5 R6 #0\n");
    fprintf(outputFile, "\tADD R5 R6 #0\n\n");
}

void epilogue(FILE *outputFile) {
    fprintf(outputFile, "\tLDR R0 R6 #0\n");
    fprintf(outputFile, "\tSTR R0 R5 #2\n");
    fprintf(outputFile, "\tADD R6 R5 #0\n");
    fprintf(outputFile, "\tLDR R5 R6 #0\n");
    fprintf(outputFile, "\tLDR R7 R6 #1\n");
    fprintf(outputFile, "\tADD R6 R6 #2\n");
    fprintf(outputFile, "\tRET\n\n");
}

void printToken(FILE *outputFile, token *t, Stack *s) {
    if (t->type == DEFUN) {
        fprintf(outputFile, ".CODE\n");
        fprintf(outputFile, ".FALIGN\n");
        fprintf(outputFile, "%s", t->str);
        prologue(outputFile);
    }
    if (t->type == IDENT) {
        fprintf(outputFile, "\tJSR %s\n", t->str);
    }
    if (t->type == RETURN) {
        epilogue(outputFile);
    }
    if (t->type == PLUS) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tADD R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == MINUS) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tSUB R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == MUL) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tMUL R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == DIV) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tDIV R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == MOD) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tMOD R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }

    if (t->type == AND) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tAND R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == OR) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tOR R0 R0 R1\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == NOT) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tNOT R0 R0\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }

    if (t->type == LT) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n"); //a
        fprintf(outputFile, "\tLDR R1 R6 #1\n"); //b
        fprintf(outputFile, "\tCMP R0 R1\n"); //a-b
        fprintf(outputFile, "\tBRn TRUE_%d\n", unique); //branch to TRUE_#
        fprintf(outputFile, "\tCONST R0 #0\n"); //store 0 in R0
        fprintf(outputFile, "\tJMP CMP_END_%d\n", unique); //jmp to edn
        fprintf(outputFile, "TRUE_%d\n", unique); //true branch
        fprintf(outputFile, "\tCONST R0 #1\n"); //store 1 in R0
        fprintf(outputFile, "CMP_END_%d", unique); //end branch
        unique++;
        fprintf(outputFile, "\tADD R6 R6 #1\n"); //decrease the stack
        fprintf(outputFile, "\tSTR R0 R6 #0\n"); //store 0 or 1 at the top
    }
    if (t->type == LE) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n"); //a
        fprintf(outputFile, "\tLDR R1 R6 #1\n"); //b
        fprintf(outputFile, "\tCMP R0 R1\n"); //a-b
        fprintf(outputFile, "\tBRnz TRUE_%d\n", unique); //branch to TRUE_#
        fprintf(outputFile, "\tCONST R0 #0\n"); //store 0 in R0
        fprintf(outputFile, "\tJMP CMP_END_%d\n", unique); //jmp to edn
        fprintf(outputFile, "TRUE_%d\n", unique); //true branch
        fprintf(outputFile, "\tCONST R0 #1\n"); //store 1 in R0
        fprintf(outputFile, "CMP_END_%d", unique); //end branch
        unique++;
        fprintf(outputFile, "\tADD R6 R6 #1\n"); //decrease the stack
        fprintf(outputFile, "\tSTR R0 R6 #0\n"); //store 0 or 1 at the top
    }
    if (t->type == EQ) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n"); //a
        fprintf(outputFile, "\tLDR R1 R6 #1\n"); //b
        fprintf(outputFile, "\tCMP R0 R1\n"); //a-b
        fprintf(outputFile, "\tBRz TRUE_%d\n", unique); //branch to TRUE_#
        fprintf(outputFile, "\tCONST R0 #0\n"); //store 0 in R0
        fprintf(outputFile, "\tJMP CMP_END_%d\n", unique); //jmp to edn
        fprintf(outputFile, "TRUE_%d\n", unique); //true branch
        fprintf(outputFile, "\tCONST R0 #1\n"); //store 1 in R0
        fprintf(outputFile, "CMP_END_%d", unique); //end branch
        unique++;
        fprintf(outputFile, "\tADD R6 R6 #1\n"); //decrease the stack
        fprintf(outputFile, "\tSTR R0 R6 #0\n"); //store 0 or 1 at the top
    }
    if (t->type == GE) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n"); //a
        fprintf(outputFile, "\tLDR R1 R6 #1\n"); //b
        fprintf(outputFile, "\tCMP R0 R1\n"); //a-b
        fprintf(outputFile, "\tBRzp TRUE_%d\n", unique); //branch to TRUE_#
        fprintf(outputFile, "\tCONST R0 #0\n"); //store 0 in R0
        fprintf(outputFile, "\tJMP CMP_END_%d\n", unique); //jmp to edn
        fprintf(outputFile, "TRUE_%d\n", unique); //true branch
        fprintf(outputFile, "\tCONST R0 #1\n"); //store 1 in R0
        fprintf(outputFile, "CMP_END_%d", unique); //end branch
        unique++;
        fprintf(outputFile, "\tADD R6 R6 #1\n"); //decrease the stack
        fprintf(outputFile, "\tSTR R0 R6 #0\n"); //store 0 or 1 at the top
    }
    if (t->type == GT) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n"); //a
        fprintf(outputFile, "\tLDR R1 R6 #1\n"); //b
        fprintf(outputFile, "\tCMP R0 R1\n"); //a-b
        fprintf(outputFile, "\tBRp TRUE_%d\n", unique); //branch to TRUE_#
        fprintf(outputFile, "\tCONST R0 #0\n"); //store 0 in R0
        fprintf(outputFile, "\tJMP CMP_END_%d\n", unique); //jmp to edn
        fprintf(outputFile, "TRUE_%d\n", unique); //true branch
        fprintf(outputFile, "\tCONST R0 #1\n"); //store 1 in R0
        fprintf(outputFile, "CMP_END_%d", unique); //end branch
        unique++;
        fprintf(outputFile, "\tADD R6 R6 #1\n"); //decrease the stack
        fprintf(outputFile, "\tSTR R0 R6 #0\n"); //store 0 or 1 at the top
    }

    if (t->type == IF) {
        addToStack(s, 0, ifcounter);
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tADD R6 R6 #1\n");
        fprintf(outputFile, "\tCMPI R0 #0\n");
        fprintf(outputFile, "\tBRz ELSE_%d\n", ifcounter);


        fprintf(outputFile, "IF_END_%d\n", ifcounter);
        ifcounter++;
    }

    if (t->type == ELSE) {
        stack_node top;
        top = peek(s);
        int topNum = top.num;
        addToStack(s, 1, topNum);
        fprintf(outputFile, "\tJMP ENDIF_%d\n", topNum);
        fprintf(outputFile, "ELSE_%d\n", topNum);

    }

    if (t->type == ENDIF) {
        stack_node top;
        top = peek(s);
        int topNum = top.num;
        if (top.ifelse == 0) {
            drop(s);
            fprintf(outputFile, "ELSE_%d\n", topNum);
        }
        else if (top.ifelse == 1) {
            drop(s);
            drop(s);
            fprintf(outputFile, "ENDIF_%d\n", topNum);
        }
        
    }

    if (t->type == DROP) {
        fprintf(outputFile, "\tADD R6 R6 #1\n");
    }
    if (t->type == DUP) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tADD R6 R6 #-1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }
    if (t->type == SWAP) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tSTR R0 R6 #1\n");
        fprintf(outputFile, "\tSTR R1 R6 #0\n");
    }
    if (t->type == ROT) {
        fprintf(outputFile, "\tLDR R0 R6 #0\n");
        fprintf(outputFile, "\tLDR R1 R6 #1\n");
        fprintf(outputFile, "\tLDR R2 R6 #2\n");
        fprintf(outputFile, "\tSTR R0 R6 #1\n");
        fprintf(outputFile, "\tSTR R1 R6 #2\n");
        fprintf(outputFile, "\tSTR R2 R6 #0\n");
    }

    if (t->type == ARG) {
        fprintf(outputFile, "\tLDR R0 R5 #%d\n", (t->arg_no + 2));
        fprintf(outputFile, "\tADD R6 R6 #-1\n");
        fprintf(outputFile, "\tSTR R0 R6 #0\n");
    }

    if (t->type == LITERAL) {
        fprintf(outputFile, "\tADD R6 R6 #-1\n");
        fprintf(outputFile, "\tCONST R0 #%d\n", t->literal_value & 255);
        fprintf(outputFile, "\tHICONST R0 #%d\n", (t->literal_value & 65280) >> 8);
        fprintf(outputFile, "\tSTR R0 R6 #0\n");        
    }
}

