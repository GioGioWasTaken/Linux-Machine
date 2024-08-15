#include "../Headers/first_pass.h"
#include <string.h>

int first_pass(char * file_name){
    int exit_code, panic_mode, IC, DC;
    char instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char directive_definition[MAX_LINE_LENGTH];
    MemoryCell Data[4096];
    MemoryCell Instructions[4096];


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

	int Label_Definition  = (strchr(instruction, ':') && sscanf(instruction, "%[^:]:", label_name) == 1);

	if(Label_Definition) { 
	    if(!isValidLabel(label_name)){
		print_assemble_time_error(INVALID_LABEL_ERROR, am_file);
		exit_code=FIRST_PASS_EXIT_FAIL;
		panic_mode = 1;
	    }
	    is_label =1;
	    char * temp = strchr(instruction, '.');
	    int isDirective = temp!=NULL;
	    if(isDirective){
		/* There is a directive used in the label definition*/
		strcpy(directive_definition,temp);
		int directive_type = isValidDirective(directive_definition);
		if(directive_type!=UNKNOWN_DIRECTIVE){
		    /* NOTE: delegate all errors to the first caller. Error handeling is outside the scope of the functions' job.*/
		    int allocate_symbol_status = allocateSymbol(directive_type, &Head,&IC,&DC, am_file, directive_definition, &exit_code,Data, Instructions, label_name);
		    if(allocate_symbol_status == MEMORY_ALLOCATION_ERROR){
			return MEMORY_ALLOCATION_ERROR;
		    }
		} else{
		    print_assemble_time_error(NO_SUCH_DIRECTIVE, am_file);
		    exit_code=FIRST_PASS_EXIT_FAIL;
		    panic_mode = 1;
		    /* Code should no longer assemble*/
		}
	    } else{
		/* This is a code memory address placeholder label*/
		/* TODO: labels that point to instructions*/
	    }

	    am_file.line_number++;
	} else{
	    /* TODO: Directives without labels*/
	    printf("Line is not a label. \n");
	    char * temp = strchr(instruction, '.');
	    int isDirective = temp!=NULL;
	    if(isDirective){
		strcpy(directive_definition, temp);
		int status = isValidDirective(temp);

	    } else {
	    
	    }
	    /* TODO: Instructions without labels*/



	    am_file.line_number++;
	    continue;
	}
	/* TODO: Adjust memory addresses by IC+100 */
    }
}



/* NOTE: make it so labels are only valid if they use alphanumeric characters (white space isn't allowed)*/
int isValidDirective(char * str){
    skipWhitespace(&str);
    int directive_type = UNKNOWN_DIRECTIVE;
    if(strncmp(str, ".data",5) ==0){
	directive_type = DATA_DIRECTIVE;
    } else if(strncmp(str, ".string",7)==0){
	directive_type = STRING_DIRECTIVE;
    } else if(strncmp(str,".extern",7)==0){
	directive_type=EXTERNAL_DIRECTIVE;
    } else if(strncmp(str,".entry",6) ==0){
	directive_type=ENTRY_DIRECTIVE;
    }
    return directive_type;
}

int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* directive_definition, int * exit_code, MemoryCell Data[], MemoryCell Instructions[], char * label_name){
	printf("allocatesymbols called with : %s\n. The directive type is: %d\n",directive_definition, directive_type);
	
    /* Prepare directive */


	if(directive_type==NO_DIRECTIVE){
	    /* If this function is called with this value, these are code lines*/
	} else{
	    symbol_node * newNode = (symbol_node *) malloc(sizeof(symbol_node));
	    if(newNode==NULL){
		return MEMORY_ALLOCATION_ERROR;
	    }

	/* Set initial values */
	newNode->Next=NULL;
	newNode->symbol.is_external_line = 0;
	newNode->symbol.is_entry_line = 0;
	newNode->symbol.is_data_line = 0;
	strcpy(newNode->symbol.label_name, label_name);

	/* NOTE: the functions called  down below only allocate the data and modify DC and IC respectively.
	     * Just point the label at DC or IC respectively*/
	if(directive_type==DATA_DIRECTIVE){
	    newNode->symbol.is_data_line =1;
	    cleanCommas(directive_definition);

	    newNode->symbol.address=*DC;
	    int add_numbers_status = addNumbers(DC, Data,directive_definition,am_file);
	    (*DC)++; /* addNumbers will move DC to the last element, we are now pointing it to one memory address after the last allocated element.*/
	    if(add_numbers_status==INTEGER_OVERFLOW){
		*exit_code = FIRST_PASS_EXIT_FAIL;
		print_assemble_time_error(INTEGER_OVERFLOW, am_file);
	    } else{
		printf("DC's current value : %d\n",*DC);
	    }
	} else if(directive_type==STRING_DIRECTIVE){
	    /* TODO: code addString*/
	    newNode->symbol.is_data_line =1;
	    addString(DC, Data,directive_definition,am_file);
	}  else if(directive_type==EXTERNAL_DIRECTIVE){
		/* The .extern is still added to the symbol table, but the label referencing it has no meaning.*/
	    	/* TODO: add comma support for extern*/
		newNode->symbol.is_external_line =1;
		print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	    } else if(directive_type==ENTRY_DIRECTIVE){
		newNode->symbol.is_entry_line =1;
		print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	    }

	/* Write data to the linked list */

	if(*Head==NULL){
	    *Head = newNode;
	    return FIRST_PASS_EXIT_SUCESSS;
	} else{
	    /* Otherwise if it does exist: */

	     symbol_node* current_symbol = *Head;
	    printf("this should point to  something: %p\n", current_symbol);

	    /* We have some nodes to iterate through*/
	    while(current_symbol->Next !=NULL){
		current_symbol=current_symbol->Next;
	    }

	    /* this produces the effect that Head's last node is now newNode, without pointing Head elsewhere.*/
	    current_symbol->Next = newNode;
	    return FIRST_PASS_EXIT_SUCESSS;
	}
    }
}


/* TODO: Implement these functions: */

void freeSymbols(symbol_node ** Head){

}

int isValidLabel(char * label_definition){
    return 1;
}

int allocateDirective(int directive_type , int * DC, code_location am_file, char* directive_definition, int * exit_code, MemoryCell Data[] ){

}
