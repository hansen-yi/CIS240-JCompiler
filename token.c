#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

int line_number;

int read_token (token *theToken, FILE *theFile) {
    if (!feof(theFile)) {
        char first[250]="";
        char comment[250];
        char *garbage;
        fscanf(theFile, "%s", first);
        while (first[0] == ';') {
            fgets(comment, 250, theFile); 
            fscanf(theFile, "%s", first);
        }
        if (first[0]=='0' && first[1]=='x') {
            theToken -> type = LITERAL;
            theToken -> literal_value = (int) strtol(first, &garbage, 16);
        }
        else if (isdigit(first[0]) > 0 || (first[0]=='-' && isdigit(first[1]))) {
            theToken -> type = LITERAL;
            theToken -> literal_value = (int) strtol(first, &garbage, 10);
        }
        else if (first[0] == '+') {
            theToken -> type = PLUS;
        }
        else if (first[0] == '-') {
            theToken -> type = MINUS;
        }
        else if (first[0] == '*') {
            theToken -> type = MUL;
        }
        else if (first[0] == '/') {
            theToken -> type = DIV;
        }
        else if (first[0] == '%') {
            theToken -> type = MOD;
        }
        else if (strcmp(first, "and")==0) {
            theToken -> type = AND;
        }
        else if (strcmp(first, "or")==0) {
            theToken -> type = OR;
        }
        else if (strcmp(first, "not")==0) {
            theToken -> type = NOT;
        }
        else if (strcmp(first, "lt")==0) {
            theToken -> type = LT;
        }
        else if (strcmp(first, "le")==0) {
            theToken -> type = LE;
        }
        else if (strcmp(first, "eq")==0) {
            theToken -> type = EQ;
        }
        else if (strcmp(first, "ge")==0) {
            theToken -> type = GE;
        }
        else if (strcmp(first, "gt")==0) {
            theToken -> type = GT;
        }
        else if (strcmp(first, "if")==0) {
            theToken -> type = IF;
        }
        else if (strcmp(first, "else")==0) {
            theToken -> type = ELSE;
        }
        else if (strcmp(first, "endif")==0) {
            theToken -> type = ENDIF;
        }
        else if (strcmp(first, "drop")==0) {
            theToken -> type = DROP;
        }
        else if (strcmp(first, "dup")==0) {
            theToken -> type = DUP;
        }
        else if (strcmp(first, "swap")==0) {
            theToken -> type = SWAP;
        }
        else if (strcmp(first, "rot")==0) {
            theToken -> type = ROT;
        }
        else if (strcmp(first, "defun")==0) {
            theToken -> type = DEFUN;
            fscanf(theFile, "%s", theToken -> str);
        }
        else if (strcmp(first, "return")==0) {
            theToken -> type = RETURN;
        }
        else if (first[0]=='a' && first[1]=='r' && first[2]=='g') {
            if (atoi(&first[3])>20) {
                theToken -> type = BAD_TOKEN;
            }
            else {
                theToken -> type = ARG;
                theToken -> arg_no = atoi(&first[3]);
            }
        }
        else if (isalpha(first[0])) {
            theToken -> type = IDENT;
            strcpy(theToken -> str, first);
        }
        else {
            theToken -> type = BAD_TOKEN;
            //printf("bad token found\n"); //commented out since if there is additional white space at the end will print that bad token exists
            return 1;
        }
       return 0; 
    }
    else {
        return 1;
    }
}