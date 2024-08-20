#ifndef FIRST_PASS_H
#define FIRST_PASS_H


#include "exit.h"
#include "preprocessor.h"
#include "utils.h"
#include "globals.h"
#include "memory.h"
#include "lexer.h"

#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct label_t {
    int address;
    char *label_name;
    /* The reason I implemented it as a pointer (and in first-pass.c allocated a full line length ot it ) and not a fixed-size char array of size 31,
     * is because the user might try to make a longer label despite it being illegal.
    I decided that a label name being too long should not crash the program.
    It's safer if it persists and exists under my conditions instead, when I check for label integrity. */
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




int first_pass(char * file_name, macroNames ** StringHead);

int isValidDirective(char * str);

int isComment(char * instruction);

int isValidLabel(char * label_name, symbol_node ** Head, macroNames ** StringHead);

int labelExists(char * label_query,int directive_type, symbol_node ** HEAD);



symbol_node * allocateNewNode(void);

int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* directive_definition, int * exit_fail,MemoryCell Data[], MemoryCell Instructions[], char * label_name);

int allocateDirective(int directive_type , int * DC, code_location am_file, char* directive_definition, int * exit_fail, MemoryCell Data[] );

void updateDataSymbols(symbol_node ** Head, int IC);

void mergeMemoryImages(MemoryCell Data[],MemoryCell Instructions[], int IC, int DC);

char *skip_label(char *str);

void freeSymbols(symbol_node ** Head);


int secondPass(MemoryCell Code[], int IC, int DC, symbol_node ** Head, code_location am_file, FILE * proc_src );

#endif
