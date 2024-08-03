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


FILE * preprocessor(char * src);

FILE * Trim_file(FILE * src);

int Save_macros(Macro *Macros, FILE* clean_file, int * Macro_count);



int isStatement(char * macroName);
#endif
