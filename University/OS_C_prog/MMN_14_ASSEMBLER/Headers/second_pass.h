
#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "first_pass.h"

int setEntryAddress(char * directive_name, symbol_node ** Head);

void createEntryOutput(symbol_node ** Head, char entryOUT[]);

void writeEntry(FILE * entryOUT, char * entry_name, int addr );

void deleteExternOutput(symbol_node **Head, char *output_name);

#endif
