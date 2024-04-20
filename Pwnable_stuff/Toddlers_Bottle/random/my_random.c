#include <stdio.h>
#include <stdlib.h> // Include <stdlib.h> for rand() function

int main() {
  unsigned int random;
  random = rand(); // random value!
  int input;
  printf("Random num: %d\n", random);

  // printf("Please enter your input:\n");
  // scanf("%d", &input);
  input = 0xB526FB88;
  if ((random ^ input) == 0xdeadbeef) {
    printf("You got it!\n");
  } else {
    printf("Wrong complement.\n");
    printf("xor result (binary): %b\n", random ^ input);
    printf("Xor result (hex): %x\n", random ^ input);
    printf("Xor result (decimal): %u\n",
           random ^ input); // Print decimal representation
  }
  return 0;
}
