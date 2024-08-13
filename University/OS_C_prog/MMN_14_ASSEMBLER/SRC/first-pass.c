#include "../Headers/exit.h"
#include "../Headers/preprocessor.h"
#include "../Headers/utils.h"
#include "../Headers/globals.h"
#include "../Headers/first_pass.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int first_pass(char * file_name){
    int exit_code, panic_mode, IC, DC;
    char instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char directive_definition[MAX_LINE_LENGTH];
    /* NOTE:  Declare the memory image structs here. Each with size 4096.*/
    /* NOTE: make sure where to start allocating the bytes in the instruction struct*/

    /* Variable declerations */
    IC = IC_INITIAL; /* Start addressing from memory address 100 */
    DC = 0;
    panic_mode = 0;
    exit_code = FIRST_PASS_EXIT_SUCESSS;

    if(line_too_long_exists(file_name)){
	/* If panic mode is set, an error has been encountered somewhere in the file and no output files shall be produced.*/
	/* The assembler will do its best to report as many errors as possible before it exists. Hence, "Panic" mode.*/
	panic_mode = 1;
    }

    /* processed src file*/
    FILE * proc_src = fopen(file_name, "r");
    if(proc_src==NULL){
	printf("am file %s doesn't exist. Can't continue. Exiting.\n",file_name);
	return NO_SUCH_FILE;
    }
    code_location am_file = {
	.line_number = 1,
	.filename=file_name,
    };

    /* Allocate space for the symbol table*/
    symbol_node * Head = NULL;

    while(fgets(instruction, sizeof(instruction), proc_src) !=NULL && IC+DC<=IC_MAX-IC_INITIAL){
	int is_label =0;
	if(strcmp(instruction, "\n") ==0){
	    /* \n lines are allowed and are ignored*/
	    continue;
	}
	/* Modify the line so it's easier to parse without errors. */
	char* ptr = instruction; 
	skipWhitespace(&ptr);
	removeTrailingNewline(instruction); /* Far easier to do parsing without the newline delimiter.*/

	if (strchr(instruction, ':') && sscanf(instruction, "%[^:]:", label_name) == 1) {
	    is_label =1;
	    char * temp = strchr(instruction, '.');
	    if(temp!=NULL){
		/* There is a directive used in the label definition*/
		strcpy(directive_definition,temp);
		int directive_type = isValidDirective(directive_definition);
		if(directive_type!=UNKNOWN_DIRECTIVE){
		    int allocate_symbol_status = allocateSymbol(directive_type, &Head,&IC,&DC, am_file, directive_definition);
		    if(allocate_symbol_status == MEMORY_ALLOCATION_ERROR){
			return MEMORY_ALLOCATION_ERROR;
		    }
		} else{
		    print_assemble_time_error(INVALID_DIRECTIVE_ERROR, am_file);
		    exit_code=FIRST_PASS_EXIT_FAIL;
		    panic_mode = 1;
		    /* Code should no longer assemble*/
		}
	    } else{
		/* This is a code memory address placeholder label*/

	    }

	    am_file.line_number++;
	} else{
	    printf("Line is not a label. Continue...\n");
	    am_file.line_number++;
	    continue;
	}
    }
}



/* NOTE: make it so labels are only valid if they use alphanumeric characters (white space isn't allowed)*/
int isValidDirective(char * str){
    skipWhitespace(&str);
    int directive_type = UNKNOWN_DIRECTIVE;
    if(strncmp(str, ".data",5) ==0){
	directive_type = DATA_DIRECTIVE;
    } else if(strncmp(str, ".string",7)==0){
	/* Strings are just a specific type of data. Creating a seperate directive type for them is redundnt.*/
	directive_type = DATA_DIRECTIVE;
    } else if(strncmp(str,".extern",7)==0){
	directive_type=EXTERNAL_DIRECTIVE;
    } else if(strncmp(str,".entry",6) ==0){
	directive_type=ENTRY_DIRECTIVE;
    }
    return directive_type;
}

/* NOTE: implement the data and instruction memory images as an array of cells, 
 * where each cell is struct of 2 chars or unit16 */
/* NOTE: break addData to addNumbers*/
int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* directive_definition){
	printf("allocatesymbols called with : %s\n. The directive type is: %d\n",directive_definition, directive_type);
	if(directive_type==NO_DIRECTIVE){
	    /* If this function is called with this value, these are code lines*/
	} else{
	    symbol_node * newNode = (symbol_node *) malloc(sizeof(symbol_node));
	    if(newNode==NULL){
		return MEMORY_ALLOCATION_ERROR;
	    }

	    /* Set initial values */
	    newNode->symbol.is_external_line = 0;
	    newNode->symbol.is_entry_line = 0;
	    newNode->symbol.is_data_line = 0;

	    if(directive_type==DATA_DIRECTIVE){
		newNode->symbol.is_data_line =1;
		cleanCommas(&directive_definition);
		addData(DC, data,directive_definition);
	    }  else if(directive_type==EXTERNAL_DIRECTIVE){
		/* The .extern is still added to the symbol table, but the label referencing it has no meaning.*/
		newNode->symbol.is_external_line =1;
		print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	    } else if(directive_type==ENTRY_DIRECTIVE){
		newNode->symbol.is_entry_line =1;
		print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	    }
	if(*Head==NULL){
	    *Head = newNode;
	    return FIRST_PASS_EXIT_SUCESSS;
	} else{

	    /* Otherwise if it does exist: */

	     symbol_node* current_symbol = *Head;

	    /* We have some nodes to iterate through*/
	    while(current_symbol->Next !=NULL){
		current_symbol=current_symbol->Next;
	    }

	    /* this produces the effect that Head's last node is now newNode, without modifying Head.*/
	    current_symbol->Next = newNode;
	    return PREPROCESSOR_EXIT_SUCESSS;
	}
    }
}

