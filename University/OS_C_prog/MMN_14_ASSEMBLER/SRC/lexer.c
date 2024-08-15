#include "../Headers/lexer.h"
#include <stdio.h>
#include <string.h>
int determine_opcode(char * str){
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
    const char *directives[4]= {".data", ".string", ".extern", ".entry"};
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
    printf("Token %s\n",Token);
    while(Token != NULL){
	printf("Debug, Token value: %s\n",Token );
	int status_add = addNumber(DC,Data,Token);
	if(status_add==INTEGER_OVERFLOW){
	    print_assemble_time_error(INTEGER_OVERFLOW ,am_file);

	}
	Token = strtok(NULL, ",");
    }
    return LEXER_EXIT_SUCESS;

}

int addString(int * DC,MemoryCell Data[], char * directive_definition, code_location am_file){

}


void cleanCommas(char *instruction) {
    char buffer[MAX_LINE_LENGTH] = "";   /* Temporary buffer for the cleaned string */
    char *result = buffer;
    char *Token;

     /* Skip leading whitespace */
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
