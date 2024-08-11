#include "../Headers/preprocessor.h"
#include "../Headers/globals.h"
#include "../Headers/exit.h"
#include <stdio.h>
#include <string.h>


int preprocessor(char * src){

    /* Step 0: clean whitespaces for proper parsing */

    /* Load file */
    FILE *src_file = fopen(src, "r");
    if (!src_file) {
        fprintf(stderr, "Source file %s doesn't exist.\n", src);
        return PREPROCESSOR_EXIT_FAIL;
    }
    printf("Preprocessing file\n");

    /* Clean file */
    Macro_node_t *Head = NULL;

    /* Step 1: find all macros and add them to the linked list if and only if they are all valid. */
    int macro_count = 0;
    int status_save_macros = Save_macros(&Head, &macro_count, src_file);

    switch (status_save_macros) {
        case OPEN_ENDED_MACRO_ERROR:
            printf("Error: Open-ended macro detected.\n");
            goto cleanup;
        case INVALID_MACRO_ERROR:
            printf("Error: Invalid macro.\n");
            goto cleanup;
        case INVALID_MACRO_FORMAT_ERROR:
            printf("Error: Invalid macro format.\n");
            goto cleanup;
        case DUPLICATE_MACRO_ERROR:
            printf("Error: Duplicate macro.\n"); goto cleanup;
        case MEMORY_ALLOCATION_ERROR:
            printf("Error: Memory allocation failure.\n");
            goto cleanup;
        default:
            /* No errors, continue processing */
            break;
    }

    /* Step 2 & 3: Remove all macro declarations and replace all macro calls with macro definitions */
    printf("Current Head: %p\n", Head);
    FILE *preprocessed_file = writeMacros(&Head, &macro_count, src_file);
    if (!preprocessed_file) {
        fprintf(stderr, "Failed to create preprocessed file.\n");
        goto cleanup;
    }
    create_file(preprocessed_file);

cleanup:
    freeMacros(&Head);
    fclose(src_file);
    if (preprocessed_file) {
        fclose(preprocessed_file);
	return status_save_macros;
    } else{
	return PREPROCESSOR_EXIT_FAIL;
    }
}


int Save_macros(Macro_node_t **Head,  int * Macro_count, FILE* src_file){
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    int currentMacroIndex = 0;

    printf("Saving Macros...\n");

    while(fgets(line,sizeof(line), src_file)){
        if (strncmp(line, "macr ", 5) == 0){
	    puts("Macro start encountered.\n");
	    char macroName[MAX_MACRO_NAME];

	    if(sscanf(line, "macr %s", macroName) == 1){
		if(isIllegalName(macroName)){
		    return INVALID_MACRO_ERROR;
		    /* Macro cannot be an opcode*/
		}
		if(MacroAlreadyExists(Head, Macro_count, macroName)){
		    return DUPLICATE_MACRO_ERROR;
		} 
	} else {
		/* Handle case where macro name is not provided*/
		return INVALID_MACRO_FORMAT_ERROR;
	    }
    
	    int add_macro_status = Add_macro(Head, macroName, src_file);
	    if(add_macro_status!=PREPROCESSOR_EXIT_SUCESSS){
		return add_macro_status;
	    }
	} else{
	    continue;
	}
    }
    rewind(src_file);

    return PREPROCESSOR_EXIT_SUCESSS;
}



