#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <stdio.h>


#include "utils.h"
#include "lexer.h"
#include "globals.h"
#include "exit.h"


#include <string.h>
#include <stdlib.h>
#include <stdlib.h>


/* A linked list implementation to hold all all names of all macros found.  */
typedef struct macroNames { 
    char macroName[MAX_MACRO_NAME];  
    struct macroNames *Next;
} macroNames;


/* A struct implementation of macro. Proprities as described below.*/
typedef struct {
    char name[MAX_MACRO_NAME];
    char **lines; /* Will hold all lines that make a macro*/
    int line_count; /* Amount of lines stored so far */
    int line_capacity; /* Amount of lines there is space allocated for */
} Macro;

/* Forward declaration of Macro_node */
typedef struct Macro_node Macro_node_t;

/* We want it to be dynamic, so again a linked list suffices nicely.*/
struct Macro_node {
    Macro macro;
    Macro_node_t *Next;
};


/**
 * @brief Preprocesses a source file by handling macros.
 *
 * This function processes a given source file to handle macro definitions and expansions.
 * It performs the following steps:
 * 1. Finds and validates all macros in the source file, adding them to a linked list.
 * 2. Removes all macro declarations and replaces macro calls with their corresponding definitions.
 *
 * If any error occurs during macro processing (e.g., open-ended macros, invalid formats, or memory allocation failures),
 * appropriate error messages are displayed, and the process is terminated.
 *
 * @param src A string representing the path to the source file.
 * @param StringHead A pointer to the head of a linked list that holds the names of the macros.
 * @return An integer status code indicating success or specific errors encountered during preprocessing.
 *         On success, it returns the status from saving macros; on failure, it returns `PREPROCESSOR_EXIT_FAIL`.
 */
int preprocessor(char *src, macroNames **StringHead);

/**
 * @brief Scans a source file for macro definitions and saves them to a linked list.
 *
 * This function iterates through the lines of a given source file, searching for macro definitions.
 * When a macro is found, it validates the macro's name and adds it to a linked list if valid. (see Add_macro) 
 * If the macro is invalid or the format is incorrect, it returns the appropriate error code.
 * 
 * The function also rewinds the file pointer to the beginning of the source file after processing.
 *
 * @param Head A pointer to the head of the linked list where macros are stored.
 * @param StringHead A pointer to the head of the linked list that holds the names of the macros.
 * @param Macro_count A pointer to an integer that tracks the number of macros encountered.
 * @param src_file A pointer to the file object representing the source file.
 * @return An integer status code indicating success or specific errors encountered:
 *         - `PREPROCESSOR_EXIT_SUCESSS` if all macros are successfully saved.
 *         - `INVALID_MACRO_ERROR` if an invalid macro name is detected.
 *         - `INVALID_MACRO_FORMAT_ERROR` if the macro format is incorrect.
 */
int Save_macros(Macro_node_t **Head,  macroNames **StringHead,int * Macro_count, FILE* src_file);

/**
 * @brief Adds a new macro to the linked list of macros.
 *
 * This function creates a new macro node and a corresponding string node, then appends them to their respective linked lists.
 * It reads the macro's content from the source file, storing each line in the newly created macro node.
 * If the macro declaration is incomplete or any memory allocation fails, the function returns an error code.
 * 
 * @param Head A pointer to the head of the linked list where macros are stored.
 * @param StringHead A pointer to the head of the linked list that holds the names of the macros.
 * @param macr_name A string representing the name of the macro being added.
 * @param src_file A pointer to the file object representing the source file, currently pointing to the line after the macro name declaration.
 * @return An integer status code indicating success or specific errors encountered:
 *         - `PREPROCESSOR_EXIT_SUCESSS` if the macro is successfully added.
 *         - `MEMORY_ALLOCATION_ERROR` if memory allocation fails for the macro or its contents.
 *         - `GLOBAL_EXIT_FAILURE` if the program encounters a fatal error during allocation.
 *         - `OPEN_ENDED_MACRO_ERROR` if the macro definition is not properly closed with `endmacr`.
 */
int Add_macro(Macro_node_t **Head,macroNames **StringHead,  char * macr_name, FILE* src_file);

/**
 * @brief Writes preprocessed content to a new file, replacing macro calls with their definitions.
 *
 * This function processes a source file to replace macro calls with the corresponding macro definitions stored in a linked list.
 * It skips macro definitions, avoids replacing labels mistakenly identified as macros, and writes the final preprocessed content to a new file with an ".am" extension.
 * If any issues arise, such as mistaking a label for a macro, the function returns NULL.
 *
 * @param Head A pointer to the head of the linked list where macros are stored.
 * @param Macro_count A pointer to an integer tracking the number of macros encountered.
 * @param src_file A pointer to the file object representing the source file.
 * @param src_name A string representing the name of the source file.
 * @return A pointer to the newly created preprocessed file or NULL if an error occurs.
 */
FILE *writeMacros(Macro_node_t **Head, int *Macro_count, FILE *src_file, char *src_name);

/**
 * @brief Checks if a macro with the given name already exists in the macro name linked list.
 *
 * This function iterates through the linked list of macro names and checks if any node's name matches the provided macro name.
 * If a match is found, it returns `TRUE`, indicating that the macro already exists in the list.
 *
 * @param macroName A string representing the name of the macro to check.
 * @param StringHead A pointer to the head of the linked list of macro names.
 * @return An integer value:
 *         - `TRUE` (non-zero) if the macro name is found in the list.
 *         - `FALSE` (zero) if the macro name is not found.
 */
int MacroAlreadyExists(char *macroName, macroNames **StringHead);

/**
 * @brief Frees memory allocated for all macros in the linked list.
 *
 * This function iterates through the linked list of macros and frees the memory associated with each macro node. 
 * It first frees each line stored within a macro, then frees the array of lines, and finally frees the macro node itself.
 *
 * @param Head A pointer to the head of the linked list of macros.
 */
void freeMacros(Macro_node_t **Head);

/**
 * @brief Validates a macro name according to specific rules.
 *
 * This function checks whether the provided macro name is valid. A macro name is considered valid if it:
 * - Does not exceed the maximum allowed length.
 * - Consists only of alphanumeric characters.
 * - Does not already exist in the list of macro names.
 * - Is not a reserved word in the language.
 *
 * @param macro_name A string representing the name of the macro to validate.
 * @param StringHead A pointer to the head of the linked list of macro names.
 * @return An integer value:
 *         - `TRUE` (non-zero) if the macro name is valid.
 *         - `FALSE` (zero) if the macro name is invalid.
 */
int isValidMacro(char *macro_name, macroNames **StringHead);


#endif
