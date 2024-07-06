#include "../include/Hermes.h"

int main(int argc, char ** argv){
	if(argc == 1) {
		HermesHelp();
		return EXIT_FAILURE;
	}
	ReadFlags(argc, argv);
	return EXIT_SUCCESS;
}
