#include <stdio.h>
#include "Headers/assembler.h"
#include "Headers/exit.h"
/* Student Name: Iyar Segev
 * ID: 330579889
 * Date submitted: 22/8/2024 
 * This is the main function that kicks the entire assembler into action. */

/* VERY IMPORTANT NOTE
 * When compiled, the file shows a few "implicit function declerations" warnings. THOSE HEADERS WERE INCLUDED. Both inside, and outside my own header files. This warning won't go away no matter what I try.
 * The reason this happens seems to be snprintf not being defined under C90. Therefore I defined my own header:*/

int snprintf(char *str, size_t size, const char *format, ...);

int main(int argc, char ** argv){
    char filename[259]; /* 255 is actually the maximum file name for most file systems, so 255 + .as (or .am) + \0 = 259 */
    int preprocessor_status, file_index;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>(without the .as file extension)\nNo .as files provided\n", argv[0]);
        return GLOBAL_EXIT_FAILURE;
    }

    /* Step 1: fetch source file(s)*/
    file_index = 1;
    /* argv[0] is the program name, so we'll start with 1. */
    while(--argc > 0){ /* So long as there are files to process...*/
        macroNames * StringHead;
        StringHead =NULL; /* Used to keep track of the macroNames even after the macro struct is free'd.*/
        /* Step 1: preprocess it*/
        snprintf(filename, sizeof(filename), "%s.as", argv[file_index]); 
        printf("%s:\n",filename);

        preprocessor_status = preprocessor(filename, &StringHead);

        if(preprocessor_status == PREPROCESSOR_EXIT_FAIL){
            fprintf(stderr, "Error while processing %s. Continuing to next file.\n",argv[argc]);
            /* Free resources*/
            if(StringHead!=NULL){
                freeStrings(&StringHead);
            }
            file_index++;
            continue;
        }

        /*Step 3: First pass && Second pass (which gets called by the first_pass function as needed)*/
        snprintf(filename, sizeof(filename), "%s.am", argv[file_index]); 
        first_pass(filename,&StringHead);

        /* Free resources*/
        freeStrings(&StringHead);

        file_index++;
    }
    printf("All jobs finished.\n");
    return 0;
}


/* Function to free the linked list of macroNames */
void freeStrings(macroNames **Head) {
    macroNames *current = *Head;
    macroNames *next_node = NULL;

    while (current != NULL) {
        next_node = current->Next;  /* Save the next node*/

        /* Free the current node itself*/
        free(current);

        /* Move to the next node*/
        current = next_node;
    }

    /* Set the head to NULL to avoid dangling pointer*/
    *Head = NULL;
}
