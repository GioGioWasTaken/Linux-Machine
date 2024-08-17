#ifndef MEMORY_H
#define MEMORY_H


typedef struct MemoryCell{
char FirstByte;
char SecondByte;
}MemoryCell;



int addNumber(int * DC,MemoryCell Data[], char * Number);

int addChar(int * DC,MemoryCell Data[], char chara);

int setMemoryCell(int * DC, MemoryCell * Cell, int value);

int getMemoryCell(int DC, MemoryCell Data[]);

int addInstruction(int * IC,MemoryCell Instructions[], int op_code,int arg_count, int args_addressing[], int ARE);

int setInstructionBits( MemoryCell * Cell, int opcode, int address_src, int address_dest, int ARE);

#endif
