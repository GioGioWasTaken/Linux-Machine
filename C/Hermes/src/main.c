#include <stdio.h>
#include "../include/Exit.h"
#include "../include/Help.h"

int main(int argc, char ** argv){
	if(argc == 0) {
		HermesHelp();
		exit(EXIT_SUCCESS);
	}

}
