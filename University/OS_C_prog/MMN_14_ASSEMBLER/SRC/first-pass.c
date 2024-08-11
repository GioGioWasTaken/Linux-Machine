#include "../Headers/exit.h"
#include "../Headers/preprocessor.h"
#include "../Headers/utils.h"
#include "../Headers/globals.h"
#include "../Headers/first_pass.h"
#include <stdio.h>
#include <string.h>

int first_pass(char * file_name){
    int exit_code, panic_mode, IC, DC;
    char instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    char directive_definition[MAX_LINE_LENGTH];

    /* Variable declerations */
    IC = 0;
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
    code_location am_file = {
	.line_number = 1,
	.filename=file_name,
    };

    while(fgets(instruction, sizeof(instruction), proc_src) !=NULL && IC<=IC_MAX){
	int is_label =0;
	if(strcmp(instruction, "\n") ==0){
	    /* \n lines are allowed and are ignored*/
	    continue;
	}
	if(sscanf(instruction,"%s:",label_name)==1){
	    is_label =1;
	    label_t * new_label = malloc(sizeof(label_t));
	    new_label->label_name=label_name;
	    char * temp = strchr(instruction, '.');
	    if(temp!=NULL){
		strcpy(directive_definition,temp);
		if(isValidDataLabel()){

		} else if(isValidNonDataLabel()){

		} else{
		    print_assemble_time_error(INVALID_DIRECTIVE_ERROR, am_file);
		    exit_code=FIRST_PASS_EXIT_FAIL;
		    panic_mode = 1;
		    /* Code should no longer assemble*/
		}
	    }


	} else{

	}
    }
}



int isValidDataLabel(char * str){
    if(strcmp(str, ".data") ==0){


    } else if(strcmp(str, ".string")){

    } else{
	return 0;
    }

}
int isValidNonDataLabel(char * str){
    if(strcmp(str, ".extern") ==0){

    } else if(strcmp(str, ".entry")){

    } else{
	return 0;
    }
}
