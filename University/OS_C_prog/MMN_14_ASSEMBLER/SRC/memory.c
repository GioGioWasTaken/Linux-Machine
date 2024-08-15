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

int addNumber(int * DC,MemoryCell Data[], char * Number){
    int number = atoi(Number);
    if(setMemoryCell(DC, &Data[*DC], number) == INTEGER_OVERFLOW){
	return INTEGER_OVERFLOW;
    }
    return 1;
}
