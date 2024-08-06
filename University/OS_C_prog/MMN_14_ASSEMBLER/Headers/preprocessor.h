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


int preprocessor(char * src);


int Save_macros(Macro *Macros,int * Macro_count,FILE* src_file);

int MacroAlreadyExists(Macro * Macros, int *Macro_count, char * macroName);

FILE * writeMacros(Macro *Macros,int * Macro_count,FILE* src_file);

int isStatement(char * macroName);
#endif
