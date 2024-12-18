/* The purpose of the UTILS subdirectory is to provide organized space for useful functions
 * that I will be making use of throughout this project. */
/* These functions have no relation to the assembler requirements themselves, 
 * and only serve my comfort and your ease of reading through my code. */

#include "../Headers/utils.h"
#include <unistd.h>
#include "../Headers/exit.h"


void print_assemble_time_error(int error_code, code_location am_file){
    printf("\n\nError found in %s", am_file.filename);
    printf(" in line %d\n\n", am_file.line_number);
    switch (error_code) {
        case INVALID_DIRECTIVE_DEFINITION_NO_SPACE:
            printf("Error: Invalid directive definition - no space after directive.\n");
            fflush(stdout);
            break;
        case INVALID_DIRECTIVE_DEFINITION_NO_ARGS:
            printf("Error: Invalid directive definition - no arguments provided.\n");
            fflush(stdout);
            break;
        case UNCLOSED_STRING_ERROR:
            printf("Error: Unclosed string encountered.\n");
            fflush(stdout);
            break;
        case INTEGER_OVERFLOW:
            printf("Error: Integer overflow detected.\n");
            fflush(stdout);
            break;
        case MEMORY_ALLOCATION_ERROR:
            printf("Error: Memory allocation failed.\n");
            fflush(stdout);
            break;
        case NO_SUCH_DIRECTIVE:
            printf("Error: No such directive exists.\n");
            fflush(stdout);
            break;
        case INVALID_DIRECTIVE:
            printf("Error: Invalid directive encountered.\n");
            fflush(stdout);
            break;
        case INVALID_LABEL_ERROR:
            printf("Error: Invalid label found.\n");
            fflush(stdout);
            break;
        case NO_SUCH_OPCODE:
            printf("Error: this instruction does not exist.\n");
            fflush(stdout);
            break;
        case NO_SUCH_REGISTER:
            printf("Error: This register does not exist. The registers available for use are:\nr0-r7 (inclusive)\n");
            fflush(stdout);
            break;
        case TOO_MANY_ARGUMENTS:
            printf("Error: Too many arguments provided. \n");
            fflush(stdout);
            break;
        case NO_SUCH_LABEL:
            printf("Error: .entry was defined but no such label was found.\n");
            fflush(stdout);
            break;
        case INVALID_ADDRESSING_METHOD:
            printf("Error: an unknown symbol was referenced.\n");
            fflush(stdout);
            break;
        default:
            printf("Error: Unknown error code.\n");
            fflush(stdout);
            break;
    }
}

void print_assembler_warning(int error_code, code_location am_file){
    printf("Warning in file %s ", am_file.filename);
    printf("in line %d: ", am_file.line_number);
    switch (error_code) {
        case UNDEFINED_LABEL_WARNING:
            printf("assigning a label to .extern or .entry is meaningless and the assembler ignores this.\n");
    };
}


void skipWhitespace(char** str) {
    while (**str && isspace((unsigned char)**str)) {
        (*str)++;
    }
}

void removeTrailingNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int isAlphaNumericString(char * str) {
    char * local_str = str;
    char current_char = *local_str;

    while (current_char != '\0') {
        if (!isalnum((unsigned char) current_char)) {
            return FALSE;  /* Return FALSE if any character is not alphanumeric*/
        }
        local_str++;
        current_char = *local_str;
    }

    return TRUE;  /* Return TRUE if all characters are alphanumeric*/
}

void printBinary(char byte) {
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
}


int line_too_long_exists(char *file_name) {
    FILE *file = fopen(file_name, "r");
    char line[MAX_LINE_LENGTH+1];  /* Buffer size: MAX_LINE_LENGTH, defined in globals.h. +1 , in case it exceeds the length*/

    if (file == NULL) {
        perror("Error opening file");
        return 0;  /* Assume no lines exceed the length if the file cannot be opened */
    }


    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) >= MAX_LINE_LENGTH ) {
            /* If the length is bigger than MAX_LINE_LENGTH   */
            rewind(file);
            fclose(file);
            return TRUE;
        }
    }

    /* Rewind the file to the beginning */
    rewind(file);

    fclose(file);
    return FALSE;
}
