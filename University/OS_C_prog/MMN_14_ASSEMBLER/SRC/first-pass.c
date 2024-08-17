#include "../Headers/first_pass.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int first_pass(char * file_name){
    int exit_code, panic_mode, IC, DC;
    char instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char directive_definition[MAX_LINE_LENGTH];
    MemoryCell Data[4096];
    MemoryCell Instructions[4096];
    memset(&Data, 0, sizeof(MemoryCell)* 4096);
    memset(&Instructions, 0, sizeof(MemoryCell)* 4096);


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

    while(fgets(instruction, sizeof(instruction), proc_src) !=NULL && IC+DC+1<=IC_MAX-IC_INITIAL){
	/* + 1 because if IC is 100, since we use 0-based-indexing, it actually has allocated space for 100 words.*/
	int is_label =0;
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
	    if(!isValidLabel(label_name, &Head)){
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
		int status = isValidDirective(directive_definition);
		if(status!=NO_SUCH_DIRECTIVE && status!=INVALID_DIRECTIVE){
		    /* NOTE: delegate all errors to the first caller. Error handeling is outside the scope of the functions' job.*/
		    int allocate_symbol_status = allocateSymbol(status, &Head,&IC,&DC, am_file, directive_definition,&exit_code,Data, Instructions, label_name);

		    if(allocate_symbol_status == FIRST_PASS_EXIT_FAIL || exit_code ==FIRST_PASS_EXIT_FAIL){
			panic_mode = 1;
		    }

		} else{
		    if(NO_SUCH_DIRECTIVE){
			print_assemble_time_error(NO_SUCH_DIRECTIVE, am_file);
		    } else if(INVALID_DIRECTIVE){
			print_assemble_time_error(INVALID_DIRECTIVE, am_file);
		    }
		    exit_code=FIRST_PASS_EXIT_FAIL;
		    panic_mode = 1;
		    /* Code should no longer assemble*/
		}
	    } else{
		int status = NO_DIRECTIVE;
		int allocate_symbol_status = allocateSymbol(status, &Head,&IC,&DC, am_file, directive_definition,&exit_code,Data, Instructions, label_name);
		if(allocate_symbol_status == FIRST_PASS_EXIT_FAIL || exit_code == FIRST_PASS_EXIT_FAIL){
		    panic_mode = 1;
		}
	    }


	    am_file.line_number++;
	} else{
	    printf("Line is not a label. \n");
	    char * temp = strchr(instruction, '.');
	    int isDirective = temp!=NULL;
	    if(isDirective){
		strcpy(directive_definition, temp);
		int status = isValidDirective(temp);
		if(status!=NO_SUCH_DIRECTIVE && status!=INVALID_DIRECTIVE){
		    if(status == DATA_DIRECTIVE || status == STRING_DIRECTIVE){
			int allocate_directive_status = allocateDirective(status , &DC, am_file,directive_definition, &exit_code, Data);

			if(allocate_directive_status == FIRST_PASS_EXIT_FAIL){
			    panic_mode = 1;
			}

		    } else if(status ==EXTERNAL_DIRECTIVE || status == ENTRY_DIRECTIVE){
			/* External and entry directives are added as symbols either way. This is the control path where they are properly defined */
			printf("properly defined external or entry\n");
			int allocate_symbol_status = allocateSymbol(status, &Head,&IC,&DC, am_file, directive_definition,&exit_code,Data, Instructions, NULL);

			if(allocate_symbol_status == FIRST_PASS_EXIT_FAIL){
			    panic_mode = 1;
			}
		    }
		} else{
		    if(NO_SUCH_DIRECTIVE){
			print_assemble_time_error(NO_SUCH_DIRECTIVE, am_file);
		    } else if(INVALID_DIRECTIVE){
			print_assemble_time_error(INVALID_DIRECTIVE, am_file);
		    }
		    exit_code=FIRST_PASS_EXIT_FAIL;
		    panic_mode = 1;
		}
	    } else {
		int Current_IC = IC;
		if(parseInstruction(&Current_IC,&IC, Instructions, instruction, am_file) != LEXER_EXIT_SUCESS){
		    panic_mode= 1;
		}
		printf("Current IC: %d\n",IC);
	    }

	    am_file.line_number++;
	    continue;
	}

    }
    /* Now that we know the size of all instructions and the size of all data, we can safely move them to the same memory image. 
     * To do that, We will relocate all Data symbols to their current address + (IC+100) (or in my case IC)*/

    if(IC+DC+1>IC_MAX-IC_INITIAL){
	return RUN_OUT_OF_MEMORY;
    }

    updateDataSymbols(&Head,IC);
    mergeMemoryImages(Data,Instructions, IC, DC);

    /* We will now start the second pass. All data was moved to one array, and the symbol table is all updated*/

    rewind(proc_src);
    if(!panic_mode){
	secondPass(Instructions, IC, DC, &Head, am_file, proc_src);
    } else{
	printf("One or more errors have been detected in this file. Exiting without producing .obj .extern or .entry files.\n ");
	return FIRST_PASS_EXIT_FAIL;
    }

    /* free the symbol table, as well as all other resources: */
}



