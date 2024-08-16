#ifndef FIRST_PASS_H
#define FIRST_PASS_H


#include "exit.h"
#include "utils.h"
#include "globals.h"
#include "memory.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct label_t {
    int address;
    char *label_name;
    int is_data_line ;
    int is_external_line;
    int is_entry_line;
} label_t;


/* Forward declaration of Macro_node */
typedef struct symbol_node symbol_node;

typedef struct symbol_node {
    label_t symbol;
    symbol_node * Next;
}symbol_node;



#define UNKNOWN_DIRECTIVE 0

#define DATA_DIRECTIVE 1

#define STRING_DIRECTIVE 2

#define EXTERNAL_DIRECTIVE 3

#define ENTRY_DIRECTIVE 4

#define NO_DIRECTIVE 5




int first_pass(char * file_name);

int isValidDirective(char * str);

int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* directive_definition, int * exit_fail,MemoryCell Data[], MemoryCell Instructions[], char * label_name);


void freeSymbols(symbol_node ** Head);

int isValidLabel(char * label_definition, symbol_node ** Head );

int allocateDirective(int directive_type , int * DC, code_location am_file, char* directive_definition, int * exit_fail, MemoryCell Data[] );

#endif
