#include "../Headers/exit.h"
#include "../Headers/memory.h"
#include "../Headers/utils.h"
#include <stdlib.h>



int setMemoryCell(int * DC, MemoryCell * Cell, int value){
    if(value < -16384 || value > 16383){
	return INTEGER_OVERFLOW;
    }
    /* Store the least significant 8 bits in FirstByte*/
    Cell->FirstByte =  value &0xFF; 
    /* Store the most significant 6 bits (without the sign bit )*/
    Cell->SecondByte = (value>>8) &0x3F; /* 0x3F=  00 1111 */
    if(value <0){
	Cell->SecondByte|= 0x40; /* 0x40 = 0100 00*/
    }
    (*DC)++;

    /* printf("Set memory: FirstByte: 0x%02X, SecondByte: 0x%02X\n", Cell->FirstByte, Cell->SecondByte);  */
    return 1;
}

int getMemoryCell(int DC, MemoryCell Data[]) {
    MemoryCell Cell = Data[DC];
    int LSB = Cell.FirstByte;          /* Least significant 8 bits */
    int MSB = Cell.SecondByte;         /* Most significant 6 bits */

    /* Check if the sign bit is set */
    int sign = (MSB & 0x40) >> 6;  /* Extract the sign bit */
    
    /* Remove the sign bit from MSB */
    MSB &= 0x3F;  /* Mask out the sign bit */

    /* Reconstruct the 15-bit value */
    int value = (MSB << 8) | LSB;   /* Combine MSB and LSB */

    /* If the sign bit is set, make the value negative */
    if (sign) {
        value |= 0x8000;  /* Set the sign bit in the 16-bit value */
        value = (short)value;  /* Convert to signed 15-bit value */
    }

    return value;
}

/* BUG: some bug while storing "214". Look into it.*/
int addNumber(int * DC,MemoryCell Data[], char * Number){
    int number = atoi(Number);
    if(setMemoryCell(DC, &(Data[*DC]), number) == INTEGER_OVERFLOW){
	return INTEGER_OVERFLOW;
    }
    return 1;
}

int addChar(int * DC,MemoryCell Data[], char chara){
    /* ascii values are just the normal values of chars. chars at the end of the day are just a 1 bit integer that we choose to interpret as a letter.*/
    if(setMemoryCell(DC, &Data[*DC], chara) == INTEGER_OVERFLOW){
	printf("Integer overflow with a char. This should NEVER happen");
	return INTEGER_OVERFLOW;
    }
    return 1;
}

int setInstructionBits( MemoryCell * Cell, int opcode, int address_src, int address_dest, int ARE){
    /* The bits we need to set for each one of these values passed */
    int SET_BIT = 1;
    int address_src_bit = 7 + address_src;
    int address_dest_bit = 3 + address_dest;
    int ARE_bit = ARE;

    char * LSB = &(Cell->FirstByte);          /* Least significant 8 bits */
    char * MSB = &(Cell->SecondByte);         /* Most significant 8 bits (7 bits are used) */

    /* Clear the LSB and MSB to avoid unwanted set bits */
    *LSB = 0;
    *MSB = 0;

    /* Set the opcode bits (4 most significant bits in MSB) */
    *MSB |= (opcode & 0x0F) << 4;

    /* Set the address_src_bit */
    if(address_src_bit<0){
	printf("No arguments op code: Leave source set to 0. value: %d\n",address_src_bit);
    } else{

    if (address_src_bit < 8) {
        *LSB |= (SET_BIT << address_src_bit);
    } else {
        *MSB |= (SET_BIT << (address_src_bit - 8));
    }

    }

    if(address_dest_bit<0){
	printf("no arguments op code: leave dest set to 0.\n");
    } else{
	/* Set the address_dest_bit */
	*LSB |= (SET_BIT << address_dest_bit);
    }

    /* Set the ARE bit */
    *LSB |= (SET_BIT << ARE_bit);

    /* Return success */
    return 1;
}

int addInstruction(int * IC,MemoryCell Instructions[], int op_code,int arg_count, int args_addressing[], int ARE){
    int FirstWordAddress;
    if(arg_count==0){
	FirstWordAddress = *IC;
	setInstructionBits(&Instructions[*IC], op_code, args_addressing[0],args_addressing[1],ARE);
	(*IC)++;
    } else if(arg_count==1){
	FirstWordAddress = *IC;
	setInstructionBits(&Instructions[*IC], op_code, args_addressing[0],args_addressing[1],ARE);
	(*IC)+=2;
    } else if(arg_count==2){
	FirstWordAddress = *IC;
	setInstructionBits(&Instructions[*IC], op_code, args_addressing[0],args_addressing[1],ARE);
	(*IC)+=3;
    } 
    return FirstWordAddress;
}

