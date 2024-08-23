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


/**
 * @brief Determines the opcode corresponding to a mnemonic from a string.
 *
 * This function parses the input string to extract the mnemonic and then compares it
 * with a list of predefined opcodes to find a match. If a match is found, the corresponding
 * opcode is returned. Otherwise, an error code is returned.
 *
 * @param str The input string containing the mnemonic and potentially other content.
 * @param OPCODES An array of instruction_t structures containing mnemonics and their corresponding opcodes.
 * @return int The opcode corresponding to the mnemonic if a match is found; otherwise, an error code.
 */
int determine_opcode(char *str, const instruction_t OPCODES[]);


int addString(int * DC,MemoryCell Data[], char * directive_definition, code_location am_file);

/* This function will parse all the data declared in the directive definition as seperated by commas
 * It will call another function addNumber which will actually add the data to the data image itself
 * It will keep track of the current index using DC, 
 * and after it's called, it's the job of the caller to properly add DC to the label, 
 * if the directive is part of a a label definition */
int addNumbers(int *DC,MemoryCell Data[], char * directive_definition , code_location am_file);


void cleanCommas(char *instruction);


char * addExternEntry(char * directive_definition , code_location am_file);


/**
 * @brief Parses an instruction definition and adds the instruction to memory.
 *
 * This function processes a string representing an instruction, determines its opcode,
 * parses its arguments, and adds the instruction to the memory array. It handles various
 * addressing modes and performs error checking for invalid opcodes and arguments.
 *
 * @param Current_IC A pointer to the current instruction counter.
 * @param IC A pointer to the instruction counter -- increment it while running.
 * @param Instructions An array of memory cells where the instruction will be stored.
 * @param instruction_definition The string containing the instruction definition to be parsed.
 * @param am_file A structure containing file and line information for error reporting.
 * @return int Returns a success or error code indicating the outcome of the parsing.
 */
int parseInstruction(int *Current_IC, int *IC, MemoryCell Instructions[], char *instruction_definition, code_location am_file);


/**
 * @brief Checks if a given string represents a valid register.
 *
 * This function compares the provided string to known register names to determine if it
 * matches any of the valid register names. Registers are assumed to be two characters long.
 *
 * @param instruction The string representing a register.
 * @param Registers An array of valid register names.
 * @return int Returns TRUE (1) if the string is a valid register, otherwise FALSE (0).
 */
int isRegister(char *instruction, const char *Registers[]);


/**
 * @brief Checks if a given word is a reserved language keyword.
 *
 * This function determines if the provided word matches any of the reserved keywords used
 * in the assembly language, including register names and opcode mnemonics.
 *
 * @param word_to_check The string to be checked against reserved keywords.
 * @return int Returns TRUE (1) if the word matches a register name or opcode mnemonic, otherwise FALSE (0).
 */
int isSavedLanguageWord(char *word_to_check);

/**
 * @brief Retrieves the address of a label from the symbol table.
 *
 * This function searches the symbol table for a given label name and returns its address if found.
 * If the label is marked as external, it returns -1. If the label is not found, it returns
 * a predefined error code indicating that no such label exists.
 *
 * @param label_name The name of the label whose address is to be retrieved.
 * @param Head A pointer to the head of the symbol table list.
 * @return int The address of the label if found, -1 if the label is external, or NO_SUCH_LABEL if the label does not exist.
 */
int getLabelAddress(char *label_name, symbol_node **Head);

/**
 * @brief Parses the remaining instruction and processes operands.
 *
 * This function processes the remaining part of an instruction, handles operand addressing,
 * and updates the program counter accordingly. It supports different addressing modes and
 * ensures that operands are correctly interpreted and stored.
 *
 * @param PC Pointer to the program counter, which will be updated based on the instruction's length.
 * @param Instructions Array of memory cells where the parsed instruction will be stored.
 * @param instruction_definition The definition of the instruction to be parsed.
 * @param am_file The location information of the file where the instruction is found, used for error reporting.
 * @param Head Pointer to the head of the symbol table list, used for label resolution.
 * @param extern_name name of the extern file, depending on the name of the original .as file.
 * @param externOpened Flag indicating if the external file was already opened. 
 * @return int Returns `LEXER_EXIT_SUCESS` upon successful parsing and processing of the instruction.
 */
int parseRemainingInstruction(int *PC, MemoryCell Instructions[], char *instruction_definition, code_location am_file, symbol_node **Head, char *extern_name, int *externOpened);


/**
 * @brief Builds and writes an operand to the instruction memory based on the addressing mode.
 *
 * This function processes an operand based on its addressing method and writes the corresponding 
 * value to the instruction memory. It handles different addressing methods including absolute, 
 * direct, and register addressing. The function also manages external labels and creates or 
 * appends more data to an existing external file if necessary.
 *
 * @param operand_addressing The addressing method for the operand. It can be one of the following:
 *        - `ABSOLUTE_ADDRESSING`
 *        - `DIRECT_ADDRESSING`
 *        - `INDIRECT_REGISTER_ADDRESSING`
 *        - `DIRECT_REGISTER_ADDRESSING`
 * @param extern_name Name of the external file to be created or appended to if the operand is an external label.
 * @param Instructions Array of memory cells where the operand value will be written.
 * @param am_file The location information of the file where the instruction is found, used for error reporting.
 * @param Head Pointer to the head of the symbol table list, used for label resolution.
 * @param externOpened Flag indicating if an external file was already made
 * @param instruction_definition The definition of the operand to be processed.
 * @param PC Pointer to the program counter, which is updated based on the operand's length.
 *
 * @param is_only_operand Flag indicating if it's the only operand of the expression
 * @param is_second_operand Flag indicating if it's the second Operand of the expression
 *
 * Together, these two flags let use determine how to set the first and second word in case a register is one of those words.
 *
 * @return int Returns `LEXER_EXIT_SUCESS` upon successful processing and writing of the operand. 
 *         Returns an error code if an issue is encountered, such as `INTEGER_OVERFLOW` or `INVALID_ADDRESSING_METHOD`.
 */
int buildOperand(int operand_addressing , char * extern_name,  MemoryCell Instructions[], code_location am_file, symbol_node ** Head, int * externOpened, char * instruction_definition, int * PC, int is_only_operand, int is_second_operand);

#endif
