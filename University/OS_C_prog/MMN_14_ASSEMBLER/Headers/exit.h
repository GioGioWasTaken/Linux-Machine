#ifndef EXIT_H
#define EXIT_H

/* Exit codes for different parts of the assembler*/

#define PREPROCESSOR_EXIT_SUCESSS 1

#define FIRST_PASS_EXIT_SUCESSS 1

#define PREPROCESSOR_EXIT_FAIL -1

#define FIRST_PASS_EXIT_FAIL -1

#define LEXER_EXIT_SUCESS 1

#define LEXER_EXIT_FAIL -1

/* Errors: */

#define INVALID_MACRO_ERROR -2

#define INVALID_MACRO_FORMAT_ERROR -3

#define DUPLICATE_MACRO_ERROR -4

#define NO_SUCH_FILE -5

#define MEMORY_ALLOCATION_ERROR -6

#define LINE_TOO_LONG_ERROR -7

#define OPEN_ENDED_MACRO_ERROR -8

#define INVALID_DIRECTIVE_ERROR -9

#define INVALID_DIRECTIVE_DEFINITION -10

/* Warnings: */
#define UNDEFINED_LABEL_WARNING -100

#endif
