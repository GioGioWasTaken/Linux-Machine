#include "Headers/assembler.h"

int main(int argc, char ** argv){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>(without the .as file extension)\nNo .as files provided\n", argv[0]);
        return 1;
    }
    macroNames * StringHead =NULL; /* Used to keep track of the macroNames even after the macro struct is free'd.*/

    /* Step 1: fetch source file(s)*/
    int file_index = 1;
    /* argv[0] is the program name, so we'll start with 1. */
    while(--argc > 0){ /* So long as there are files to process...*/

        /* Step 1: preprocess it*/
        char filename[259]; /* 255 is actually the maximum file name for most file systems, so 255 + .as (or .am) + \0 = 259 */
        snprintf(filename, sizeof(filename), "%s.as", argv[file_index]); 

        int preprocessor_status = preprocessor(filename, &StringHead);

        if(preprocessor_status == PREPROCESSOR_EXIT_FAIL){
            fprintf(stderr, "Error while processing %s. Continuing to next file.\n",argv[argc]);
            continue;
        }

        /*Step 3: First pass && Second pass (which gets called by the first_pass function as needed)*/
        snprintf(filename, sizeof(filename), "%s.am", argv[file_index]); 
        int first_pass_exit = first_pass(filename,&StringHead);
        if(first_pass_exit == FIRST_PASS_EXIT_FAIL){
            /* All errors were reported and a binary cannot be generated. Continue to the next file*/
            continue;
        }


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
