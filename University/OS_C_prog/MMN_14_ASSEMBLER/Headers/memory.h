#ifndef MEMORY_H
#define MEMORY_H

#include "utils.h"

typedef struct MemoryCell{
char FirstByte;
char SecondByte;
}MemoryCell;



/**
 * @brief Adds a number to the data section of memory.
 *
 * This function converts a string representation of a number to an integer and stores it in the
 * memory cell array. It updates the data counter (DC) and handles integer overflow errors.
 *
 * @param DC Pointer to the data counter, which tracks the current position in the data array.
 * @param Data Array of memory cells representing the data section of memory.
 * @param Number String representation of the number to be added.
 * @return Returns 1 if the number is successfully added, or INTEGER_OVERFLOW if an overflow occurs.
 */
int addNumber(int *DC, MemoryCell Data[], char *Number);

/**
 * @brief Adds a character to the data section of memory.
 *
 * This function adds a character to the memory cell array. Characters are treated as
 * integers within the range of 1 byte. It handles integer overflow errors by ensuring
 * that the value fits within the expected range for a character.
 *
 * @param DC Pointer to the data counter, which tracks the current position in the data array.
 * @param Data Array of memory cells representing the data section of memory.
 * @param chara The character to be added.
 * @return Returns 1 if the character is successfully added, or INTEGER_OVERFLOW if an overflow occurs.
 */
int addChar(int *DC, MemoryCell Data[], char chara);

/**
 * @brief Sets the value of a memory cell.
 *
 * This function stores a value in a memory cell, checking for overflow conditions. It splits
 * the value into two parts: the least significant byte and the most significant byte (with sign handling).
 *
 * @param DC Pointer to the data counter, which tracks the current position in the data array.
 * @param Cell Pointer to the memory cell where the value will be stored.
 * @param value The integer value to be stored in the memory cell.
 * @return Returns 1 if the value is successfully set, or INTEGER_OVERFLOW if an overflow occurs.
 */
int setMemoryCell(int *DC, MemoryCell *Cell, int value);

/**
 * @brief Adds an instruction to memory and updates the instruction counter.
 *
 * This function stores an instruction into the memory, increments the instruction counter 
 * based on the number of operands, and returns the address of the first word of the instruction.
 *
 * @param IC Pointer to the instruction counter. It will be updated to point to the next free location after storing the instruction.
 * @param Instructions Array of memory cells representing the instruction section of memory.
 * @param op_code The operation code for the instruction to be stored.
 * @param arg_count The number of arguments for the instruction.
 * @param args_addressing Array of addressing methods for the instruction's arguments.
 * @param ARE The addressing mode of the instruction (absolute, relative, or external).
 * @return Returns the address of the first word of the instruction in memory.
 */
int addInstruction(int * IC, MemoryCell Instructions[], int op_code, int arg_count, int args_addressing[], int ARE);

/**
 * @brief Sets the instruction bits in a memory cell.
 *
 * This function configures the bits in a memory cell for the first word of an instruction by setting the opcode, source 
 * and destination address bits, and the Addressing Mode (ARE) bits. It updates the least significant byte 
 * (LSB) and most significant byte (MSB) of the memory cell to reflect these settings.
 *
 * @param Cell Pointer to the memory cell to be updated. It contains the least significant byte and most 
 *             significant byte where the bits will be set.
 * @param opcode The operation code (opcode) for the instruction. It determines the operation type.
 * @param address_src The source address for the instruction, which is used to specify the source operand.
 * @param address_dest The destination address for the instruction, used to specify the destination operand.
 * @param ARE The Addressing Mode (ARE) for the instruction, which determines the addressing mode (absolute, 
 *            relative, or external).
 * @return Returns `GLOBAL_EXIT_SUCCESS` upon successful execution. If any invalid conditions are encountered, 
 *         it prints an error message but still returns success.
 */
int setInstructionBits( MemoryCell * Cell, int opcode, int address_src, int address_dest, int ARE);

