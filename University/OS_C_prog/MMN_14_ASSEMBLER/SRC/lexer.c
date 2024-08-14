#include "../Headers/lexer.h"
#include "../Headers/memory.h"
#include "../Headers/exit.h"
#include "../Headers/utils.h"
#include <cstring>
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



char * removeDirectiveType(char * directive_definition){
    char * Token;
    Token = strtok(directive_definition, " ");
    skipWhitespace(&directive_definition);
    return Token;
}


int addNumbers(int *DC,MemoryCell Data[], char * directive_definition , code_location am_file){
    char * Token;
    Token = removeDirectiveType(directive_definition);
    if(Token== NULL || *Token=='\0'){
	/* invalid .data definition
	* .data     isn't valid.*/
	print_assemble_time_error(INVALID_DIRECTIVE_DEFINITION,  am_file);
	return INVALID_DIRECTIVE_DEFINITION;
    }
    Token = strtok(NULL, ",");
    while(Token != NULL){
	printf("Debug, Token value: %s",Token );
	addNumber(DC,Data,Token);
	Token = strtok(NULL, ",");
    }
    return LEXER_EXIT_SUCESS;

}

int addString(int * DC,MemoryCell Data[], char * directive_definition, code_location am_file){

}

