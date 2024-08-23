#include <stdio.h>
#include "../Headers/lexer.h"
#include <stdlib.h>
#include <string.h>
/* NOTE:  Might be broken if the addsymbols function doesn't expect the instruction to be without the label make sure lalter*/

const char * Registers[8] = {
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
};

const instruction_t OPCODES[16] = {
    {"mov",  2, 0},
    {"cmp",  2, 1},
    {"add",  2, 2},
    {"sub",  2, 3},
    {"lea",  2, 4},
    {"clr",  1, 5},
    {"not",  1, 6},
    {"inc",  1, 7},
    {"dec",  1, 8},
    {"jmp",  1, 9},
    {"bne",  1, 10},
    {"red",  1, 11},
    {"prn",  1, 12},
    {"jsr",  1, 13},
    {"rts",  0, 14},
    {"stop", 0, 15}
};


int determine_opcode(char *str, const instruction_t OPCODES[]) {
    char *mnemonic;
    int opcode, i;
    char *instr = str;

    skipWhitespace(&instr);  /* Skip leading whitespace */

    /* Extract the mnemonic using strtok*/
    mnemonic = strtok(instr, " ");

    /* Iterate through OPCODES to find a match */
    for (i = 0; i < 16; i++) {
	if (mnemonic && strcmp(mnemonic, OPCODES[i].mnemonic) == 0) {
	    char *end;
	    opcode = OPCODES[i].opcode;

	    /* Restore the delimiter by finding the end of the mnemonic token*/
	    end = mnemonic + strlen(mnemonic);
	    *end = ' ';  /* Set the last character to the delimiter, so the state is preserved*/

	    return opcode;  /* Return the opcode for the matched mnemonic */
	}
    }

    printf("Faulty Opcode mnemonic detected: '%s'\n", mnemonic);
    return NO_SUCH_OPCODE;  /* Example error code for unknown mnemonic */
}

int parseInstruction(int *Current_IC,int *IC,MemoryCell Instructions[], char * instruction_definition , code_location am_file){
    char *Token, *inst;
    int opcode, arg_count, args_provided, ARE, first_reg_found, second_reg_found;
    int args_addressing[2] = {-100, -100};
    args_provided = 0;
    first_reg_found = 0;
    second_reg_found = 0;
    inst=instruction_definition;

    /* Determine opcode*/
    opcode = determine_opcode(inst, OPCODES);
    if(opcode==NO_SUCH_OPCODE){
	print_assemble_time_error(NO_SUCH_OPCODE, am_file);
	return NO_SUCH_OPCODE;
    }
    arg_count = OPCODES[opcode].operand_count;


    /* Parse arguments */
    cleanCommas(inst);
    Token = strtok(inst,",");
    if(arg_count!=0){
	while(Token !=NULL){
	    if(args_provided+1 > arg_count){
		print_assemble_time_error(TOO_MANY_ARGUMENTS, am_file);
		return TOO_MANY_ARGUMENTS;
	    }

	    /* Token is now pointing at the first char of the first argument*/
	    switch (*Token) {
		case '*':
		    /* Since I am using the same function for the other case as well,
		    the function should assume the same state. I will pass the first char of the register in both Tokenances*/
		    if(isRegister(Token+1, Registers)){
			/* This is to make sure we don't accidently allocate 2 cells instead of 1.*/
			if(args_provided==0){
			    first_reg_found =1;
			} else if(first_reg_found){
			    second_reg_found =1;
			}
			args_addressing[args_provided]=INDIRECT_REGISTER_ADDRESSING;
		    } else{
			print_assemble_time_error(NO_SUCH_REGISTER, am_file);
			return NO_SUCH_REGISTER;
		    }
		    break;
		case '#':
		    args_addressing[args_provided]=ABSOLUTE_ADDRESSING;
		    break;
		default:
		    if(isRegister(Token, Registers)){
			args_addressing[args_provided]=DIRECT_REGISTER_ADDRESSING;
			if(args_provided==0){
			    first_reg_found =1;
			} else if(first_reg_found){
			    second_reg_found =1;
			}
		    } else{
			args_addressing[args_provided]=DIRECT_ADDRESSING;
		    }
		    break;
	    }
	    args_provided++;
	    Token = strtok(NULL, ",");
	}
    } 


    /* Add the instruction to memory */
    ARE = 2; /*  This method will only be used for the first word of the instruction, so it's always going to be 2*/
    if(arg_count==1){
	/* If there are two arguments, the first one is source and the second is dest.*/
	/* If there is one argument, its dest.*/
	args_addressing[1] = args_addressing[0];
	args_addressing[0] = -100;
    }
    if(second_reg_found){
	arg_count = 1;
	*Current_IC=addInstruction(IC, Instructions,opcode, arg_count, args_addressing, ARE);
    } else{
	*Current_IC=addInstruction(IC, Instructions,opcode, arg_count, args_addressing, ARE);
    }
    return LEXER_EXIT_SUCESS;
}


