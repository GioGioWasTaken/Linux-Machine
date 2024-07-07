#include "../include/Hermes.h"
#include "../include/Exit.h"
#include <stdio.h>
#include <string.h>

// NOTE: Revamp setMark function completely. Implement Marks as an array of a struct, whose only member is a char array of size 1024. Every "mark" is now gotten by the location of the mark in the array, and the directory.




typedef struct{
	int mark_num;
	char directory[1024];
} Mark;

#define MAX_MARKS 100

static Mark Marks[MAX_MARKS];
static int mark_count = 0;



// Function to get the marks file path

const char* GetMarksFilePath() {
    static char path[1024];  // Static buffer to hold the path

    // Construct the path if not already done
    if (path[0] == '\0') {
        const char *home = getenv("HOME");
        if (home) {
            snprintf(path, sizeof(path), "%s/%s", home, MARK_FILE_NAME);
        } else {
            snprintf(path, sizeof(path), "/%s", MARK_FILE_NAME); // Fallback if HOME is not set. Shouldn't happen
        }
    }

    return path;
}



/* Firstly, we'll want to load marks from previous sessions, if there are any. */
/* we will need to consume new lines characters, since those are our terminators. */

void consumeNewline(){

}


int LoadMarks() {
    const char *MARKS_FILE_PATH = GetMarksFilePath();
    FILE *MarkFilePath = fopen(MARKS_FILE_PATH, "r");

    if (MarkFilePath) {
        mark_count = 0;

        // Read marks from the file
        while (1) {
            int fields_read = fscanf(MarkFilePath, "%d %[^\n]", &Marks[mark_count].mark_num, Marks[mark_count].directory);
			// this will only return 2 if the input was of the expected type.
			// Break on end of file or error
            if (fields_read == EOF) {
                break;
            }

            // Check if the correct number of fields were read
            if (fields_read != 2) {
                printf("Error reading marks file: Invalid format or corrupted data.\n");
                fclose(MarkFilePath);
                exit(EXIT_FAILURE) ;
            }

            // Ensure the mark number is valid (non-negative)
            if (Marks[mark_count].mark_num < 0 ) {
                printf("Error: Invalid mark number %d in marks file.\n", Marks[mark_count].mark_num);
                fclose(MarkFilePath);
				exit(EXIT_FAILURE);
            }

            mark_count++;
            int ch = fgetc(MarkFilePath);
            if(ch !="\n" || ch ==EOF){
                ungetc(ch, MarkFilePath);
            }
        }

        fclose(MarkFilePath);
        return EXIT_SUCCESS;
    } 

    printf("Marks file could not be loaded. It's possible that it doesn't exist or couldn't be opened.\n");
    printf("To resolve this, ensure that the file \".Hermes_marks\" exists in your HOME directory.\n");
    printf("The file path should look like this: ~/.Hermes_marks\n");
    return EXIT_FAILURE;
}

int SaveMarks(){
	const char *MARKS_FILE_PATH = GetMarksFilePath();
	FILE *MarkFilePath = fopen(MARKS_FILE_PATH, "w");

	if(MarkFilePath){
		for(int i =0; i< mark_count; i++){
			fprintf(MarkFilePath, "%d %s", Marks[i].mark_num, Marks[i].directory);
		}
		fclose(MarkFilePath);
	}
	else{
		fprintf(stderr,"ERROR. failed to create marks file. Please open an issue on GitHub");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// int SetMark(int mark_number, const char *dir) {
//     LoadMarks();
//
//     strncpy(Marks[mark_number].directory, dir, strlen(Marks[mark_number].directory)+1);
//     Marks[mark_number].mark_num= mark_number;
//
//     if(SaveMarks() ==EXIT_FAILURE){
//         fprintf(stderr, "Failed to save new mark to .Hermes_marks");
//     }
//     
//     if (mark_count < MAX_MARKS) {
//         strncpy(Marks[mark_count].directory, dir, sizeof(Marks[mark_count].directory));
//         mark_count++;
//         if(SaveMarks() ==EXIT_FAILURE){
//             fprintf(stderr, "Failed to save new mark to .Hermes_marks");
//             return EXIT_FAILURE;
//         }
//     } else if(mark_count>=MAX_MARKS){
//         fprintf(stderr, "Max Marks limit reached.\n");
//         return EXIT_FAILURE;
//     }
//
//
//     return EXIT_SUCCESS;
// }

int JumpToMark(int mark_number) {
    LoadMarks();
    // NOTE: temporary change! move to having an array of marks.
    for (int i = 0; i < mark_count; i++) { 
        printf("i: \"%d\"\n" ,i);
        printf("mark: \"%d\"\n" ,mark_number);
        printf("mark count: %d\n", mark_count);
        fflush(stdout);
        if (Marks[i].mark_num == mark_number) {
            printf("cd %s\n", Marks[i].directory);
            return EXIT_SUCCESS;
        }
    }
	fprintf(stderr, "Mark not found.\n");
	return EXIT_FAILURE;
}

void ListMarks() {
	LoadMarks();
    for (int i = 0; i < mark_count; i++) {
        printf("Mark #%d: %s\n", Marks[i].mark_num, Marks[i].directory);
    }
}


//NOTE: Add other functions later. It's test time!!


int RemoveMark(int mark_number){
    return 0;
}
int SwitchMarks(int mark1, int mark2){
    return 0;
}

int findDir(const char *dirname){
    return 0;
}


