#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <stdio.h>
#include "utils.h"
#include <string.h>
#include "globals.h"
#include <stdlib.h>
#include <stdlib.h>

typedef struct {
    char name[MAX_MACRO_NAME];
    char **lines; /* Will hold all lines that make a macro*/
    int line_count; /* Amount of lines stored so far */
    int line_capacity; /* Amount of lines there is space allocated for */
} Macro_t;

/* Forward declaration of Macro_node */
typedef struct Macro_node_t Macro_node_t;

typedef struct Macro_node_t{
    Macro_t macro;
    Macro_node_t *Next;
} Macro_node_t;

int preprocessor(char * src);


int Save_macros(Macro_node_t **Head,  int * Macro_count, FILE* src_file);

int Add_macro(Macro_node_t **Head,  char * macr_name, FILE* src_file);

FILE * writeMacros(Macro_node_t **Head,int * Macro_count,FILE* src_file);

int MacroAlreadyExists(Macro_node_t **Head, int *Macro_count, char * macroName);

int isIllegalName(char * macroName);

void freeMacros(Macro_node_t ** Head);

#endif
