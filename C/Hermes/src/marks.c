#include "../include/Hermes.h"
#include "../include/Exit.h"
#include <stdio.h>
#include <string.h>

// NOTE: Revamp setMark function completely. Implement Marks as an array of a struct, whose only member is a char array of size 1024. Every "mark" is now gotten by the location of the mark in the array, and the directory.




typedef struct{
	char directory[1024];
        int mark_num;
} Mark;

#define MAX_MARKS 100

static Mark Marks[MAX_MARKS];
static int mark_count = 0;



// Function to get the marks file path

void initialize_Marks(Mark Marks[]){
    int i;
    for(i = 0; i<100; i++){
        Marks[i].mark_num = 0;
    }
}


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



int LoadMarksFile() {
    initialize_Marks(Marks);
    const char *MARKS_FILE_PATH = GetMarksFilePath();
    FILE *MarkFilePath = fopen(MARKS_FILE_PATH, "r");

    if (MarkFilePath) {
        mark_count = 0;
        // Read marks from the file
        while (1) {
            int fields_read = fscanf(MarkFilePath, "%d %[^\n]\n", &Marks[mark_count].mark_num, Marks[mark_count].directory);
            // printf("mark num read: %d\n",Marks[mark_count].mark_num);

            if (fields_read == EOF) {
                // printf("Invalid file. File is empty.\n");
                break; // empty file
            }

            // Check if the correct number of fields were read
            if (fields_read != 2) {
                printf("Error reading marks file: Invalid format or corrupted data.\n");
                fclose(MarkFilePath);
                exit(EXIT_FAILURE) ;
            }

            if(Marks[mark_count].mark_num <1){
                printf("An invalid mark was detected when loading marks.\n");
                fclose(MarkFilePath);
                exit(EXIT_FAILURE);
            }

            mark_count++; // if there was any valid mark.
            printf("Mark count: %d\n", mark_count);
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
            printf("Writing to file...\nmarknum: %d\nmark_dir: %s\n", Marks[i].mark_num, Marks[i].directory);
            fprintf(MarkFilePath, "%d %s\n", Marks[i].mark_num, Marks[i].directory);
        }
        fclose(MarkFilePath);
    }
    else{
        fprintf(stderr,"ERROR. File not found. This file should be created automatically. Run: touch ~/.Hermes_marks\n ");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int SetMark(int mark_number, const char *dir) {
    int mark_saved;
    LoadMarksFile(); // read former contents so as to not lose data.

    if(mark_number < 1 || mark_number >100){
        fprintf(stderr,"Mark must be greater or equal to 1 and smaller than 100.\n");
        exit(EXIT_FAILURE);
    }



    strncpy(Marks[mark_number-1].directory, dir, strlen(dir)+1);
    Marks[mark_number-1].mark_num= mark_number;
    if(Marks[mark_number-1].mark_num == 0){
        ++mark_count; // mark count only increases if the mark was unset beforehand.
    } 
    if((  mark_saved = SaveMarks() ) ==EXIT_FAILURE){
        fprintf(stderr, "Failed to save new mark to .Hermes_marks");
    }
    
    if(mark_count>=MAX_MARKS){
        fprintf(stderr, "Max Marks limit reached.\n");
        return EXIT_FAILURE;
    }
    mark_count++;
    return EXIT_SUCCESS;
}

int JumpToMark(int mark_number) {
    LoadMarksFile();
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
	LoadMarksFile();
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


