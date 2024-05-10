#include <stdio.h>
#include <string.h>
int main() {
  int lightbulb[100];
  int i;
  int j;
  for (i = 1; i <= 100; i++) {
    for (j = 0; j < 100; j++) {
      if (j % i == 0) {
        lightbulb[j] = !lightbulb[j];
      } /* iterate over all lightbulb turn on and off. */
    }
  }

  printf("Array: \n");
  int k;
  for (k = 0; k < 100; k++) {
    printf("%d, ", lightbulb[k]);
  }
  printf("\n");
  return 0;
}