int Add_macro(Macro_node_t **Head,  char * macr_name, FILE* src_file){
    char macr_line[MAX_LINE_LENGTH];
    Macro_node_t * newNode = (Macro_node_t *) malloc(sizeof(Macro_node_t));
    if(newNode==NULL){
	return MEMORY_ALLOCATION_ERROR;
    }

    /* Set new node data*/

    /* Macro Name */
    strncpy(newNode->macro.name, macr_name, MAX_MACRO_NAME - 1);
    newNode->macro.name[MAX_MACRO_NAME - 1] = '\0'; /* Ensure null-termination */
    printf("Macro name: %s\n", newNode->macro.name);

    newNode->macro.line_count = 0;
    newNode->macro.line_capacity = Initial_lines;
    newNode->macro.lines = malloc(Initial_lines * sizeof(char *));
    if(newNode->macro.lines == NULL){
	return MEMORY_ALLOCATION_ERROR;
    }
    /* src_file is currently winded to the line after macr macrname */
    int lines_until_end = 0;	
    while(fgets(macr_line,sizeof(macr_line), src_file)){
	if(strncmp(macr_line, "endmacr\n", 8) == 0){
	    printf("Macro length in lines: %d\n", lines_until_end);
	    puts("macro end encountered\n");
	    break;
	}
	int i = newNode->macro.line_count;
	if(i==newNode->macro.line_capacity){
	    /* Allocated space for 40 more lines if needed*/
	    newNode->macro.lines= realloc(newNode->macro.lines, i + 40);
	    if(newNode->macro.lines == NULL){
		return MEMORY_ALLOCATION_ERROR;
	    }
	}
	newNode->macro.lines[i] = malloc(sizeof(char) * MAX_LINE_LENGTH);
	if(newNode->macro.lines[i]==NULL){
	    return MEMORY_ALLOCATION_ERROR;
	}
	strcpy(newNode->macro.lines[i], macr_line);
	printf("macro line: %s\n",newNode->macro.lines[i]);
	newNode->macro.line_count++;
	lines_until_end++;
    }
    if(strcmp("endmacr\n",macr_line) != 0){
	printf("expected endmacr but got '%s' instead.\n",macr_line);
	return OPEN_ENDED_MACRO_ERROR;
    }


    /* Determine position of new node based on head */

    /* If head does not exist: */
    if(*Head==NULL){
	printf("Head should now point to: %p\n", newNode);
	*Head = newNode;
	return PREPROCESSOR_EXIT_SUCESSS;
    } else{
	printf("Head found at address %p\n",Head);

	/* Otherwise if it does exist: */

	Macro_node_t * current_macro = *Head;

	/* We have some nodes to iterate through*/
	while(current_macro->Next !=NULL){
	    current_macro=current_macro->Next;
	}

	/* this produces the effect that Head's last node is now newNode, without modifying Head.*/
	printf("The last node that was added has an address: %p\n", newNode);
	current_macro->Next = newNode;
	return PREPROCESSOR_EXIT_SUCESSS;
    }
}



FILE * writeMacros(Macro_node_t **Head, int *Macro_count, FILE* src_file) {
    char line[MAX_LINE_LENGTH];
    int insideMacro = 0;
    FILE *temp_file = tmpfile(); /* Temporary file to store preprocessed content */
    Macro_node_t * Current_macro = *Head;



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
            insideMacro = 1;
	    continue;
        }

        /* Check if the line contains the end of a macro definition */
        if (insideMacro && strncmp(line, "endmacr", 7) == 0) {
            insideMacro = 0;
            continue; /* Skip this line as well */
        }

        /* If inside a macro definition, skip the line */
        if (insideMacro) {
            continue;
        }

        /* Check if the line contains a macro call and replace it */
	if(Current_macro ==NULL){
	    printf("No macros detected. Continuing....\n");
	    continue;
	}
	while(Current_macro!=NULL){
	    printf("Checking for macro : %s\n",Current_macro->macro.name);

	    if (strstr(line, Current_macro->macro.name) != NULL) {
		printf("Call to macro %s detected\nIt has %d lines\n",Current_macro->macro.name, Current_macro->macro.line_count );
		macro_found = 1;


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
	Current_macro = *Head;

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




int MacroAlreadyExists(Macro_node_t **Head, int *Macro_count, char * macroName){
    return 0;
}


void freeMacros(Macro_node_t **Head){
    Macro_node_t * current = *Head;
    Macro_node_t * next;
    while(current!=NULL){
	int i;
	next = current->Next;
	for(i=0;i<current->macro.line_count;i++){
	    free(current->macro.lines[i]);
	}
	free(current->macro.lines);
	free(current);
	current = next;
    }
}


