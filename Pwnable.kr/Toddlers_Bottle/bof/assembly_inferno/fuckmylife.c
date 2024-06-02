#include <stdio.h>
int fn(int x) {
  int number = 4;
  return number + x;
}

int main() {
  int x = 5;
  printf("%d", fn(x));
  return 0;
}
