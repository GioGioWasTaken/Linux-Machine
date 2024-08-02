/* The purpose of the UTILS subdirectory is to provide organized space for useful functions
 * that I will be making use of throughout this project. */
/* These functions have no relation to the assembler requirements themselves, 
 * and only serve my comfort and your ease of reading through my code. */

#include "../Headers/utils.h"

FILE * create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
		fprintf(stderr, "Error while creating file:  %s\n", filename);
		// currently not defined what happens when one of the input files of the assembler fails to assemble.
    }
    return file;
}
