#include "../Headers/preprocessor.h"
#include "../Headers/globals.h"
/*
 * This is the "main" function of the preprocessor. It will return 0 on a sucess, and -1 on a failure.
 * Note that there is no need to return a file discriptor or pointer,
 * since the names of the files follow a specific known in advance format "name.x"
 * where x is the file type.
 * */

FILE * preprocessor(char * src){
    /* Step 0: clean whitespaces for proper parsing */


    /* Load file */
    FILE *src_file = fopen(src, "r");
    if (!src_file) {
        fprintf(stderr,"Source file %s doesn't exist.\n",src);
        return NULL;
    } 
    
    /* Clean file */

    FILE *Clean_file= Trim_file(src_file);
    Macro *Macros;

    /* Step 1: find all macros and add them to the array*/
    if(!Save_macros(Macros, Clean_file)){
	free(Macros);
	// #NOTE: code this function
	exit_current_file();
	return 0;
    } 

    /* Step 2: Check for macro calls before definition, a macro declared more than once, a call for macro that doesn't exist*/

    /* Step 3: Remove all macro declerations */

    /* Step 4: Replace all macro calls with the macro definitions */
}

int Save_macros(Macro *Macros, FILE* clean_file){
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    int currentMacroIndex = -1;


    /* So long as lines can be read*/
    while(fgets(line, sizeof(line), clean_file)){
        if (strncmp(line, "macr ", 5) == 0){
	
	}
    } 


}
