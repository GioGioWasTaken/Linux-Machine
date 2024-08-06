#include "../Headers/preprocessor.h"
#include "../Headers/globals.h"
#include "../Headers/exit.h"
#include <stdio.h>
/*
 * This is the "main" function of the preprocessor. It will return 0 on a sucess, and -1 on a failure.
 * Note that there is no need to return a file discriptor or pointer,
 * since the names of the files follow a specific known in advance format "name.x"
 * where x is the file type.
 * */

int preprocessor(char * src){
    /* Step 0: clean whitespaces for proper parsing */


    /* Load file */
    FILE *src_file = fopen(src, "r");
    if (!src_file) {
        fprintf(stderr,"Source file %s doesn't exist.\n",src);
	return PREPROCESSOR_EXIT_FAIL; /* It is easier in smaller scale projects to use custom error codes.  */
    } 
    
    printf("Preprocessing file\n");
    /* Clean file */

    Macro* Macros = malloc(sizeof(Macro) * MAX_MACRO_AMOUNT);
    /* Step 1: find all macros and add them to the array if and only if they are all valid.*/
    int macro_count = 0;

    int status_save_macros = Save_macros(Macros,  &macro_count, src_file);

    if(status_save_macros == INVALID_MACRO_ERROR || status_save_macros == INVALID_MACRO_FORMAT_ERROR || status_save_macros == DUPLICATE_MACRO_ERROR){
	free(Macros);
	free(src_file);
	/* #NOTE: code this function. It is instructed that if an error is found in this step we discard the file and process the next one. */
	return PREPROCESSOR_EXIT_FAIL;
    } 

    /* Step 2 & 3 : Remove all macro declerations and Replace all macro calls with the macro definitions */
    
    FILE * preprocessed_file = writeMacros(Macros,  &macro_count, src_file);
    create_file(preprocessed_file);
    return PREPROCESSOR_EXIT_SUCESSS;
}




int Save_macros(Macro *Macros,  int * Macro_count,FILE* src_file){
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    int currentMacroIndex = 0;


    /* So long as lines can be read*/
    while(fgets(line, sizeof(line), src_file)){
        if (strncmp(line, "macr ", 5) == 0){
	    char macroName[MAX_MACRO_NAME];

	    if(sscanf(line, "macr %s", macroName) == 1){

		if(isStatement(macroName)){
		    return INVALID_MACRO_ERROR;
		    /* Macro cannot be an opcode*/
		}
		if(MacroAlreadyExists(Macros, Macro_count, macroName)){
		    return DUPLICATE_MACRO_ERROR;
		}
	    } else {
		    return INVALID_MACRO_FORMAT_ERROR;
		    /* Handle case where macro name is not provided*/
		}

	    strncpy(Macros[currentMacroIndex].name, macroName, MAX_MACRO_NAME - 1);
	    Macros[currentMacroIndex].name[MAX_MACRO_NAME - 1] = '\0'; /* Ensure null-termination */


	/* Initiliaze inside macro state */
	    insideMacro = 1; /* Boolean state flag*/
	    Macros[currentMacroIndex].line_count = 0;
	    Macros[currentMacroIndex].lines = malloc(MAX_LINE_LENGTH * sizeof(char *));
	} else if(strncmp(line, "endmacr", 7) == 0){
	    insideMacro = 0;
	} else if(insideMacro){
	    int current_line = Macros[currentMacroIndex].line_count;
	    Macros[currentMacroIndex].lines[current_line] = strdup(line);
	    /* NOTE: strdup is a malloc */
	    Macros[currentMacroIndex].line_count++;
	}

	*Macro_count = currentMacroIndex + 1;
	/* We will keep src_file open for the time being */
    } 
    rewind(src_file);
    return PREPROCESSOR_EXIT_SUCESSS;
}


FILE * writeMacros(Macro *Macros, int *Macro_count, FILE* src_file) {
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    FILE *temp_file = tmpfile(); /* Temporary file to store preprocessed content */
    if (!temp_file) {
        fprintf(stderr, "Could not create temporary file for preprocessing.\n");
        return NULL;
    }

    /* Iterate through each line of the source file */
    printf("writeMacros: \n");
    while (fgets(line, sizeof(line), src_file)) {
	printf("%s\n", line);
        int macro_found = 0;

        /* Check if the line contains the start of a macro definition */
        if (strncmp(line, "macr ", 5) == 0) {
	    printf("macr\n");
            insideMacro = 1;
	    continue;
        }

        /* Check if the line contains the end of a macro definition */
        if (insideMacro && strncmp(line, "endmacr", 7) == 0) {
            insideMacro = 0;
	    printf("endmacr\n");
            continue; /* Skip this line as well */
        }

        /* If inside a macro definition, skip the line */
        if (insideMacro) {
	    printf("Macro line: %s\n", line);
            continue;
        }

        /* Check if the line contains a macro call and replace it */
	int i;
        for (i = 0; i < *Macro_count; i++) {
            if (strstr(line, Macros[i].name) != NULL) {
		printf("Call to macro %s detected\nIt has %d lines\n",Macros[i].name, Macros[i].line_count );
		fflush(stdout);
		macro_found = 1;

                /* Replace macro call with macro definition */


		int j;
                for (j = 0; j < Macros[i].line_count; j++) {
                    fprintf(temp_file, "%s\n", Macros[i].lines[j]);
                }

                break;
            }
        }

        /* If no macro call was found, and we are not inside a macro definition, write the original line to the temp file */
        if (!macro_found) {
	    printf("code line: %s\n", line);
            fprintf(temp_file, "%s\n", line);
        }
    }

    /* Reset the source file pointer and copy from temp file */
    rewind(src_file);
    rewind(temp_file);

    FILE * fully_processed_file = fopen("preprocessed.am", "w");
    printf("Preprocessed file: \n");
    while (fgets(line, sizeof(line), temp_file)) {
	printf("%s\n",line );
        fprintf(fully_processed_file, "%s", line);
    }


    free(temp_file);
    free(src_file);

    return fully_processed_file; /* Return the preprocessed file  */
}




int isStatement(char * macroName){
    /* NOTE: For now we'll just return false. */
    return 0;
}



int MacroAlreadyExists(Macro * Macros, int *Macro_count, char * macroName){
    /* NOTE: For now we'll just return false. */
    return 0;
}