char * removeDirectiveType(char * directive_definition,code_location am_file){
    char * Token;
    char * res;
    Token = strtok(directive_definition, " ");
    if(Token!=NULL){
	res = directive_definition+strlen(Token);
	skipWhitespace(&res);
	/* Move the pointer after the directive definition including the spaces */
    } else {
	print_assemble_time_error(INVALID_DIRECTIVE_DEFINITION_NO_SPACE, am_file);
	return NULL;
    }
    return res;
}


int addNumbers(int *DC,MemoryCell Data[], char * directive_definition , code_location am_file){
    char * Token;
    int status_add;
    if (*directive_definition=='\0'){
	/* invalid .data definition
	* .data     (without any arguments) isn't valid.*/
	print_assemble_time_error(INVALID_DIRECTIVE_DEFINITION_NO_ARGS,  am_file);
	return INVALID_DIRECTIVE_DEFINITION_NO_ARGS;
    } else if(directive_definition==NULL){
	/* .data4,3,  is invalid */
	print_assemble_time_error(INVALID_DIRECTIVE_DEFINITION_NO_SPACE, am_file);
	return INVALID_DIRECTIVE_DEFINITION_NO_SPACE;
    }

    Token = strtok(directive_definition, ",");
    while(Token != NULL){
	status_add = addNumber(DC,Data,Token);
	if(status_add==INTEGER_OVERFLOW){
	    print_assemble_time_error(INTEGER_OVERFLOW ,am_file);

	}
	Token = strtok(NULL, ",");
    }
    return LEXER_EXIT_SUCESS;

}

int addString(int * DC,MemoryCell Data[], char * directive_definition, code_location am_file){
    /* NOTE: I heard some other students saying that a string with a " character inside it is valid,
     * but that seemed quite undefined to me so I decided to not include it in this implementation 
     * I hope that wasn't the actual thing we were supposed to do as it wasn't directly included in the instructions :0 */
    char *Token;
    int i;

    /* We do this to clear leading spaces. E.g. "    .data"*/
    char *string_definition = directive_definition;
    skipWhitespace(&string_definition);

    /* Extract the directive (e.g., .data) and skip it */
    Token = strtok(string_definition, " ");
    Token = strtok(NULL, "\"");  /* this depends on your text editor, because there are seemingly multiple types of opening quotes...*/
    if(Token==NULL){
	print_assemble_time_error(UNCLOSED_STRING_ERROR, am_file);
	return UNCLOSED_STRING_ERROR;
    }

    i = 0;
    /* We also want to pass the null byte into the function. So we'll use <= */
    while(i<=strlen(Token)){
	addChar(DC,Data,Token[i]);
	i++;
    }
    return LEXER_EXIT_SUCESS;
}


/* The cleanCommas function deletes every unneeded space of an instrction while modifying it in place. After using it, the state of the string passed, 
 * would be only the operands of the instrction (if it has any), with proper commas (no unneeded whitespaces)*/
void cleanCommas(char *instruction) {
    char buffer[MAX_LINE_LENGTH] = "";   /* Temporary buffer for the cleaned string */
    char *result = buffer;
    char *Token;

    /* We do this to clear leading spaces. E.g. "    .data"*/
    char *instr = instruction;
    skipWhitespace(&instr);

    /* Extract the first part of the instruction (e.g. .data, mov, etc) and skip it */
    Token = strtok(instr, " ");
    skipWhitespace(&Token);
    Token = strtok(NULL, ",");   

    /* Rebuild the string with commas cleaned */
    while (Token != NULL) {
	/* Add the token to the result buffer */
	while (*Token) {
	    if (!isspace((unsigned char)*Token)) {
		*result++ = *Token;   /* Copy the character to the result */
	    }
	    Token++;
	}
	Token = strtok(NULL, ",");   /* Get the next token, splitting by commas */

	/* If there's another token, add a comma without spaces */
	if (Token != NULL) {
	    *result++ = ',';
	}
    }

    /* Null-terminate the result string */
    *result = '\0';

    /* Copy the cleaned string back to the original instruction */
    strcpy(instruction, buffer);
}


