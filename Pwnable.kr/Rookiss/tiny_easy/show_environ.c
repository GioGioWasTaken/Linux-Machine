#include <stdio.h>

int main() {
  extern char **environ; // Declare extern for environment variable array

  for (char **var = environ; *var != NULL; var++) {
    printf("%s\n", *var);
  }

  return 0;
}
