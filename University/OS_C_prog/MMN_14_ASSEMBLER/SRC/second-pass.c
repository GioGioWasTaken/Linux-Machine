#include "../Headers/second_pass.h"
#include <stdio.h>
#include <time.h>
int secondPass(MemoryCell Code[], int IC, int DC, symbol_node ** Head, code_location am_file, FILE * proc_src ){
    char instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char directive_definition[MAX_LINE_LENGTH];
    char * directive_name;
    char file_no_extension[256];  
    char entry_output_name[260];  
    char extern_output_name[260];
    char object_output_name[260];
    int panic_mode = 0;

    while(fgets(instruction, sizeof(instruction), proc_src) !=NULL){
	if(strcmp(instruction, "\n") ==0){
	    /* \n lines are allowed and are ignored*/
	    continue;
	}
	if(isComment(instruction)){
	    continue;
	}

	char* ptr = instruction; 
	skipWhitespace(&ptr);  /* Modify the line so it's easier to parse without errors. */
	removeTrailingNewline(instruction); /* Far easier to do parsing without the newline delimiter.*/

	int Label_Definition  = (strchr(instruction, ':') && sscanf(instruction, "%[^:]:", label_name) == 1);

	if(Label_Definition) { 
	    char * temp = strchr(instruction, '.');
	    int isDirective = temp!=NULL;
	    if(isDirective){
		/* There is a directive used in the label definition*/
		strcpy(directive_definition,temp);
		int status = isValidDirective(directive_definition);
		if(status!=ENTRY_DIRECTIVE){
		    continue;
		    /* We can do an else  block here immediately because if it was of any other undefined directive type,
		     * it would have been discovered in the first pass.*/
		} else{
		    int entry_status = setEntryAddress(directive_name, Head);
		    if(entry_status== NO_SUCH_LABEL){
			print_assemble_time_error(NO_SUCH_LABEL, am_file);
			panic_mode = 1;
		    }
		}
	    } else{
		/* TODO: build the rest of the words of the instruction*/

	    /* while i'm compelting the rest of words of the instruction, if I find that the label referenced is external (i will iterate through the symbol table and look for an equivalent label name to the one referenced in code ) I should also at that moment mark the external label with the address it was called from. */
	    /* this address will be placed in the address field, even though it's not the address where it's defined. */
	    /* We will modify the function behaviour, such that if it finds that the currently referenced label is external, the address it writes is special.*/
	    }






	}
    }
    /* TODO: Create the output files*/ 

    /* Copy filename and remove the ".am" extension*/
    strncpy(file_no_extension, am_file.filename, strlen(am_file.filename) - 3); 
    file_no_extension[strlen(am_file.filename) - 3] = '\0';  

    /* Create new file names with different extensions*/
    snprintf(entry_output_name, sizeof(entry_output_name), "%s.ent", file_no_extension);
    snprintf(extern_output_name, sizeof(extern_output_name), "%s.ext", file_no_extension);
    snprintf(object_output_name, sizeof(object_output_name), "%s.ob", file_no_extension);


    createEntryOutput(Head, entry_output_name);
}

/* TODO: add comments before function and function prototypes.*/

int setEntryAddress(char * directive_name, symbol_node ** Head){
    symbol_node * Current = *Head;
    while(Current!=NULL){
	if(Current->symbol.is_entry_line == 1){
	    symbol_node * Current_instruction= *Head;
	    while(strcmp(Current_instruction->symbol.label_name,Current->symbol.label_name)!=0){
		Current_instruction= Current_instruction->Next;
	    } 
	    if(strcmp(Current_instruction->symbol.label_name,Current->symbol.label_name)==0){
		Current->symbol.address = Current_instruction->symbol.address;
		printf("Found matching label for an entry call. The address %d was allocated.\n ",Current_instruction->symbol.address );
	    } else{
		return NO_SUCH_LABEL;
	    }
	}
	Current= Current->Next;
    }
    return SECOND_PASS_EXIT_SUCESS;

}

void createEntryOutput(symbol_node **Head, char *entry_name) {
    symbol_node *current = *Head;
    FILE *entryOUT = NULL;
    int file_created = 0;  /* Flag to check if the file has been created*/

    while (current != NULL) {
        if (current->symbol.is_entry_line == 1) {
	    printf("entry line\n");
            if (!file_created) {
		printf("creating file\n");
                /* Create the entry output file only once */
                entryOUT = fopen(entry_name, "w");
                if (entryOUT == NULL) {
                    perror("Error opening entry output file");
                    return;
                }
                file_created = 1;  /* Set the flag to avoid creating the file again*/
            }

            /* Write entry to file */
            writeEntry(entryOUT, current->symbol.label_name, current->symbol.address);
        }
	printf("not entry line\n");
        current = current->Next;  /* Move to the next node in the list*/
    }

    /* Close the file if it was created */
    if (file_created) {
	create_file(entryOUT);
        fclose(entryOUT);
    }
}

void writeEntry(FILE *entryOUT, char *entry_name, int addr) {
    /* Check if the file stream is valid*/
    printf("Writing to file\n");
    if (entryOUT == NULL) {
        perror("Error opening entry file\n");
        return;
    }

    /* Write the entry in the format: entry_name  addr*/
    fprintf(entryOUT, "%-20s %04d\n", entry_name, addr);
}
