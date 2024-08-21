#ifndef MEMORY_H
#define MEMORY_H

#include "utils.h"

typedef struct MemoryCell{
char FirstByte;
char SecondByte;
}MemoryCell;



int addNumber(int * DC,MemoryCell Data[], char * Number);

int addChar(int * DC,MemoryCell Data[], char chara);

int setMemoryCell(int * DC, MemoryCell * Cell, int value);

int readWord(int DC, MemoryCell Data[]);

int addInstruction(int * IC,MemoryCell Instructions[], int op_code,int arg_count, int args_addressing[], int ARE);

int setInstructionBits( MemoryCell * Cell, int opcode, int address_src, int address_dest, int ARE);

int readAddressingMethods(int addressing_methods[], MemoryCell Instructions[], int IC);

int writeAbsoluteValue(MemoryCell * Cell,  code_location am_file, int num_read);

void writeExternAddress(MemoryCell * Cell,  code_location am_file);

int writeLabelAddress(MemoryCell * Cell,  code_location am_file, int address);

void writeRegisterNumber(MemoryCell * Cell,int source_num,int dest_num);
#endif
