/* TODO: add comments before function and function prototypes.*/
#include "../Headers/second_pass.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


#define is_not_instruction_label (Current_instruction->symbol.is_entry_line == 1 || \
                                  Current_instruction->symbol.is_data_line == 1 || \
                                  Current_instruction->symbol.is_external_line == 1)

int secondPass(MemoryCell Code[], int IC, int DC, symbol_node ** Head, code_location am_file, FILE * proc_src ){
    char raw_instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char * instruction;
    int PC = IC_INITIAL;
    char directive_definition[MAX_LINE_LENGTH];
    char * directive_name;
    char file_no_extension[256];  
    char entry_output_name[260];  
    char extern_output_name[260];
    char object_output_name[260];
    int panic_mode = 0;

    while(fgets(raw_instruction, sizeof(raw_instruction), proc_src) !=NULL){
	if(strcmp(raw_instruction, "\n") ==0){
	    /* \n lines are allowed and are ignored*/
	    continue;
	}
	if(isComment(raw_instruction)){
	    continue;
	}

	char* ptr = raw_instruction; 
	skipWhitespace(&ptr);  /* Modify the line so it's easier to parse without errors. */
	removeTrailingNewline(raw_instruction); /* Far easier to do parsing without the newline delimiter.*/

	int Label_Definition  = (strchr(raw_instruction, ':') && sscanf(raw_instruction, "%[^:]:", label_name) == 1);

	if(Label_Definition) { 
	    instruction = skip_label(&raw_instruction[0]);
	} else{
	    instruction = &raw_instruction[0];
	}
	    char * temp = strchr(instruction, '.');
	    int isDirective = temp!=NULL;
	if(isDirective){
	    strcpy(directive_definition,temp);
	    int status = isValidDirective(directive_definition);
	    if(status!=ENTRY_DIRECTIVE){
		continue;
		/* We can do an else  block here immediately because if it was of any other undefined directive type,
		     * it would have been discovered in the first pass.*/
	    } else{
		printf("entry detected! Looking for its address....\n");
		int entry_status = setEntryAddress(directive_name, Head);
		if(entry_status== NO_SUCH_LABEL){
		    print_assemble_time_error(NO_SUCH_LABEL, am_file);
		    panic_mode = 1;
		}
	    }
	} else{
	    printf("Current instruction: %s\n", raw_instruction);
	    parseRemainingInstruction(&PC, Code, raw_instruction, am_file,Head);
	    fflush(stdout);

	    /* while i'm completing the rest of words of the instruction, if I find that the label referenced is external, I should also at that moment mark the external label with the address it was called from. */
	    /* We will modify the function behaviour, such that if it finds that the currently referenced label is external, the address it writes is special.*/
	}
	am_file.line_number++;
	} 
    /* TODO: Create the output files
     * External : setting the address of the external temporarily to where it was called from*/ 

    /* Copy filename and remove the ".am" extension*/
    strncpy(file_no_extension, am_file.filename, strlen(am_file.filename) - 3); 
    file_no_extension[strlen(am_file.filename) - 3] = '\0';  

    /* Create new file names with different extensions*/
    snprintf(entry_output_name, sizeof(entry_output_name), "%s.ent", file_no_extension);
    snprintf(extern_output_name, sizeof(extern_output_name), "%s.ext", file_no_extension);
    snprintf(object_output_name, sizeof(object_output_name), "%s.ob", file_no_extension);


    if(panic_mode!=1){
	createEntryOutput(Head, entry_output_name);
	deleteExternOutput(Head,extern_output_name);
    }
}


int setEntryAddress(char * directive_name, symbol_node ** Head){
    symbol_node * Current = *Head;

    while (Current != NULL) {
        if (Current->symbol.is_entry_line == 1) {
            symbol_node * Current_instruction = *Head;
            int label_found = 0;

            while (Current_instruction != NULL) {
                if (is_not_instruction_label) {
                    Current_instruction = Current_instruction->Next;
                } else if (strcmp(Current_instruction->symbol.label_name, Current->symbol.label_name) == 0) {
                    /* Found matching label*/
                    Current->symbol.address = Current_instruction->symbol.address;
                    printf("Found matching label for entry %s. The address %d was allocated.\n", Current->symbol.label_name, Current_instruction->symbol.address);
                    label_found = 1;
                    break;
                } else {
                    Current_instruction = Current_instruction->Next;
                }
            }

            if (!label_found) {
                return NO_SUCH_LABEL;
            }
        }
        Current = Current->Next;
    }
    return SECOND_PASS_EXIT_SUCESS;
}

void createEntryOutput(symbol_node **Head, char *entry_name) {
    symbol_node *current = *Head;
    FILE *entryOUT = NULL;
    int file_created = 0;  /* Flag to check if the file has been created*/

    while (current != NULL) {
        if (current->symbol.is_entry_line == 1) {
            if (!file_created) {
		printf("Creating .ent file...\n");
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
    if (entryOUT == NULL) {
        perror("Error opening entry file\n");
        return;
    }

    /* Write the entry in the format: entry_name  addr*/
    fprintf(entryOUT, "%-5s %04d\n", entry_name, addr);
}

void deleteExternOutput(symbol_node **Head, char *output_name){
    /* if file doesn't exist return sucesss*/
    /* else delete it */
}
