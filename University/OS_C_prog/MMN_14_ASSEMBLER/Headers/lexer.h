#ifndef LEXER_H
#define LEXER_H
#include "memory.h"
#include "symbols.h"
#include "exit.h"
#include "utils.h"
#include "globals.h"
#include <fcntl.h>
#include <string.h>
typedef struct {
    const char *mnemonic;
    int operand_count;
    int opcode;
} instruction_t;


int addString(int * DC,MemoryCell Data[], char * directive_definition, code_location am_file);

/* This function will parse all the data declared in the directive definition as seperated by commas
 * It will call another function addNumber which will actually add the data to the data image itself
 * It will keep track of the current index using DC, 
 * and after it's called, it's the job of the caller to properly add DC to the label, 
 * if the directive is part of a a label definition */
int addNumbers(int *DC,MemoryCell Data[], char * directive_definition , code_location am_file);


void cleanCommas(char *instruction);


char * addExternEntry(char * directive_definition , code_location am_file);


int parseInstruction(int *Current_IC,int *IC,MemoryCell Instructions[], char * instruction_definition , code_location am_file);


int isRegister(char * instruction, const char * Registers[]);


int isSavedLanguageWord(char * word_to_check);

char * getAbsoluteNum(char * instruction_definition);


char * getLabelName(char * instruction_definition);

int getLabelAddress(char * label_name, symbol_node ** Head);

int parseRemainingInstruction(int * PC,  MemoryCell Instructions[], char * instruction_definition , code_location am_file, symbol_node ** Head, char * extern_name, int * externOpened);

char * skipOpCode(char * instruction_definition);


int buildOperand(int operand_addressing , char * extern_name,  MemoryCell Instructions[], code_location am_file, symbol_node ** Head, int * externOpened, char * instruction_definition, int * PC);

#endif
