#include <stdio.h>
#include "../Headers/first_pass.h"

int first_pass(char * file_name, macroNames ** StringHead){
    int exit_code, panic_mode, IC, DC;

    /* If panic mode is set, an error has been encountered somewhere in the file and no output files shall be produced.*/
    /* The assembler will do its best to report as many errors as possible before it exists. Hence, "Panic" mode.*/
    int Label_Definition;
    char raw_instruction[MAX_LINE_LENGTH]; /* This is the line read with no modifications*/
    char label_name[MAX_LINE_LENGTH];
    /* See my comment in the label struct definition(first_pass.h) as to why the label_name size is MAX_LINE_LENGTH and not 31. */
    char directive_definition[MAX_LINE_LENGTH]; /* This is the definition of the directive, without the label*/
    FILE * proc_src;
    char * temp,*instruction_definition, *ptr; /* This is an instruction definition, without the label*/
    MemoryCell Data[4096];
    MemoryCell Instructions[4096];
    code_location am_file;
    /* Allocate space for the symbol table*/
    symbol_node * Head = NULL;



    memset(&Data, 0, sizeof(MemoryCell)* 4096);
    memset(&Instructions, 0, sizeof(MemoryCell)* 4096);


    /* Variable declerations */
    IC = IC_INITIAL; /* Start addressing from memory address 100 */
    DC = 0;
    panic_mode = 0; /* Panic mode is the variable I use to check if any errors arised during the runtime of my assembler.
    The name comes from a convention in compiler design.*/
    exit_code = FIRST_PASS_EXIT_SUCESSS;

    if(line_too_long_exists(file_name)){
	printf("Error: A line longer than the max length of %d was detected. Will continue parsing but won't prduce output files.\n",MAX_LINE_LENGTH);
	panic_mode = 1;
    } 
    /* processed src file*/
    proc_src = fopen(file_name, "r");
    if(proc_src==NULL){
	printf("am file %s doesn't exist. Can't continue. Exiting.\n",file_name);
	return NO_SUCH_FILE;
    }
    am_file.line_number = 1;
    am_file.filename=file_name;


    while(fgets(raw_instruction, sizeof(raw_instruction), proc_src) !=NULL && IC+DC+1<=IC_MAX-IC_INITIAL){
	/* + 1 because if IC is 100, since we use 0-based-indexing, it actually has allocated space for 100 words.*/
	if(strcmp(raw_instruction, "\n") ==0){
	    /* \n lines are allowed and are ignored*/
	    continue;
	}
	if(isComment(raw_instruction)){
	    continue;
	}
	ptr = raw_instruction; 
	skipWhitespace(&ptr);  /* Modify the line so it's easier to parse without errors. */
	removeTrailingNewline(raw_instruction); /* Far easier to do parsing without the newline delimiter.*/
	/* An implication of this is that when a label is preceeded by whitespaces it'll still be a valid label and those won't count as part of its definition
	 * which seems valid to me*/

	Label_Definition  = (strchr(raw_instruction, ':') && sscanf(raw_instruction, "%[^:]:", label_name) == 1);

	if(Label_Definition) { 
	    int isValidLabelStatus = isValidLabel(label_name, &Head,StringHead);
	    int isDirective;
	    if(!isValidLabelStatus){
		/* If the label is invalid, we skip it altogether and don't bother adding it to the table. */
		print_assemble_time_error(INVALID_LABEL_ERROR, am_file);
		exit_code=FIRST_PASS_EXIT_FAIL;
		panic_mode = 1;
	    } else{
		temp = strchr(raw_instruction, '.');
		isDirective = temp!=NULL;
		if(isDirective){
		    int status;
		    /* Directives with labels */
		    strcpy(directive_definition,temp);
		    status = isValidDirective(directive_definition);
		    if(status!=NO_SUCH_DIRECTIVE && status!=INVALID_DIRECTIVE){

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
		    int allocate_symbol_status;
		    /* Instructions with labels*/
		    int status = NO_DIRECTIVE;
		    instruction_definition = skip_label(&raw_instruction[0]);
		    allocate_symbol_status = allocateSymbol(status, &Head,&IC,&DC, am_file, instruction_definition,&exit_code,Data, Instructions, label_name);
		    if(allocate_symbol_status == FIRST_PASS_EXIT_FAIL || exit_code == FIRST_PASS_EXIT_FAIL){
			panic_mode = 1;
		    }
		}
	    }

	    am_file.line_number++; /* We increment the line even if the label is invalid, to continue parsing.*/
	} else{
	    char * temp = strchr(raw_instruction, '.');
	    int isDirective = temp!=NULL;
	    if(isDirective){
		int status;
		/* Directives without labels */
		strcpy(directive_definition, temp);
		status = isValidDirective(temp);
		if(status!=NO_SUCH_DIRECTIVE && status!=INVALID_DIRECTIVE){
		    if(status == DATA_DIRECTIVE || status == STRING_DIRECTIVE){
			int allocate_directive_status = allocateDirective(status , &DC, am_file,directive_definition, &exit_code, Data);

			if(allocate_directive_status == FIRST_PASS_EXIT_FAIL){
			    panic_mode = 1;
			}

		    } else if(status ==EXTERNAL_DIRECTIVE || status == ENTRY_DIRECTIVE){
			/* External and entry directives are added as symbols either way. This is the control path where they are properly defined */
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
		int Current_IC;
		/* Instructions without labels*/
		fflush(stdout);
		Current_IC = IC;
		if(parseInstruction(&Current_IC,&IC, Instructions, raw_instruction, am_file) != LEXER_EXIT_SUCESS){
		    panic_mode= 1;
		}
	    }

	    am_file.line_number++;
	    continue;
	}

    }
    /* Now that we know the size of all instructions and the size of all data, we can safely move them to the same memory image. 
     * To do that, We will relocate all Data symbols to their current address + (IC+100) (or in my case IC)*/

    if(IC+DC>IC_MAX-IC_INITIAL){
	return RUN_OUT_OF_MEMORY;
    }

    updateDataSymbols(&Head,IC);
    mergeMemoryImages(Data,Instructions, IC, DC);

    /* We will now start the second pass. All data was moved to one array, and the symbol table is all updated*/

    rewind(proc_src);



    if(panic_mode!=1){
	int second_pass_status;
	am_file.line_number= 0;
	rewind(proc_src); 
	second_pass_status = secondPass(Instructions, IC, DC, &Head, am_file, proc_src);
	if(second_pass_status!=SECOND_PASS_EXIT_SUCESS){
	    printf("an error was encountered during the second-pass stage.\n");
	    /* free the symbol table*/
	    freeSymbols(&Head);
	    return SECOND_PASS_EXIT_FAIL;
	}
    } else{
	printf("One or more errors have been detected in this file. Exiting without producing .obj .extern or .entry files.\n ");
	/* free the symbol table*/
	freeSymbols(&Head);
	return FIRST_PASS_EXIT_FAIL;
    }
    return FIRST_PASS_EXIT_SUCESSS;
}


int isValidDirective(char * str){
    int directive_type = NO_SUCH_DIRECTIVE;
    skipWhitespace(&str);
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

    symbol_node * newNode = allocateNewNode();
    char * extern_entry_name; 
    if(newNode==NULL){
	/* This should practically never happen */
	printf("Fatal error: error allocating symbol table.\nCan't continue. Exiting.\n");
	return GLOBAL_EXIT_FAILURE;
    }
    /* Set the label name, accordingly if it's an entry/external or isn't. */
    if(directive_type!=EXTERNAL_DIRECTIVE && directive_type!= ENTRY_DIRECTIVE){
	newNode->symbol.label_name = (char *)malloc(strlen(label_name) * sizeof(char) +1);
	strcpy(newNode->symbol.label_name, label_name);
	if(labelExists(label_name,directive_type,Head)){
	    printf("%s Is an invalid label. %s with type %d was already defined. \nInvalid Label: Duplicate labels are not allowed.\n", label_name, label_name, directive_type);
	    print_assemble_time_error(INVALID_LABEL_ERROR, am_file);
	    return FIRST_PASS_EXIT_FAIL;
	} 
    } else if(directive_type==EXTERNAL_DIRECTIVE || directive_type==ENTRY_DIRECTIVE){
	extern_entry_name= addExternEntry(instruction_definition,am_file);
	newNode->symbol.label_name = (char *)malloc(strlen(extern_entry_name) * sizeof(char) +1);
	strcpy(newNode->symbol.label_name,extern_entry_name );

	if(labelExists(newNode->symbol.label_name,directive_type,Head)){
	    printf("Invalid entry or external Label: Duplicate labels are not allowed.\n");
	    print_assemble_time_error(INVALID_LABEL_ERROR, am_file);
	    return FIRST_PASS_EXIT_FAIL;
	} 
    }


    if(directive_type==NO_DIRECTIVE){	/* If this function is called with this value, these are code lines*/
	int Current_IC = *IC;
	if(parseInstruction(&Current_IC,IC, Instructions, instruction_definition, am_file) != LEXER_EXIT_SUCESS){
	    *exit_fail = FIRST_PASS_EXIT_FAIL;
	}
	newNode->symbol.address=Current_IC;
    } else if(directive_type==DATA_DIRECTIVE){
	int add_numbers_status;
	newNode->symbol.is_data_line =1;
	cleanCommas(instruction_definition);
	newNode->symbol.address=*DC;
	add_numbers_status = addNumbers(DC, Data,instruction_definition,am_file);

	if(add_numbers_status!=LEXER_EXIT_SUCESS){
	    *exit_fail = FIRST_PASS_EXIT_FAIL;
	} 
    } else if(directive_type==STRING_DIRECTIVE){
	newNode->symbol.is_data_line =1;
	newNode->symbol.address=*DC;
	addString(DC, Data,instruction_definition,am_file);

    }  else if(directive_type==EXTERNAL_DIRECTIVE){
	/* The .extern is still added to the symbol table, but the label referencing it has no meaning. (the value after .extern does have meaning)*/
	if(label_name!=NULL){
	    print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	}
	newNode->symbol.is_external_line =1;

    } else if(directive_type==ENTRY_DIRECTIVE){
	if(label_name!=NULL){
	    print_assembler_warning(UNDEFINED_LABEL_WARNING, am_file);
	}
	newNode->symbol.is_entry_line =1;
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



/* I took the librety of assuming that whitespaces do not count as characters when implementing comments.
 * so, some whitespaces followed by a ; character still denote a comment line.*/
int isComment(char * instruction){
    skipWhitespace(&instruction);
    if(*instruction==';'){
	fflush(stdout);
	return TRUE;
    }
    return FALSE;
}

void freeSymbols(symbol_node ** Head){
    symbol_node * current = *Head;
    while(current!=NULL){
	symbol_node * next_node = current->Next; /* set up a next node before we deallcoate the memory*/

	/* Free any dynamically allocated members of the node*/

	if (current->symbol.label_name != NULL) {
	    free(current->symbol.label_name);  /* Free label_name if it was allocated*/
	}

	/* Free the current node itself*/
	free(current);

	/* Move to the next node*/
	current = next_node;
    }

}

/* NOTE: make it so labels are only valid if they use alphanumeric characters (white space isn't allowed)
 * They cannot have the same name as macros, registers, or opcodes 
 * A label cannot be added twice
 * Modify this function after you have made the change of passing a linked list of all macro names as an argument to first_pass*/

int isValidLabel(char * label_name, symbol_node ** Head, macroNames ** StringHead){
    if(strlen(label_name) > MAX_LABEL_LENGTH){
	printf("Invalid Label: Label name exceeds maximum allowed length (%d)\n", MAX_LABEL_LENGTH);
	return FALSE;
    }
    if(!isAlphaNumericString(label_name)){
	printf("Invalid Label: Uses non alphanumeric characters.\n");
	return FALSE;
    }
    if(MacroAlreadyExists(label_name, StringHead)){
	/* In all likelihood this is redundant. A similar check was already made in the preprocessing step, but better to be safe I suppose.*/
	printf("Invalid Label: Uses name saved for a macro\n");
	return FALSE;
    }
    if(isSavedLanguageWord(label_name)){
	printf("Invalid Label: Uses saved language words.\n");
	return FALSE;
    }
    return TRUE;
}

/* This function allocates a directive without adding it to the symbol table */
int allocateDirective(int directive_type , int * DC, code_location am_file, char* directive_definition, int * exit_fail, MemoryCell Data[] ){
    if(directive_type==DATA_DIRECTIVE){
	int add_numbers_status;
	cleanCommas(directive_definition);
	add_numbers_status = addNumbers(DC, Data,directive_definition,am_file);
	if(add_numbers_status!=LEXER_EXIT_SUCESS){
	    *exit_fail = FIRST_PASS_EXIT_FAIL;
	    print_assemble_time_error(INTEGER_OVERFLOW, am_file);
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
	    current->symbol.address+=IC;
	}
	current=current->Next;
    }
}



void mergeMemoryImages(MemoryCell Data[], MemoryCell Instructions[], int IC, int DC) {
    int i;
    for (i = 0; i < DC; i++) {
	Instructions[IC + i] = Data[i];  /* Adjusted indexing to start from IC*/
    }
}


int labelExists(char * label_query,int query_directive_type, symbol_node ** HEAD){
    symbol_node * current = *HEAD;
    while(current!=NULL){
	fflush(stdout);
	if(strcmp(current->symbol.label_name,label_query) == 0){
	    /* NOTE: An entry line decleration and a label that points to an instruction is the only two symbol combination that allows and even forces use of the same label name.*/
	    if(current->symbol.is_entry_line==0 && current->symbol.is_external_line==0 && query_directive_type==ENTRY_DIRECTIVE){
		/* The symbol attempted to be added is an entry for an already defined label, that isn't an entry or an external*/
		current= current->Next;
		continue;
	    }  else if(current->symbol.is_entry_line==1 && query_directive_type!=ENTRY_DIRECTIVE && query_directive_type!=EXTERNAL_DIRECTIVE){
		/* The symbol attempted to be added is a label for which an entry was already defined . */
		current= current->Next;
		continue;
	    }
	    /* In all other cases, including an extern being defined for a label that was defined in the current file: */
	    return TRUE;
	}
	current= current->Next;
    }
    return FALSE;
}

char *skip_label(char * str) {
    /* Skip leading spaces*/
    skipWhitespace(&str);

    /* Skip until the colon*/
    while (*str != ':' && *str != '\0') {
	str++;
    }

    /* If the colon was found, move past it*/
    if (*str == ':') {
	str++;
    }

    /* Skip any spaces after the colon*/
    skipWhitespace(&str);

    /* Return pointer to the first character of content*/
    return str;
}


symbol_node * allocateNewNode(){
    symbol_node * newNode = (symbol_node *) malloc(sizeof(symbol_node));
    if(newNode==NULL){return NULL;}

    /* Set initial values */
    newNode->Next=NULL;
    newNode->symbol.label_name=NULL;
    newNode->symbol.is_external_line = 0;
    newNode->symbol.is_entry_line = 0;
    newNode->symbol.is_data_line = 0;
    return newNode;
}



