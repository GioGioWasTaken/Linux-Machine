#ifndef FIRST_PASS_H
#define FIRST_PASS_H


#include "exit.h"
#include "preprocessor.h"
#include "utils.h"
#include "globals.h"
#include "memory.h"
#include "lexer.h"
#include "symbols.h"

#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>




#define UNKNOWN_DIRECTIVE 0

#define DATA_DIRECTIVE 1

#define STRING_DIRECTIVE 2

#define EXTERNAL_DIRECTIVE 3

#define ENTRY_DIRECTIVE 4

#define NO_DIRECTIVE 5



/**
 * @brief Performs the first pass of the specified assembly architecture on a source file.
 *
 * This function processes each line of the given assembly source file, identifying and handling
 * labels, directives, adding them to the symbol table as needed. 
 * It also parses instructions: It updates the instruction counter (IC) and data counter (DC)
 * as needed, builds the first word of the instructions, and reports errors if the file does not meet certain criteria. The function also sets 
 * the panic mode if any critical errors are detected, which prevents the generation of output files.
 *
 * @param file_name The name of the source file to be processed. The file should be in the format expected
 *                  by the assembler.
 * @param StringHead Pointer to the head of the macroNames list, which will be used for storing macros.
 * @return Returns `FIRST_PASS_EXIT_SUCESSS` (1) on successful completion of the first pass or
 *         `FIRST_PASS_EXIT_FAIL` (-1) if errors were encountered.
 */
int first_pass(char * file_name, macroNames ** StringHead);

/**
 * @brief Checks if a given string is a valid directive.
 *
 * This function checks the provided string to determine if it matches one of the predefined
 * assembler directives (e.g., `.data`, `.string`, `.extern`, `.entry`). It returns the type 
 * of directive if valid, or `NO_SUCH_DIRECTIVE` if the string does not match any known directive.
 *
 * @param str The string to check, which is expected to be a directive.
 * @return Returns the type of directive if valid, otherwise `NO_SUCH_DIRECTIVE`.
 */
int isValidDirective(char * str);

/**
 * @brief Checks if a given line is a comment.
 *
 * This function determines if the provided line of text is a comment based on the presence of
 * a comment character (`;`) at the beginning of the line. It returns `TRUE` if the line is a comment,
 * otherwise `FALSE`.
 *
 * @param instruction The line of text to check.
 * @return Returns `TRUE` if the line is a comment, otherwise `FALSE`.
 */
int isComment(char * instruction);

/**
 * @brief Validates if a given label name is a valid label.
 *
 * This function performs several checks to ensure that the provided label name meets the criteria
 * for valid labels. It checks the length of the label, whether it contains only alphanumeric characters,
 * and if it conflicts with existing macros or reserved language words.
 *
 * @param label_name The label name to validate.
 * @param Head Pointer to the head of the symbol table to check for existing labels.
 * @param StringHead Pointer to the head of the macro names list to check for conflicts with macros.
 * @return Returns `TRUE` if the label is valid, otherwise `FALSE`.
 */
int isValidLabel(char * label_name, symbol_node ** Head, macroNames ** StringHead);

/**
 * @brief Checks if a label exists in the symbol table with a specific directive type.
 *
 * This function iterates through the symbol table to determine if a label with the given name
 * exists.
 * It also verifies if the label is valid under the given directive type conditions:
 * The function handles special cases where a label might be associated with both entry lines and instructions.
 *
 * @param label_query The name of the label to search for in the symbol table.
 * @param directive_type The type of directive to check against (e.g., ENTRY_DIRECTIVE).
 * @param HEAD Pointer to the head of the symbol table.
 * @return Returns `TRUE` if the label exists and is valid under the specified conditions, otherwise `FALSE`.
 */

int labelExists(char * label_query,int directive_type, symbol_node ** HEAD);

/**
 * @brief Allocates and initializes a new symbol node.
 *
 * This function allocates memory for a new `symbol_node`, initializes its fields to default values,
 * and returns a pointer to the newly created node. If memory allocation fails, it returns `NULL`.
 *
 * @return A pointer to the newly allocated and initialized `symbol_node`, or `NULL` if memory allocation fails.
 */
symbol_node * allocateNewNode(void);
/**
 * @brief Allocates and initializes a new symbol in the symbol table.
 *
 * This function creates a new `symbol_node`, initializes it based on the directive type,
 * and inserts it into the symbol table, either at the start if HEAD is NULL, or at the end if HEAD exists.
 * It handles different directive types including 
 * code lines(NO_DIRECTIVE), data directives, string directives, external directives, and entry directives.
 *
 * @param directive_type The type of directive or instruction being processed.
 * @param Head Pointer to the head of the symbol table linked list.
 * @param IC Pointer to the instruction counter. It is updated if the directive_type is `NO_DIRECTIVE`.
 * @param DC Pointer to the data counter. It is updated if the directive_type is `DATA_DIRECTIVE` or `STRING_DIRECTIVE`.
 * @param am_file Structure containing file-related information such as line number and filename.
 * @param instruction_definition The definition of the directive or instruction, without the label.
 * @param exit_fail Pointer to the exit code. It is updated to indicate failure if an error occurs.
 * @param Data Array representing the data section of memory.
 * @param Instructions Array representing the instruction section of memory.
 * @param label_name The name of the label associated with the directive or instruction, or `NULL` if .entry or .external (name parsed inside the function scope)
 * @return Returns `FIRST_PASS_EXIT_SUCCESS` if successful, or `FIRST_PASS_EXIT_FAIL` if an error occurs.
 */