char * addExternEntry(char * directive_definition , code_location am_file){
    char * Token;
    char * instr = directive_definition;
    /* We do this to clear leading spaces. E.g. "    .entry func"*/
    skipWhitespace(&instr);
    Token = strtok(instr," ");
    Token = strtok(NULL, "\n");
    return Token;
}

int isRegister(char * instruction, const char * Registers[]){
    char Register[2];
    int i;
    strncpy(Register, instruction, 2);
    for(i = 0; i<8; i++){
	if(strcmp(Register, Registers[i]) == 0){
	    return TRUE;
	}
    }
    return FALSE;
}



/* This function returns TRUE if the parameter word_to_check
 * is a register name or opcode mnemonic, otherwise it returns FALSE. */
int isSavedLanguageWord(char * word_to_check) {
    /* Check if the word matches any register name*/
    int i;
    for (i = 0; i < 8; i++) {
	if (strcmp(word_to_check, Registers[i]) == 0) {
	    return TRUE;
	}
    }

    /* Check if the word matches any opcode mnemonic*/
    for (i = 0; i < 16; i++) {
	if (strcmp(word_to_check, OPCODES[i].mnemonic) == 0) { return TRUE;
	}
    }

    return FALSE;  /* Return FALSE if no match is found*/
}



/* NOTE: I refer to the current IC as PC here, since we are essentially going instruction by instruction now. */
int parseRemainingInstruction(int * PC,  MemoryCell Instructions[], char * instruction_definition , code_location am_file, symbol_node ** Head, char * extern_name, int * externOpened){
    int addressing_methods[] = {NO_OPERAND_ADDRESSING, NO_OPERAND_ADDRESSING}; 
    char *first_operand,*second_operand;
    /* If this value is read at the end, it means that either the source or dest operand don't exist. */
    readAddressingMethods(addressing_methods, Instructions, *PC);
    cleanCommas(instruction_definition);
    if(addressing_methods[0] == NO_OPERAND_ADDRESSING && addressing_methods[1]==NO_OPERAND_ADDRESSING){
	/* No operands*/
	(*PC)++;
	return LEXER_EXIT_SUCESS;
    } else if(addressing_methods[1] != NO_OPERAND_ADDRESSING && addressing_methods[0]==NO_OPERAND_ADDRESSING){
	/* One operand*/
	int dest_addressing = addressing_methods[1];
	int status = buildOperand(dest_addressing, extern_name, Instructions, am_file, Head, externOpened, instruction_definition, PC, 1,0);
	if(status!=LEXER_EXIT_SUCESS){
	    return LEXER_EXIT_FAIL;
	}
	(*PC)+=2;
    } else if(addressing_methods[0] != NO_OPERAND_ADDRESSING && addressing_methods[1]!=NO_OPERAND_ADDRESSING){
	/* Two operands */
	int source_addressing = addressing_methods[0];
	int destination_addressing = addressing_methods[1];

	if (((source_addressing == destination_addressing) && (source_addressing == 2)) ||
	    ((source_addressing == destination_addressing) && (source_addressing == 3)) ||
	    (source_addressing + destination_addressing == 5)) {
	    /* If they are both 2, both 3, or either one of them is 2 with the other being 3: */
	    /* They will share a word, and the instruction will be two words long. (The unused space that was allocated in advance, will be set 0)*/
	    int source_register_num, dest_register_num;
	    if(*instruction_definition=='*'){
		instruction_definition++;
	    }
	    instruction_definition+=1;
	    source_register_num = (*instruction_definition) -'0';
	    instruction_definition+=3;
	    dest_register_num = (*instruction_definition) -'0';

	    writeRegisterNumber(&Instructions[*PC+1], source_register_num, dest_register_num);
	    (*PC)+=2;
	} else{
	    int status;
	    first_operand = strtok(instruction_definition, ",");
	    second_operand = strtok(NULL, "\n");

	    status = buildOperand(source_addressing, extern_name, Instructions, am_file, Head, externOpened, first_operand, PC, 0, 0);
	    if(status!=LEXER_EXIT_SUCESS){
		return LEXER_EXIT_FAIL;
	    }
	    (*PC)+=1;
	    status = buildOperand(destination_addressing, extern_name, Instructions, am_file, Head, externOpened, second_operand, PC, 0, 1);
	    if(status!=LEXER_EXIT_SUCESS){
		return LEXER_EXIT_FAIL;
	    }
	    (*PC)+=2;
	}
    }
    return LEXER_EXIT_SUCESS;
}

