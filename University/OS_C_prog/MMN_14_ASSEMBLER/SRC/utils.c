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
    switch (error_code) {
    
    };

    printf("in line %d\n", am_file.line_number);
}