/**
 * @brief Reads and interprets addressing methods from the the first word instruction memory cell.
 *
 * This function extracts the addressing methods for the source and destination operands from a memory cell 
 * containing an instruction. The methods are read from specific bits in the least significant byte (LSB) and 
 * most significant byte (MSB) of the memory cell.
 *
 * @param addressing_methods Array to store the addressing methods for source and destination operands. 
 *                           The first element will store the source addressing method, and the second element 
 *                           will store the destination addressing method.
 * @param Instructions Array of memory cells representing the instructions.
 * @param IC Instruction counter index used to access the specific instruction in the `Instructions` array.
 * @return Returns 0 on success.
 */

void readAddressingMethods(int addressing_methods[], MemoryCell Instructions[], int IC);

/**
 * @brief Writes an absolutely addressed value (prepended by # ) 
 * into a memory cell with a specific addressing format.
 *
 * This function encodes a signed 12-bit signed absolutely value into a memory cell, considering the 
 * specified ARE bit it was told to set.
 * It also handles the conversion of negative values and ensures the value fits within the 12-bit limit.
 *
 * @param Cell Pointer to the memory cell where the value will be written.
 * @param am_file Location of the code file (used for error reporting).
 * @param num_read The signed 12-bit absolutely value to be written into the memory cell.
 * @return Returns `GLOBAL_EXIT_SUCESSS` on success or `INTEGER_OVERFLOW` if the value exceeds 
 *         the 12-bit signed range.
 */

int writeAbsoluteValue(MemoryCell * Cell,  code_location am_file, int num_read);

/**
 * @brief Writes an extern address into a memory cell with a specific addressing format.
 *
 * This function encodes an extern address into a memory cell, setting the Addressing Register 
 * Extension (ARE) bit to 0 (external addressing) and marking the extern address within the cell,
 * by setting the address value to 1.
 *
 * @param Cell Pointer to the memory cell where the extern address will be written.
 * @param am_file Location of the code file (used for debugging purposes).
 */

void writeExternAddress(MemoryCell * Cell,  code_location am_file);

/**
 * @brief Writes a label address into a memory cell with a specific addressing format.
 *
 * This function encodes a label address into a memory cell, setting the Addressing Register 
 * Extension (ARE) bit to 1 (Direct addressing) and marking the address within the cell.
 *
 * @param Cell Pointer to the memory cell where the label address will be written.
 * @param am_file Location of the code file (used for debugging purposes).
 * @param address The label address to be written into the memory cell.
 * 
 * @return Status code indicating success or failure (e.g., GLOBAL_EXIT_SUCESSS or INTEGER_OVERFLOW).
 */

int writeLabelAddress(MemoryCell * Cell,  code_location am_file, int address);

/**
 * @brief Writes register numbers into a memory cell. The function expects valid registers (this is checked elsewhere).
 *
 * This function encodes the source and destination register numbers into the memory cell, setting
 * the Addressing Register Extension (ARE) bit and placing the register numbers into the appropriate
 * bits in the LSB and MSB.
 * Its behaviour changes depending on if both a source_num and a dest_num are provided, according to the specification given in MAMAN 14.
 *
 * @param Cell Pointer to the memory cell where the register numbers will be written.
 * @param source_num The source register number to be written (0-7), or -1 if not used.
 * @param dest_num The destination register number to be written (0-7) or -1 if not used.
 */

void writeRegisterNumber(MemoryCell * Cell,int source_num,int dest_num);





/**
 * @brief Reads a 15-bit value from a memory cell.
 *
 * This function reads a value from a specified memory cell and reconstructs it from its
 * stored least significant byte (LSB) and most significant byte (MSB). It correctly handles
 * sign extension for negative values.
 *
 * @param DC The data counter, which specifies the index of the memory cell to read from.
 * @param Data Array of memory cells representing the data section of memory.
 * @return Returns the reconstructed 15-bit value. If the value was originally negative, it will be negative.
 */
int readWord(MemoryCell Cell);

#endif
