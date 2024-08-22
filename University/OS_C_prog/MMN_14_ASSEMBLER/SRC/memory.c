#include "../Headers/memory.h"
#include "../Headers/exit.h"
#include "../Headers/utils.h"
#include <stdio.h>
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
	Cell->SecondByte|= 0x80; /* 0x80 = 1000 000*/
    }
    (*DC)++;

    return 1;
}

int readWord(MemoryCell Cell) {
    int LSB = Cell.FirstByte;          /* Least significant 8 bits */
    int MSB = Cell.SecondByte;         /* Most significant 6 bits */

    /* Reconstruct the 15-bit value */
    int value = (MSB << 8) | LSB;   /* Combine MSB and LSB */

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

    /* Set the opcode bits (4 second most significant bits in MSB 0(111 1)111 */
    *MSB |= (opcode & 0x0F) << 3;

    /* Set the address_src_bit */
    if(address_src_bit<0){
	printf("Leave source set to 0.\n value: %d\n",address_src_bit);
    } else{

    if (address_src_bit < 8) {
        *LSB |= (SET_BIT << address_src_bit);
    } else {
        *MSB |= (SET_BIT << (address_src_bit - 8));
    }

    }

    if(address_dest_bit<0){
	printf("Leave dest set to 0.\n");
    } else{
	/* Set the address_dest_bit */
	*LSB |= (SET_BIT << address_dest_bit);
    }

    /* Set the ARE bit */
    *LSB |= (SET_BIT << ARE_bit);

    /* Return success */
    return GLOBAL_EXIT_SUCESSS;
}

int addInstruction(int * IC,MemoryCell Instructions[], int op_code,int arg_count, int args_addressing[], int ARE){
    int FirstWordAddress;

    FirstWordAddress = *IC;
    setInstructionBits(&Instructions[*IC], op_code, args_addressing[0],args_addressing[1],ARE);

    if(arg_count==0){
	(*IC)++;
    } else if(arg_count==1){
	(*IC)+=2;
    } else if(arg_count==2){
	(*IC)+=3;
    } 
    return FirstWordAddress;
}


void readAddressingMethods(int addressing_methods[], MemoryCell Instructions[], int IC) {
    MemoryCell currentCell = Instructions[IC];
    int address_dest_bit;
    int address_src_bit;
    char LSB = currentCell.FirstByte;  /* Least significant 8 bits */
    char MSB = currentCell.SecondByte; /* Most significant 8 bits */
    printf("Read addressing methods:");
    printBinary(MSB);
    printBinary(LSB);
    printf("\n");


    /* Extract address_dest_bit from bits 3-6 in LSB */
    address_dest_bit = (LSB >> 3) & 0x0F; /* Mask to get 4 bits (3-6) */

    switch (address_dest_bit) {
	/* Interpret the result of the bit mask as an addressing method referred to by index (same order given in the maman)*/
	/* 0000 1000*/
	case 8:
	    address_dest_bit = DIRECT_REGISTER_ADDRESSING;
	    break;
	case 4: 
	/* 0000 0100, etc... */ 
	    address_dest_bit = INDIRECT_REGISTER_ADDRESSING;
	    break;
	case 2:
	    address_dest_bit = DIRECT_ADDRESSING;
	    break;
	case 1:
	    address_dest_bit = ABSOLUTE_ADDRESSING;
	    break;
	case 0:
	    address_dest_bit = NO_OPERAND_ADDRESSING;
	}
    /* Extract address_src_bits from bits 7-10 in MSB */
    if(LSB>>7 & 0xFF){
	/* adressing method 0  of the source bit is kept in the LSB*/
	address_src_bit = ABSOLUTE_ADDRESSING;
    } else{
	address_src_bit = (MSB << 5) & 0xFF; /* Mask to get 4 bits (7-10) */
	switch (address_src_bit) {
	    case 128:
		address_src_bit = DIRECT_REGISTER_ADDRESSING;
		break;
	    case 64: 
		address_src_bit = INDIRECT_REGISTER_ADDRESSING;
		break;
	    case 32:
		address_src_bit = DIRECT_ADDRESSING;
		break;
	    case 0:
		address_src_bit = NO_OPERAND_ADDRESSING;
	}
    }

    /* Store the extracted bits in the addressing_methods array */
    addressing_methods[0] = address_src_bit;
    addressing_methods[1] = address_dest_bit;
}



int writeAbsoluteValue(MemoryCell * Cell,  code_location am_file, int num_read){
    int SET_BIT = 1;
    int ARE = 2;

    if(num_read > 2047 || num_read < -2048){
	/* signed 12 bit number limit*/
	return INTEGER_OVERFLOW;
    }

    char * LSB = &(Cell->FirstByte);  /* Least significant 8 bits */
    char * MSB = &(Cell->SecondByte); /* Most significant 8 bits */
    /* Set the ARE bit */
    *LSB |= (SET_BIT << ARE);
    if(num_read < 0){
	*MSB |= (SET_BIT << 7);
	num_read*=-1;
    }
    *LSB |= ((num_read & 0x1F) << 3 ); /* last five bits of the number*/
    *MSB |= ((num_read>>5)); /* rest of the bits*/

    printf("Absolutely addressed value written: ");
    printBinary(*MSB);
    printBinary(*LSB);
    printf("\n");
    return GLOBAL_EXIT_SUCESSS;
}




void writeExternAddress(MemoryCell * Cell,  code_location am_file){
    int SET_BIT = 1;
    int ARE = 0;

    char * LSB = &(Cell->FirstByte);  /* Least significant 8 bits */
    char * MSB = &(Cell->SecondByte); /* Most significant 8 bits */
    /* Set the ARE bit */
    *LSB |= (SET_BIT << ARE);

    *LSB |= (SET_BIT << 3); /* set the address value(located right after the 3 ARE bits) to one.*/

    printf("Extern value:");
    printBinary(*MSB);
    printBinary(*LSB);
    printf("\n");
}


int writeLabelAddress(MemoryCell * Cell,  code_location am_file, int address){
    int SET_BIT = 1;
    int ARE = 1;

    if(address > 4095 ){
	/* signed 12 bit number limit*/
	return INTEGER_OVERFLOW;
    }

    char * LSB = &(Cell->FirstByte);  /* Least significant 8 bits */
    char * MSB = &(Cell->SecondByte); /* Most significant 8 bits */
    /* Set the ARE bit */
    *LSB |= (SET_BIT << ARE);

    *LSB |= ((address & 0x1F) << 3 ); /* last five bits of the number*/
    *MSB |= ((address>>5)); /* rest of the bits*/

    printf("Relocatable address value: ");
    printBinary(*MSB);
    printBinary(*LSB);
    printf("\n");
    return GLOBAL_EXIT_SUCESSS;
}



void writeRegisterNumber(MemoryCell * Cell,int source_num,int dest_num){
    int SET_BIT = 1;
    int ARE = 2;

    char * LSB = &(Cell->FirstByte);  /* Least significant 8 bits */
    char * MSB = &(Cell->SecondByte); /* Most significant 8 bits */
    /* Set the ARE bit */
    *LSB |= (SET_BIT << ARE);

    if(source_num!=-1){
	*LSB |= (source_num<<3);
    } if(dest_num!=-1){
	*LSB |= ((dest_num & 0x03) << 6);
	*MSB |= ((dest_num & 0x04) >> 2);
    }

    printf("Register num value: ");
    printBinary(*MSB);
    printBinary(*LSB);
    printf("\n");

}
