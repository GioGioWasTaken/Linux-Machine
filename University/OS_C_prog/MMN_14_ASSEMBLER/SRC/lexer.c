#include "../Headers/lexer.h"
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