int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* directive_definition, int * exit_fail,MemoryCell Data[], MemoryCell Instructions[], char * label_name);

/**
 * @brief Allocates memory for directives and updates the data counter.
 *
 * This function processes and allocates memory for directives such as data and string directives.
 * It updates the data counter (`DC`) based on the directive type and performs appropriate memory operations. 
 * It's only used if the directive is not a label.
 *
 * @param directive_type The type of directive being processed (e.g., `DATA_DIRECTIVE`, `STRING_DIRECTIVE`).
 * @param DC Pointer to the data counter. It is updated to point to the next available memory location.
 * @param am_file Structure containing file-related information such as line number and filename.
 * @param directive_definition The definition of the directive, which may include data or strings to be stored.
 * @param exit_fail Pointer to the exit code. It is updated to indicate failure if an error occurs.
 * @param Data Array representing the data section of memory.
 * @return Returns `FIRST_PASS_EXIT_SUCCESS` if successful, or `FIRST_PASS_EXIT_FAIL` if an error occurs.
 */
int allocateDirective(int directive_type , int * DC, code_location am_file, char* directive_definition, int * exit_fail, MemoryCell Data[] );

/**
 * @brief Updates the addresses of data symbols based on the instruction counter.
 *
 * This function (preemptively) adjusts the addresses of symbols marked as data lines by adding the value of the 
 * instruction counter (`IC`) plus one. This is necessary to ensure that data symbols are correctly
 * positioned in memory relative to the code(data always appears after code. They are seperated).
 * The data is actually moved in mergeMemoryImages.
 *
 * @param Head Pointer to the head of the symbol table linked list.
 * @param IC The current instruction counter value, used to update data symbol addresses.
 */

void updateDataSymbols(symbol_node ** Head, int IC);

/**
 * @brief Merges data and instruction memory images into a single memory array.
 *
 * This function combines the instruction memory and data memory into a single memory image.
 * It places the data memory after the end of the instruction memory, adjusting the indices accordingly.
 *
 * @param Data Array representing the data memory.
 * @param Instructions Array representing the instruction memory.
 * @param IC The current instruction counter, which determines the starting position for merging data.
 * @param DC The current data counter, which determines the number of data cells to be merged.
 */

void mergeMemoryImages(MemoryCell Data[],MemoryCell Instructions[], int IC, int DC);

/**
 * @brief Skips over a label in a string and returns a pointer to the content following the label.
 *
 * This function advances a pointer through a string, skipping over a label format (which ends with a colon),
 * as well as any leading and trailing whitespace around the label.
 *
 * @param str Pointer to the string to process. The function will modify this pointer to point to the content
 *            following the label.
 * @return Returns a pointer to the first character of content after the label.
 */

char *skip_label(char *str);

/**
 * @brief Frees all memory allocated for the symbol table.
 *
 * This function iterates through the linked list of symbol nodes, freeing any dynamically allocated memory
 * associated with each node, including the label names. It then deallocates the memory for each node itself.
 *
 * @param Head Pointer to the head of the linked list of symbol nodes. This will be updated as nodes are freed.
 */

void freeSymbols(symbol_node ** Head);

/**
 * @brief Performs the second pass of the assembler.
 *
 * This function processes the assembly file to complete the second pass of compilation, which involves
 * parsing the instructions in order to build the second, or third word (as needed) inside the instruction memory image.
 * it skips all labels, definitions, and updates the entry directives to their corresponding labels. 
 * It also generates output files, and manages errors encountered during the second pass.
 *
 * In summary: The second pass assumes that the first pass has been completed successfully. It performs tasks such as:
 * - Parsing and handling instructions and directives.
 * - Resolving entry labels and setting their addresses.
 * - Generating the object, extern, and entry files and handling external references.
 *
 * @param Code Array of memory cells representing the instruction section of memory.
 * @param IC The initial instruction counter value.
 * @param DC The data counter value.
 * @param Head Pointer to the head of the linked list of symbol nodes.
 * @param am_file The file location and name information for error reporting.
 * @param proc_src File pointer to the processed source code.
 * @return Returns `GLOBAL_EXIT_FAILURE` if a critical error is encountered, otherwise returns `FIRST_PASS_EXIT_SUCCESS`.
 */

int secondPass(MemoryCell Code[], int IC, int DC, symbol_node ** Head, code_location am_file, FILE * proc_src );

#endif
