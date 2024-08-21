#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include "utils.h"
#include "exit.h"

#define is_not_instruction_label (Current_instruction->symbol.is_entry_line == 1 || \
                                  Current_instruction->symbol.is_data_line == 1 || \
                                  Current_instruction->symbol.is_external_line == 1)

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



void writeEntry(FILE * entryOUT, char * entry_name, int addr );

void writeExtern(FILE *externOUT, char *extern_name, int addr);

void createEntryOutput(symbol_node ** Head, char entryOUT[]);

int setEntryAddress(char * directive_name, symbol_node ** Head);

void deleteExternOutput(symbol_node **Head, char *output_name);

#endif
