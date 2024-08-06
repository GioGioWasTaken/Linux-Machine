/* The purpose of the UTILS subdirectory is to provide organized space for useful functions
 * that I will be making use of throughout this project. */
/* These functions have no relation to the assembler requirements themselves, 
 * and only serve my comfort and your ease of reading through my code. */

#include "../Headers/utils.h"


void create_file(FILE *file) {
    fflush(file);  /* Flush the file stream buffer to the file */
    int fd = fileno(file);  /* Get the file descriptor from the FILE* pointer */
    fsync(fd);  /* Sync the file descriptor to disk */
}
