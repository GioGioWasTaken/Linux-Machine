#include <stdio.h>
#include <unistd.h>

#define EXIT_SUCCESS 0;
#define EXIT_FAIL 1;

int main(int argc, char *argv[]) {
  char path[1024];
  if (getcwd(path, sizeof(path) != NULL)) {
    printf("%s\n", path);
  } else {
    perror("getcwd");
    return EXIT_FAIL;
  }

  return EXIT_SUCCESS;
}
