/* The purpose of the UTILS subdirectory is to provide organized space for useful functions
 * that I will be making use of throughout this project. */
/* These functions have no relation to the assembler requirements themselves, 
 * and only serve my comfort and your ease of reading through my code. */

#include "../Headers/utils.h"
#include "../Headers/exit.h"
#include "../Headers/first_pass.h"

#include <stdio.h>

void create_file(FILE *file) {
    fflush(file);  /* Flush the file stream buffer to the file */
    int fd = fileno(file);  /* Get the file descriptor from the FILE* pointer */
    fsync(fd);  /* Sync the file descriptor to disk */
}


int isIllegalName(char * macroName) {
    return 0;
}

int line_too_long_exists(char * file_name){
    return 0;
}

void print_assemble_time_error(int error_code, code_location am_file){
    printf("Error found in %s", am_file.filename);
    printf("in line %d\n", am_file.line_number);
    switch (error_code) {
    
    };
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

