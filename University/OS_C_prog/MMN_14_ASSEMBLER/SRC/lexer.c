#include "../Headers/lexer.h"
#include <complex>
#include <stdio.h>
#include <string.h>
/* NOTE:  Might be broken if the addsymbols function doesn't expect the instruction to be without the label make sure lalter*/
int determine_opcode(char *str, const instruction_t OPCODES[]) {
    char *mnemonic;
    int opcode;
    char *instr = str;
    skipWhitespace(&instr);  /*Skip leading whitespace*/

    mnemonic = strtok(instr, " ");  /*Extract the mnemonic*/

    /*Iterate through OPCODES to find a match*/
    for (int i = 0; i < 16; i++) {
        if (strcmp(mnemonic, OPCODES[i].mnemonic) == 0) {
            opcode = OPCODES[i].opcode;
            return opcode;  /*Return the opcode for the matched mnemonic*/
        }
    }

    /*If no match is found, return an error code or handle as needed*/
    return NO_SUCH_OPCODE;  /*Example error code for unknown mnemonic*/
}

int parseInstruction(int *IC,MemoryCell Instructions[], char * instruction_definition , code_location am_file){
    char * mnemonic;
    int opcode;
    int arg_count;
    int args_addressing[2] = {-1, -1};
    int ARE;
    char * inst =  instruction_definition;

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
    /* Determine opcode*/
    opcode = determine_opcode(inst, OPCODES);
    if(opcode==NO_SUCH_OPCODE){
	print_assemble_time_error(NO_SUCH_OPCODE, am_file);
	return NO_SUCH_OPCODE;
    }
    arg_count = OPCODES[opcode].operand_count;


    /* Parse arguments */
    if(arg_count!=0){
	skipWhitespace(&inst); 
	/* inst is now pointing at the first char of the first argument*/
	switch (*inst) {
	    case '*':
		break;
	    case '#':
	    	break;

	}
    } 
    

    /* Add the instruction to memory */
    addInstruction(IC, Instructions,opcode, arg_count, args_addressing, ARE);

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
    printf("AddString: Debug, Token value: %s\n",Token);
    while(i<=strlen(Token)){
	printf("AddString: Debug, Token value: %c\n",Token[i]);
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

     /* Extract the directive (e.g., .data) and skip it */
    Token = strtok(instr, " ");
    Token = strtok(NULL, ",");   
    skipWhitespace(&Token);

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
    printf("Cleaned: %s\n", instruction);
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
