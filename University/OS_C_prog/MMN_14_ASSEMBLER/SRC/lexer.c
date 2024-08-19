#include "../Headers/lexer.h"
#include <stdio.h>
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
    {"lea",  1, 4},
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
    char delimiter = ' ';  /* Delimiter used in strtok*/

    skipWhitespace(&instr);  /* Skip leading whitespace */

    /* Extract the mnemonic using strtok*/
    mnemonic = strtok(instr, &delimiter);
    /* printf("Opcode mnemonic: '%s' ", mnemonic);*/

    /* Iterate through OPCODES to find a match */
    for (i = 0; i < 16; i++) {
        if (mnemonic && strcmp(mnemonic, OPCODES[i].mnemonic) == 0) {
            opcode = OPCODES[i].opcode;
            printf("Opcode detected for line: %d\n", opcode);

            /* Restore the delimiter by finding the end of the mnemonic token*/
            char *end = mnemonic + strlen(mnemonic);
            *end = delimiter;  /* Set the last character to the delimiter*/

            return opcode;  /* Return the opcode for the matched mnemonic */
        }
    }

    /* If no match is found, return an error code or handle as needed */
    printf("Faulty Opcode mnemonic detected: '%s'\n", mnemonic);
    return NO_SUCH_OPCODE;  /* Example error code for unknown mnemonic */
}

int parseInstruction(int *Current_IC,int *IC,MemoryCell Instructions[], char * instruction_definition , code_location am_file){
    char *mnemonic, *Token;
    int opcode, arg_count, args_provided, ARE;
    int args_addressing[2] = {-100, -100};
    args_provided = 0;
    char * inst =  instruction_definition;
    printf("Instruction definition: %s\n", inst);

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

	    /* inst is now pointing at the first char of the first argument*/
	    switch (*inst) {
		case '*':
		    /* Since I am using the same function for the other case as well,
		    the function should assume the same state. I will pass the first char of the register in both instances*/
		    if(isRegister(inst+1, Registers)){
			printf("Treat register as pointer\n");
			args_addressing[args_provided]=2;
		    } else{
			print_assemble_time_error(NO_SUCH_REGISTER, am_file);
			return NO_SUCH_REGISTER;
		    }
		    break;
		case '#':
		    printf("Absolute value \n");
		    args_addressing[args_provided]=0;
		    break;
		default:
		    if(isRegister(inst+1, Registers)){
			printf("Treat register as value");
			args_addressing[args_provided]=3;
		    } else{
			args_addressing[args_provided]=1;
		    }
		    break;
	    }
	    args_provided++;
	    Token = strtok(NULL, ",");
	}
    } 
    

    /* Add the instruction to memory */
    ARE = 2; /*  This method will only be used for the first word of the instruction, so it's always going to be 2;*/
    *Current_IC=addInstruction(IC, Instructions,opcode, arg_count, args_addressing, ARE);
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
	int status_add = addNumber(DC,Data,Token);
	if(status_add==INTEGER_OVERFLOW){
	    print_assemble_time_error(INTEGER_OVERFLOW ,am_file);

	}
	Token = strtok(NULL, ",");
    }
    return LEXER_EXIT_SUCESS;

}

int addString(int * DC,MemoryCell Data[], char * directive_definition, code_location am_file){
    /* NOTE: I heard some other sutdents saying that a string with a " character inside it is valid,
     * but that seemed quite undefined to me so I decided to not include it in this implementation 
     * I hope that wasn't the actual thing we were supposed to do as it wasn't directly included in the instructions :0 */
    char *Token;
    int i;

    /* We do this to clear leading spaces. E.g. "    .data"*/
    char *string_definition = directive_definition;
    skipWhitespace(&string_definition);

     /* Extract the directive (e.g., .data) and skip it */
    Token = strtok(string_definition, " ");
    Token = strtok(NULL, "\""); 
    if(Token==NULL){
	print_assemble_time_error(UNCLOSED_STRING_ERROR, am_file);
	return UNCLOSED_STRING_ERROR;
    }

    i = 0;
    /* We also want to pass the null byte into the function. So we'll use <= */
    while(i<=strlen(Token)){
	int status_add = addChar(DC,Data,Token[i]);
	i++;
    }
    return LEXER_EXIT_SUCESS;
}


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
    printf("Register detected is : '%s'\n", Register);
    fflush(stdout);
    for(i = 0; i<8; i++){
	if(strcmp(Register, Registers[i]) == 0){
	    return GLOBAL_EXIT_SUCESSS;
	}
    }
    return GLOBAL_EXIT_FAILURE;
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
        if (strcmp(word_to_check, OPCODES[i].mnemonic) == 0) {
            return TRUE;
        }
    }

    return FALSE;  /* Return FALSE if no match is found*/
}
