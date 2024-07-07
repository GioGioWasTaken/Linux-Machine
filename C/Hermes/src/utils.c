#include "../include/Hermes.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define MAX_DIR_LENGTH 1024
void ReadFlags(int argc, char **argv){
	int opt;
	int mark_number = -1;
	int second_mark = -1;
	char *dir = "CURRENT"; // there can never be such a path, no conflicts.

	// convineent state of each new instance of hermes.

	static struct option long_options[] = {
		{"new", required_argument, NULL, 'n'},
		{"list", no_argument, NULL, 'l'},
		{"ls", no_argument, NULL, 'l'},
		{"remove", required_argument, NULL, 'r'},
		{"switch", required_argument, NULL, 's'},
		{"find", required_argument, NULL, 'f'},
		{0, 0, 0, 0} // terminator of struct. Getoptlong expects this.
	};
	while ((opt = getopt_long(argc, argv, "n:lr:s:f:", long_options, NULL)) != -1) {
		switch (opt) {
			case 'n':
				mark_number = atoi(optarg);
				if (optind < argc && argv[optind][0] != '-') {
					dir = argv[optind]; // Next argument is the directory path
					optind++; // Move to the next argument
				}
				// BUG: when setting directory a new line is not inserted properly, causing many issues.
				if(strcmp("CURRENT", dir) ==0){
					printf("Setting current directory as mark.\n");
					char current_dir[MAX_DIR_LENGTH];
					if(getcwd(current_dir, MAX_DIR_LENGTH) == NULL){
						printf("getcwd failed, can't set current dir as mark.");
						 exit(EXIT_FAILURE);
					} else{
						char * dir_newline = strcat(current_dir, "\n");
						SetMark(mark_number,dir_newline);
					}
				} else{
					char * dir_newline = strcat(dir, "\n");
					SetMark(mark_number,dir_newline);
				}
				break;
			case 'l':
				ListMarks();
				break;
			case 'r':
				mark_number = atoi(optarg);
				RemoveMark(mark_number);
				break;
			case 's':
				mark_number = atoi(optarg);
				second_mark = atoi(argv[optind]);
				SwitchMarks(mark_number, second_mark);
				break;
			case 'f':
				findDir(optarg);
				break;
			default:
				HermesHelp();
				exit(EXIT_FAILURE);
		}
	}
    // Jump to mark if no other options matched
    if (optind < argc) {
        mark_number = atoi(argv[optind]);
        JumpToMark(mark_number);
    }
}
