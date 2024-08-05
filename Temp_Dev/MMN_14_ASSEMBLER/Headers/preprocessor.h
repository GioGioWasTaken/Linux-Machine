#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <stdio.h>
#include "utils.h"
#include <string.h>
#include "globals.h"
#include <stdlib.h>

typedef struct {
    char name[MAX_MACRO_NAME];
    char **lines; /* Will hold all lines that make a macro*/
    int line_count;
} Macro;


typedef struct Macro_node {
    int index;
    Macro macro;
    Macro_node *Next;
} Macro_node;


FILE * preprocessor(char * src);

FILE * Trim_file(FILE * src);

int Save_macros(Macro_node *Head, FILE* clean_file, int * Macro_count);



int isStatement(char * macroName);
#endif
