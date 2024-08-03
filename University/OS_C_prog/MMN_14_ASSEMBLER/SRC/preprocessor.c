#include "../Headers/preprocessor.h"
#include "../Headers/globals.h"
#include "../Headers/exit.h"
#include <stdio.h>
#include <string.h>
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

    /* Step 1: find all macros and add them to the array if and only if they are all valid.*/
    int macro_count = 0;
    int status_save_macros = Save_macros(Macros, Clean_file, &macro_count);
    if(status_save_macros == INVALID_MACRO_ERROR || status_save_macros == INVALID_MACRO_FORMAT_ERROR ){
	free(Macros);
	/* #NOTE: code this function. It is instructed that if an error is found in this step we discard the file and process the next one. */
	exit_current_file();
    } 

    /* Step 2:  a macro declared more than once */

    /* Step 3: Remove all macro declerations */

    /* Step 4: Replace all macro calls with the macro definitions */
}




int Save_macros(Macro *Macros, FILE* clean_file, int * Macro_count){
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    int currentMacroIndex = 0;


    /* So long as lines can be read*/
    while(fgets(line, sizeof(line), clean_file)){
        if (strncmp(line, "macr ", 5) == 0){

	    char macroName[MAX_MACRO_NAME];

	    if(sscanf(line, "macr %s", macroName) == 1){
		if(isStatement(macroName)){
		    return INVALID_MACRO_ERROR;
		    /* Macro cannot be an opcode*/
		} else {
		    return INVALID_MACRO_FORMAT_ERROR;
		    /* Handle case where macro name is not provided*/
		}

	    }
	    strncpy(Macros[currentMacroIndex].name, macroName, MAX_MACRO_NAME - 1);
	    Macros[currentMacroIndex].name[MAX_MACRO_NAME - 1] = '\0'; // Ensure null-termination


	/* Initiliaze inside macro state */
	    insideMacro = 1; /* Boolean state flag*/
	    currentMacroIndex++;
	    Macros[currentMacroIndex].line_count = 0;
	    Macros[currentMacroIndex].lines = malloc(MAX_LINE_LENGTH * sizeof(char *));
	} else if(strncmp(line, "endmacr", 7) == 0){
	    insideMacro = 0;
	} else if(insideMacro){
	    int current_line = Macros[currentMacroIndex].line_count;
	    Macros[currentMacroIndex].lines[current_line] = strdup(line);
	    //NOTE: strdup is a malloc
	    Macros[currentMacroIndex].line_count++;
	}

	*Macro_count = currentMacroIndex + 1;
	fclose(clean_file);
    } 
    return PREPROCESSOR_EXIT_SUCESSS;
}




FILE * Trim_file(FILE * src){

}



int isStatement(char * macroName){

}
