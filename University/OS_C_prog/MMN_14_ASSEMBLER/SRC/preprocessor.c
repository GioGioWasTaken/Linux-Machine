#include "../Headers/preprocessor.h"
#include "../Headers/globals.h"
#include "../Headers/exit.h"
#include <complex.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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

    Macro_node Head;
    Head.Next=NULL;


    /* Step 1: find all macros and add them to the array if and only if they are all valid.*/
    int macro_count = 0;

    int status_save_macros = Save_macros(&Head,  &macro_count, src_file);

    if(status_save_macros == INVALID_MACRO_ERROR || status_save_macros == INVALID_MACRO_FORMAT_ERROR || status_save_macros == DUPLICATE_MACRO_ERROR){
	freeMacros(&Head);
	fclose(src_file);
	/* #NOTE: It is instructed that if an error is found in the preprocessing step we discard the file and process the next one. */
	return PREPROCESSOR_EXIT_FAIL;
    } 

    /* Step 2 & 3 : Remove all macro declerations && Replace all macro calls with the macro definitions */
    
    FILE * preprocessed_file = writeMacros(&Head,  &macro_count, src_file);
    create_file(preprocessed_file);
    fclose(preprocessed_file);
    freeMacros(&Head);

    fclose(src_file);

    fclose(preprocessed_file);

    return PREPROCESSOR_EXIT_SUCESSS;
}




int Save_macros(Macro_node *Head,  int * Macro_count, FILE* src_file){
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    int currentMacroIndex = 0;
    Macro_node * current_macro = Head;

    printf("Saving Macros...\n");

    /* So long as lines can be read*/
    while(fgets(line, sizeof(line), src_file)){
        if (strncmp(line, "macr ", 5) == 0){
	    char macroName[MAX_MACRO_NAME];

	    if(sscanf(line, "macr %s", macroName) == 1){

		if(isIllegalName(macroName)){
		    return INVALID_MACRO_ERROR;
		    /* Macro cannot be an opcode*/
		}
		if(MacroAlreadyExists(Head, Macro_count, macroName)){
		    return DUPLICATE_MACRO_ERROR;
		} else{
		    strncpy(current_macro->macro.name, macroName, MAX_MACRO_NAME - 1);
		    current_macro->macro.name[MAX_MACRO_NAME - 1] = '\0'; /* Ensure null-termination */
		}
	    } else {
		/* Handle case where macro name is not provided*/
		    return INVALID_MACRO_FORMAT_ERROR;
		}



	/* Initiliaze inside macro state */


	    insideMacro = 1; /* Boolean state flag*/
	    current_macro->macro.line_count = 0;
	    current_macro->macro.line_capacity = Initial_lines;
	    current_macro->macro.lines = malloc(Initial_lines * sizeof(char *));



	} else if(strncmp(line, "endmacr", 7) == 0){
	    insideMacro = 0;
	    /* go to next macro*/
	    current_macro->index = currentMacroIndex;

	    current_macro= current_macro->Next;
	    currentMacroIndex++;
	} else if(insideMacro){
	    /* Memory allocation check */
	    if(current_macro->macro.line_capacity<=current_macro->macro.line_count){
		size_t new_capacity = current_macro->macro.line_capacity + 10;
		char **new_lines = realloc(current_macro->macro.lines, new_capacity * sizeof(char *));

		if (new_lines == NULL) {
		    fprintf(stderr, "Error reallocating memory for new lines. Allocation size: %zu\n", new_capacity);
		    return MEMORY_ALLOCATION_ERROR;
		}

		 /*  Update the lines pointer and capacity */
		current_macro->macro.lines = new_lines;
		current_macro->macro.line_capacity = new_capacity;
	    }
	    if(current_macro->macro.lines ==NULL){
		fprintf(stderr, "Error reallocating memory for new lines. Allcoation size: %d\n",current_macro->macro.line_capacity);
		return MEMORY_ALLOCATION_ERROR;
	    }
	    /*NOTE: strdup is a malloc */

	    int current_line = current_macro->macro.line_count;
	    /* BUG: This length check causes a segfault. Fix later*/
	    /*     char * line_to_copy = strdup(line); */
	    /*     if(line_to_copy==NULL){ */
	    /*  printf("wtf\n"); */
	    /*  exit(EXIT_FAILURE); */
	    /*     } */
	    /*     printf("%s\n", line_to_copy); */
	    /*     if(strlen(line_to_copy) > 80){ */
	    /*  fprintf(stderr, "Maximum length of line (excluding the null terminator) is 80. Line #%d is of length %lu\n",current_line,strlen(line_to_copy)); */
	    /*  return LINE_TOO_LONG_ERROR; */
	    /*     } */
	    current_macro->macro.lines[current_line] = strdup(line);
	    if (current_macro->macro.lines[current_macro->macro.line_count] == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	    };
	    current_macro->macro.line_count++;
	}

    } 
	/* We will keep src_file open for the time being */
    *Macro_count = currentMacroIndex + 1;
    rewind(src_file);
    return PREPROCESSOR_EXIT_SUCESSS;
}


FILE * writeMacros(struct Macro_node *Head, int *Macro_count, FILE* src_file) {
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    FILE *temp_file = tmpfile(); /* Temporary file to store preprocessed content */
    Macro_node * Current_macro = Head;



    if (!temp_file) {
        fprintf(stderr, "Could not create temporary file for preprocessing.\n");
        return NULL;
    }

    /* Iterate through each line of the source file */
    printf("Writing Macros: \n");
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
	if(Current_macro ==NULL){
	    printf("No macros detected. Continuing....\n");
	}
	while(Current_macro!=NULL){
	    printf("Checking for macro : %s\n",Current_macro->macro.name);
	    fflush(stdout);

	    if (strstr(line, Current_macro->macro.name) != NULL) {
		printf("Call to macro %s detected\nIt has %d lines\n",Current_macro->macro.name, Current_macro->macro.line_count );
		fflush(stdout);
		macro_found = 1;

		/* Replace macro call with macro definition */
		/*  BUG: any attempt to reference the lines memory cause a segfault*/

		printf("First macro line %p\n", Current_macro->macro.lines);



		printf("First macro line %s\n", Current_macro->macro.lines[0]);
		printf("Second macro line %s\n", Current_macro->macro.lines[1]);
		printf("Third macro line %s\n", Current_macro->macro.lines[2]);
		int j;
		for (j = 0; j < Current_macro->macro.line_count; j++) {
		    fprintf(temp_file, "%s\n", Current_macro->macro.lines[j]);
		}

		break;
	    } else{
		if(Current_macro->Next!=NULL){
		    Current_macro = Current_macro->Next;
		} else{
		    break;
		}
	    }
	}
	Current_macro = Head;

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

    fclose(temp_file);
    return fully_processed_file; /* Return the preprocessed file  */
}


int isIllegalName(char * macroName){
    /* NOTE: For now we'll just return false. */
    return 0;
}



int MacroAlreadyExists(Macro_node *Head, int *Macro_count, char * macroName){
    /* NOTE: For now we'll just return false. */
    return 0;
}


/* void freeMacros(Macro_node *Head){*/
/*     Macro_node * current = Head;*/
/*     Macro_node * next;*/
/*     while(current!=NULL){*/
/* 	next = current->Next;*/
/* 	int i;*/
/* 	for(i=0;i<current->macro.line_count;i++){*/
/* 	    free(current->macro.lines[i]);*/
/* 	}*/
/**/
/* 	free(current->macro.lines);*/
/* 	free(current);*/
/* 	current = next;*/
/*     }*/
/* }*/

void freeMacros(Macro_node *Head){

}