int isValidDirective(char * str){
    skipWhitespace(&str);
    int directive_type = NO_SUCH_DIRECTIVE;
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

int allocateSymbol(int directive_type, symbol_node ** Head ,int * IC, int * DC, code_location am_file, char* instruction_definition, int * exit_fail,MemoryCell Data[], MemoryCell Instructions[], char * label_name){
    printf("allocatesymbols called with : %s\n.\nThe directive type is: %d\n",instruction_definition, directive_type);

    symbol_node * newNode = (symbol_node *) malloc(sizeof(symbol_node));
    if(newNode==NULL){
	/* This should practically never happen */
	print_assemble_time_error(MEMORY_ALLOCATION_ERROR, am_file);
	*exit_fail = FIRST_PASS_EXIT_FAIL;
    }

    /* Set initial values */
    newNode->Next=NULL;
    newNode->symbol.is_external_line = 0;
    newNode->symbol.is_entry_line = 0;
    newNode->symbol.is_data_line = 0;

    /* Prepare directive */
    if(directive_type==NO_DIRECTIVE){	/* If this function is called with this value, these are code lines*/
	int Current_IC = *IC;
	if(parseInstruction(&Current_IC,IC, Instructions, instruction_definition, am_file) != LEXER_EXIT_SUCESS){
	    *exit_fail = FIRST_PASS_EXIT_FAIL;
	}
	newNode->symbol.address=Current_IC;

	return FIRST_PASS_EXIT_SUCESSS;
    } else if(directive_type==DATA_DIRECTIVE){
	newNode->symbol.is_data_line =1;
	strcpy(newNode->symbol.label_name, label_name);

	cleanCommas(instruction_definition);

	/* NOTE: Should probably refactor this so this only adds the symbol to the table if it doesn't return an error status code
	     * (just for order, won't affect program integrity since we are still setting the flag)*/
	newNode->symbol.address=*DC;
	int add_numbers_status = addNumbers(DC, Data,instruction_definition,am_file);
	(*DC)++; /* addNumbers will move DC to the last element, we are now pointing it to one memory address after the last allocated element.*/

	if(add_numbers_status!=LEXER_EXIT_SUCESS){
	    *exit_fail = FIRST_PASS_EXIT_FAIL;
	} else{
	    printf("DC's current value : %d\n",*DC);
	}


    } else if(directive_type==STRING_DIRECTIVE){
	newNode->symbol.is_data_line =1;
	strcpy(newNode->symbol.label_name, label_name);
	addString(DC, Data,instruction_definition,am_file);

    }  else if(directive_type==EXTERNAL_DIRECTIVE){
	/* The .extern is still added to the symbol table, but the label referencing it has no meaning. (the value after .extern does have meaning)*/
	if(label_name!=NULL){
	    print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	}
	newNode->symbol.is_external_line =1;
	strcpy(newNode->symbol.label_name, addExternEntry(instruction_definition,am_file));
	printf("Extern name: %s\n", newNode->symbol.label_name);

    } else if(directive_type==ENTRY_DIRECTIVE){

	if(label_name!=NULL){
	    print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	}
	newNode->symbol.is_entry_line =1;
	strcpy(newNode->symbol.label_name, addExternEntry(instruction_definition,am_file));
	printf("Entry name: %s\n", newNode->symbol.label_name);
    }

    /* Write data to the linked list */

    if(*Head==NULL){
	*Head = newNode;
	if(*exit_fail!=FIRST_PASS_EXIT_FAIL){
	    return FIRST_PASS_EXIT_SUCESSS;
	} else{
	    return FIRST_PASS_EXIT_FAIL;
	}
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
	if(*exit_fail!=FIRST_PASS_EXIT_FAIL){
	    return FIRST_PASS_EXIT_SUCESSS;
	} else{
	    return FIRST_PASS_EXIT_FAIL;
	}
    }
}



/* TODO: Implement these functions: */

int isComment(char * instruction){

}

void freeSymbols(symbol_node ** Head){

}

/* NOTE: make it so labels are only valid if they use alphanumeric characters (white space isn't allowed)
 * They cannot have the same name as macros, registers, or opcodes 
 * A label cannot be added twice*/
int isValidLabel(char * label_definition, symbol_node ** Head ){
    return 1;
}

/* This function allocates a directive without adding it to the symbol table */
int allocateDirective(int directive_type , int * DC, code_location am_file, char* directive_definition, int * exit_fail, MemoryCell Data[] ){
    if(directive_type==DATA_DIRECTIVE){
	cleanCommas(directive_definition);
	int add_numbers_status = addNumbers(DC, Data,directive_definition,am_file);
	(*DC)++; /* addNumbers will move DC to the last element, we are now pointing it to one memory address after the last allocated element.*/
	if(add_numbers_status!=LEXER_EXIT_SUCESS){
	    *exit_fail = FIRST_PASS_EXIT_FAIL;
	    print_assemble_time_error(INTEGER_OVERFLOW, am_file);
	} else{
	    printf("DC's current value : %d\n",*DC);
	}
    } else if(directive_type==STRING_DIRECTIVE){
	addString(DC, Data,directive_definition,am_file);
    } 

    if(*exit_fail!=FIRST_PASS_EXIT_FAIL){
	return FIRST_PASS_EXIT_SUCESSS;
    } else{
	return FIRST_PASS_EXIT_FAIL;
    }
}



void updateDataSymbols(symbol_node ** Head, int IC){
    symbol_node *current  = *Head;
    while(current!=NULL){
	if(current->symbol.is_data_line==1){
	    current->symbol.address+=IC+1;
	    printf("Updated %s to address %d", current->symbol.label_name,current->symbol.address);
	}
	current=current->Next;
    }
}



void mergeMemoryImages(MemoryCell Data[], MemoryCell Instructions[], int IC, int DC) {
    int i;
    for (i = 0; i < DC; i++) {
        Instructions[IC + i + 1] = Data[i];  /* Adjusted indexing to start from IC*/
    }
}
