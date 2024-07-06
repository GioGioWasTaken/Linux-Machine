#include <stdio.h>

void HermesHelp(){
	printf("Hello and welcome to Hermes!\n");
	printf("To use hermes, you can use both the Hermes keyword and the hs keyword.\n");
	printf("Use hs --help, or hs to get this help menu.\n");
	printf("For a more detailed explaination, refer to the README file in the source github repo.\n");
	printf("Usage: hermes [options]\n");
	printf("Options:\n");
	printf("  -n, --new <num>        Set the mark number\n");
	printf("hs <num>	Jump to the <num> indexed mark");
	printf("  -l, --list, --ls       List all marks\n");
	printf("  -r, --remove <num>     Remove a mark\n");
	printf("  -s, --switch <num> <num> Switch or rebind marks\n");
	printf("  -S, --search <dirname> Search and jump to directory\n");
}
