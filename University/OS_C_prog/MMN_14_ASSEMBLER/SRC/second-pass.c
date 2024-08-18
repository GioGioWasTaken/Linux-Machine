#include "../Headers/second_pass.h"
#include <time.h>
int secondPass(MemoryCell Code[], int IC, int DC, symbol_node ** Head, code_location am_file, FILE * proc_src ){
    char instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char directive_definition[MAX_LINE_LENGTH];
    char * directive_name;
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
		} else{
		    int entry_status = setEntryAddress(directive_name, Head);
		    if(entry_status== NO_SUCH_LABEL){
			print_assemble_time_error(NO_SUCH_LABEL, am_file);
			panic_mode = 1;
		    }
		}
	    } else{
		/* TODO: build the rest of the words of the instruction*/
	    }

	    /* TODO: Create the output files*/ 


	}
    }
}


/* NOTE: first make sure directive_name is properly extracted, then iterate over head,
 * check for the case where all of the things are 0 which means it's just an instruction with a label,
 * extract the address, iterate again, and set up the entry address properly*/
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
