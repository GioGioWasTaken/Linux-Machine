#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

/* Prototypes. */
int calculate(char *expr, int size);
// the calculate function takes a string and its size as an input, and returns
// an integer, after having calculated the expression in the string.
char *printBinary(int num);

int main(int argc, char *argv[]) {
  printf("Choose mode:\n");
  printf("1: Result in Hex\n");
  printf("2. Result in Dec :\n");
  printf("3. Result in Binary:\n");

  int mode;
  scanf("%d", &mode);
  while (getchar() != '\n')
    ;
  char expr[100];
  printf("Enter expression:");
  fgets(expr, 100, stdin);
  int size = strlen(expr);
  int res = calculate(expr, size);
  switch (mode) {
  case 1:
    printf("%x\n", res);
    break;
  case 2:
    printf("%d\n", res);
    break;
  case 3:
    printBinary(res);
    break;
  }
  return EXIT_SUCCESS;
}
