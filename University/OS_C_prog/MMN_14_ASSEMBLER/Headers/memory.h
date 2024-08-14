#ifndef MEMORY_H
#define MEMORY_H

typedef struct MemoryCell{
char FirstByte;
char SecondByte;
}MemoryCell;



int addNumber(int * DC,MemoryCell Data[], char * Number);

int addChar(int * DC,MemoryCell Data[], char * directive_definition );

int addInstruction(int * IC,MemoryCell Instructions[], char * directive_definition );

#endif
