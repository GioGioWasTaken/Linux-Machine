#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "globals.h"
#include <ctype.h>


typedef struct code_location{
char * filename;
int line_number;
} code_location;


/**
 * @brief Prints an assembly time error message based on the given error code and code location.
 *
 * This function displays an error message corresponding to the provided error code. 
 * The message includes the file name and line number where the error occurred. 
 * After printing the error message, the output is flushed to ensure it is immediately visible.
 *
 * @param error_code The specific error code indicating the type of assembly error.
 * @param am_file The structure containing the file name and line number of the error.
 */
void print_assemble_time_error(int error_code, code_location am_file);

/**
 * @brief Prints an assembler warning message based on the given warning code and code location.
 *
 * This function displays a warning message corresponding to the provided warning code. 
 * The message includes the file name and line number where the warning occurred.
 *
 * @param error_code The specific warning code indicating the type of assembler warning.
 * @param am_file The structure containing the file name and line number of the warning.
 */
void print_assembler_warning(int error_code, code_location am_file);

/**
 * @brief Skips leading whitespace characters in a string.
 *
 * This function takes a pointer to a string pointer and advances the pointer 
 * past any leading whitespace characters (e.g., spaces, tabs).
 *
 * @param str A double pointer to the string to be processed. The string pointer 
 *            will be updated to point to the first non-whitespace character.
 */
void skipWhitespace(char** str);

/**
 * @brief Removes the trailing newline character from a string.
 *
 * This function checks the last character of the string. If it is a newline character (`\n`),
 * the function replaces it with a null terminator (`\0`), effectively removing the newline.
 *
 * @param str The string from which to remove the trailing newline.
 */
void removeTrailingNewline(char *str);
/**
 * @brief Checks if a string contains only alphanumeric characters.
 *
 * This function iterates through each character of the string and checks if it's 
 * either a letter or a digit. If all characters are alphanumeric, it returns TRUE (1). 
 * If any character is not alphanumeric, it returns FALSE (0).
 *
 * @param str The string to check.
 * @return int Returns TRUE (1) if the string is alphanumeric, otherwise returns FALSE (0).
 */
int isAlphaNumericString(char * str);

/* this function was used through my debugging process. I thought i'd still leave it in, just in case. */

void printBinary(char byte);

/**
 * @brief Checks if any line in the specified file exceeds the maximum line length.
 *
 * This function opens the file pointed to by `file_name`, reads through each line,
 * and determines if any line exceeds `MAX_LINE_LENGTH` characters. It then rewinds
 * the file pointer to the beginning for further use.
 *
 * @param file_name The name of the file to check.
 * @return Returns 1 (TRUE) if any line exceeds the maximum length, otherwise 0 (FALSE) .
 */
int line_too_long_exists(char *file_name);

#endif

