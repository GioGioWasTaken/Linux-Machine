#include <stdio.h>
#include <stdlib.h>
/* Function Prototypes:*/
char *get_contents(FILE *file);

int main(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      printf("Error opening file %s\n", argv[i]);
      continue; // Move to the next file
    }
    char *res = get_contents(file);
    printf("Filename: %s:\n %s\n", argv[i], res);
  }
  return 0;
}

char *get_contents(FILE *file) {
  long int size;
  fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
  size = ftell(file); // Get the current position, which is the size of the file
  rewind(file);       // Rewind the file pointer to the beginning of the file
  char *buffer = (char *)malloc(size + 1);
  if (buffer == NULL) {
    printf("Memory allocation fail error.\n");
    exit(1);
  }
  fread(buffer, sizeof(char), size, file);
  buffer[size] = '\0';
  return buffer;
}
