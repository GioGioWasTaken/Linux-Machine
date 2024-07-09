#ifndef HERMES_H
#define HERMES_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>



#define MARK_FILE_NAME ".Hermes_marks"


// Function prototypes
void HermesHelp(void);
void ReadFlags(int argc, char **argv);

int SetMark(int mark_number, const char *dir);
int LoadMarksFile(void);
int SaveMarks(void);

int JumpToMark(int mark_number);
void ListMarks(void);
int RemoveMark(int mark_number);
int SwitchMarks(int mark1, int mark2);


int findDir(const char *dirname);


//TODO: Might implement features here in the future. Not to say the above are already implemented 
// void ListFrequentDirs(int freq);

#endif
