#include <stdio.h>
#include "Headers/utils.h"
#include "Headers/preprocessor.h"

int main(int argc, char ** argv){
    /* Step 1: fetch source file(s)*/
    while(--argc > 0){ /* So long as there are files to process...*/

    /* Step 1: preprocess it*/
    FILE * processed = preprocessor(argv[argc]); // placeholder until I read the instructions properly

    /*Step 3: First pass */

    /* Final Step: Second pass */


    /* Free resources*/
    }
    printf("All jobs finished.\n");
    return 0;
}
