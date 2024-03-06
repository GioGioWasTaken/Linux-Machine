#include <stdio.h>
void increment(int *ptr);
void power(int *ptr, int exponent);
int main() {
  int i = 5;
  printf("%d\n", i);
  increment(&i);
  printf("%d\n", i);
  power(&i, 2);
  printf("%d\n", i);
}

void increment(int *ptr) { (*ptr)++; }
void power(int *ptr, int exponent) {
  if (exponent == 0) {
    *ptr = 1; // When exponent is 0, the result is 1
    return;
  }

  int original = *ptr; // Store the original value of ptr
  while (exponent > 1) {
    *ptr *= original; // Multiply ptr by the original value
    exponent--;
  }
}
