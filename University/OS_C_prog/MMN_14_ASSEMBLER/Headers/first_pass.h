#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "lexer.h"
#include "tables.h"

typedef struct code_location{
char * filename;
int line_number;
} code_location;

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

#define EXTERNAL_DIRECTIVE 2

#define ENTRY_DIRECTIVE 3

#define NO_DIRECTIVE 4




int first_pass(char * file_name);

int isValidDirective(char * str);

int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* directive_definition);

#endif

