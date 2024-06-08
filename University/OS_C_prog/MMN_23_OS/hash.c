#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER 28;
#define MAX_FILENAME_LENGTH 50

// I have limited the file name size, because working with an undefined buffer
// sizes is a major security vulnrability(can cause buffer overflows), so we
// want to be able to work with functions like strncpy. At best, the program
// will segfault because NX was enabled, at worst we have given the user a
// write-what primitive into the stack.) , especially when we write this buffer
// to the stack.

// Structure to hold a file where a number appears
//
typedef struct FileNode {
  char file_source[MAX_FILENAME_LENGTH];
  struct FileNode *next;
} FileNode;

typedef struct {
  FileNode *HEAD;
  int freq; // frequency a number appears throughout a specific buffer
} number_list;

typedef struct {
  number_list table[28+1];
} hash_table;
/* The parse function takes in a pointer to a string as input, and treats it as
 * the name of a buffer (file) that it reads data from.
 *
 * */

int parse(char *str);

int main(int argc, char **argv) {
  int i;
  for (i = 0; i < argc; i++) {
    parse(*argv);
  }
  return EXIT_SUCCESS;
}

int parse(char *str) {
  FILE *dataN = fopen(str, "r");
  if (dataN == NULL) {
    printf("There was an error while trying to open the file...");
    return 1;
  }


}
