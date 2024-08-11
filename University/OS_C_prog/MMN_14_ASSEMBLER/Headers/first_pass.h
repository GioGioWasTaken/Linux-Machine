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
    int is_data_line;
} label_t;


int first_pass(char * file_name);

int isValidDataLabel(char * str);

int isValidNonDataLabel(char * str);

// int allocate_directive_tables(extern_table * external,entry_table * entries, CodeDataTable * code, CodeDataTable * data);

#endif

