#include "../Headers/second_pass.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int secondPass(MemoryCell Code[], int IC, int DC, symbol_node ** Head, code_location am_file, FILE * proc_src ){
    char raw_instruction[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    int PC = IC_INITIAL;
    char directive_definition[MAX_LINE_LENGTH];
    char * instruction,*directive_name, *ptr , *temp;
    char file_no_extension[256];  
    char entry_output_name[260];  
    char extern_output_name[260];
    char object_output_name[260];
    int extern_opened = 0;
    int panic_mode = 0;
    int Label_Definition, status, entry_status,parsing_status;
    /* Copy filename and remove the ".am" extension*/
    strncpy(file_no_extension, am_file.filename, strlen(am_file.filename) - 3); 
    file_no_extension[strlen(am_file.filename) - 3] = '\0';  

    /* Create new file names with different extensions*/
    snprintf(entry_output_name, sizeof(entry_output_name), "%s.ent", file_no_extension);
    snprintf(extern_output_name, sizeof(extern_output_name), "%s.ext", file_no_extension);
    snprintf(object_output_name, sizeof(object_output_name), "%s.ob", file_no_extension);

    while(fgets(raw_instruction, sizeof(raw_instruction), proc_src) !=NULL){
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

	Label_Definition  = (strchr(raw_instruction, ':') && sscanf(raw_instruction, "%[^:]:", label_name) == 1);

	if(Label_Definition) { 
	    instruction = skip_label(&raw_instruction[0]);
	} else{
	    instruction = &raw_instruction[0];
	}
	    temp = strchr(instruction, '.');
	    int isDirective = temp!=NULL;
	if(isDirective){
	    strcpy(directive_definition,temp);
	    status = isValidDirective(directive_definition);
	    if(status!=ENTRY_DIRECTIVE){
		continue;
		/* We can do an else  block here immediately because if it was of any other undefined directive type,
		     * it would have been discovered in the first pass.*/
	    } else{
		printf("entry detected! Looking for its address....\n");
		entry_status = setEntryAddress(directive_name, Head);
		if(entry_status== NO_SUCH_LABEL){
		    print_assemble_time_error(NO_SUCH_LABEL, am_file);
		    panic_mode = 1;
		}
	    }
	} else{
	    printf("PC: %d\n",PC);
	    parsing_status = parseRemainingInstruction(&PC, Code, instruction, am_file,Head, extern_output_name,&extern_opened);
	    if(parsing_status==LEXER_EXIT_FAIL){
		panic_mode =1;
		break;
	    }

	}
	am_file.line_number++;
	} 
    /* TODO: Create the output files
     * Object : setting the address of the external temporarily to where it was called from*/ 



    if(panic_mode!=1){
	int i;
	for(i =100 ; i<120; i++){
	    printf("%d: ",i);
	    printBinary(Code[i].SecondByte);
	    printBinary(Code[i].FirstByte);
	    printf("\n");
	}
	createEntryOutput(Head, entry_output_name);
	createObjectOutput(object_output_name,Code,DC, IC);
	return SECOND_PASS_EXIT_SUCESS;
    } else{
	if(extern_opened==1){
	    deleteExternOutput(Head,extern_output_name);
	}
	return SECOND_PASS_EXIT_FAIL;
    }
}


