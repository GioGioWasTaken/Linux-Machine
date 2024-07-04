#include <stdio.h>

int isNumber(char c);
int getWordLength(char *input);

int main() {
  char input[100];
  scanf("%s", input);
  int length = getWordLength(input);
  int *pLength = &length;
  int i = 0;
  int j = *pLength;

  while (i < length) {
    if (isNumber(input[i])) {
      printf("first number: %c\n", input[i]);
      break;
    }
    i++;
  }

  while (j > i) {
    if (isNumber(input[j])) {
      printf("Second number: %c\n", input[j]);
      break;
    }
    j--;
  }
}

int getWordLength(char *input) {
  int counter = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    counter++;
  }
  return counter;
}

int isNumber(char c) { return (c >= '0' && c <= '9'); }
