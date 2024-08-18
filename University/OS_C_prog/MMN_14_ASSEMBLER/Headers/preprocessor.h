#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "utils.h"
#include "lexer.h"
#include "globals.h"
#include "exit.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>


typedef struct macroNames {
    char macroName[MAX_MACRO_NAME];  
    struct macroNames *Next;
} macroNames;


typedef struct {
    char name[MAX_MACRO_NAME];
    char **lines; /* Will hold all lines that make a macro*/
    int line_count; /* Amount of lines stored so far */
    int line_capacity; /* Amount of lines there is space allocated for */
} Macro;

/* Forward declaration of Macro_node */
typedef struct Macro_node Macro_node_t;

typedef struct Macro_node {
    Macro macro;
    Macro_node_t *Next;
} Macro_node_t;

int preprocessor(char * src, macroNames ** StringHead);

int Save_macros(Macro_node_t **Head,  macroNames **StringHead,int * Macro_count, FILE* src_file);

int Add_macro(Macro_node_t **Head,macroNames **StringHead,  char * macr_name, FILE* src_file);

FILE * writeMacros(Macro_node_t **Head, int *Macro_count, FILE* src_file, char* src_name);

int MacroAlreadyExists(char * macroName, macroNames ** StringHead);

int isValidMacro(char * macro_name, macroNames ** StringHead);

void freeMacros(Macro_node_t ** Head);

#endif
