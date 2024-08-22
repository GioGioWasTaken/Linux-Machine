#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_LINE_LENGTH 82 /* nullterminator and \n characters included. */


#define MAX_MACRO_NAME 76 /* Whitespace character included. len("macr ") + 76 = 81*/

#define Initial_lines 50 /* Initial amounts of lines we allocate for a macro. Lines are implemented with realloc.*/

#define MAX_LABEL_LENGTH 32 /* nullterminator character included. */
/* NOTE: ":" is not included.*/

#define OPCODES_COUNT 16

#define REGISTER_COUNT 8

#define IC_INITIAL 100

#define IC_MAX 1200

#endif
