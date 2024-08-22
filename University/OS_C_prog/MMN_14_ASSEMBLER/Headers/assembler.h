#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <unistd.h>
#include "exit.h"
#include "preprocessor.h"
#include "first_pass.h"



/**
 * @brief The main function for the assembler program.
 *
 * This function processes source assembly files specified by the user, performing preprocessing,
 * a first pass, and a second pass of assembly code. It handles multiple files and manages resources
 * for the macro names string linked list.
 *
 * @param argc Argument count, typically the number of command-line arguments.
 * @param argv Argument vector, an array of strings representing the command-line arguments.
 * @return Returns 0 if all files were processed successfully, or 1 if there was an error in the usage or processing.
 */
int main(int argc, char **argv);



/**
 * @brief Frees the memory allocated for a linked list of macro names.
 *
 * This function iterates through the linked list of `macroNames` nodes, freeing each node's memory.
 * After freeing all nodes, it sets the head pointer to NULL to avoid dangling pointers.
 *
 * @param Head Pointer to the head of the linked list of `macroNames` nodes.
 */
void freeStrings(macroNames **Head);
#endif