int buildOperand(int operand_addressing , char * extern_name,  MemoryCell Instructions[], code_location am_file, symbol_node ** Head, int * externOpened, char * instruction_definition, int * PC, int is_only_operand, int is_second_operand){
    int num_read;
    char * label_name;
    int write_status, label_address, register_num;
    switch (operand_addressing) {
	case ABSOLUTE_ADDRESSING:
	    num_read = atoi(instruction_definition+1);
	    write_status = writeAbsoluteValue(&Instructions[*PC+1], am_file, num_read); /* PC +1 Since PC points to the first word. */
	    if(write_status==INTEGER_OVERFLOW){
		printf("Error when using absolute addressed value\n");
		print_assemble_time_error(INTEGER_OVERFLOW ,am_file);
		return INTEGER_OVERFLOW;
	    }
	    break;
	case DIRECT_ADDRESSING:
	    label_name = instruction_definition;
	    label_address = getLabelAddress(label_name, Head);

	    if(label_address==NO_SUCH_LABEL){
		printf("No such label \n");
		print_assemble_time_error(INVALID_ADDRESSING_METHOD ,am_file);
		return INVALID_ADDRESSING_METHOD;
	    } 

	    if(label_address==-1){
		/* Extern label*/
		if(*externOpened==0){
		    FILE * extern_OUT;
		    /* File was not made yet*/
		    printf("Creating .ext file...\n");
		    extern_OUT = fopen(extern_name, "w");
		    if (extern_OUT == NULL) {
			perror("Fatal Error: Error creating .ext file\n");
			return GLOBAL_EXIT_FAILURE; /* or handle the error as needed */
		    }
		    writeExtern(extern_OUT, label_name, *PC);
		    *externOpened=1;
		    fclose(extern_OUT);
		} else if (*externOpened ==1){
		    /* File was made, so append to it.*/
		    FILE * extern_OUT = fopen(extern_name, "a");
		    if (extern_OUT == NULL) {
			perror("Fatal Error: .ext file cannot be found.\n");
			return GLOBAL_EXIT_FAILURE; /* or handle the error as needed */
		    }
		    writeExtern(extern_OUT, label_name, *PC);
		    fclose(extern_OUT);
		}
		writeExternAddress(&Instructions[*PC+1], am_file);
	    } else{
		/* Otherwise we simply write the address to memory. */
		writeLabelAddress(&Instructions[*PC+1], am_file, label_address);
	    }
	    break;
	/* NOTE: Intentional case fallthrough: Here the register is the first operand , so bits 6-8 hold the register number for both 2 & 3. */
	case INDIRECT_REGISTER_ADDRESSING:
	case DIRECT_REGISTER_ADDRESSING:
	    if(*instruction_definition=='*'){
		instruction_definition++;
	    }
	    instruction_definition+=1;
	    register_num = atoi(instruction_definition);
	    if(is_only_operand || is_second_operand){
		/* if it's the only operand, it's always the destination operand*/
		/* If it's the second operand, it's always the destination operand*/
		writeRegisterNumber(&Instructions[*PC+1], -1, register_num);
	    } else{
		writeRegisterNumber(&Instructions[*PC+1], register_num, -1);
	    }
	    break;
	default:
	    return INVALID_ADDRESSING_METHOD;
    }
    return LEXER_EXIT_SUCESS;
} 


int getLabelAddress(char * label_name, symbol_node ** Head){
    /* this function will iterate over all symbols and return the type of the first one it finds.
     * If it finds it's a label, whether it's an entry or not is insignificant, because the address is the same.*/
    symbol_node * current = *Head;
    while(current!=NULL){
	if(strcmp(label_name, current->symbol.label_name) == 0){
	    if(current->symbol.is_external_line){
		return -1;
	    } else{
		return current->symbol.address;
	    }
	}
	current = current->Next;
    }
    return NO_SUCH_LABEL;
}
