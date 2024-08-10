#include "../Headers/exit.h"
#include "../Headers/utils.h"
#include "../Headers/globals.h"

int first_pass(char * file_name){
    int exit_code, panic_mode, IC, DC;

    if(line_too_long_exists(file_name)){
	panic_mode = 1;
    }

}
