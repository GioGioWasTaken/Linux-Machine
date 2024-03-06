#include <stdio.h>
#include <string.h>
int charToInt(char c);
int power(int base, int exponent);
int main() {
  printf("Please enter your base value and base characters below.\n");
  int base_value;
  printf("Enter your base value: ");
  scanf("%d", &base_value);
  if (base_value < 2 || base_value > 100) {
    printf("Error. Base value cannot be smaller than 2 or bigger than 100.\n");
    return 1;
  }
  char characters[base_value];
  printf("Enter the characters you'd like to use: \n");
  fgets(characters, sizeof(characters), stdin);
  if (sizeof(characters) != base_value) {
    printf(
        "You must enter the same amount of characters as your base value.\n");
    return 1;
  }
  int characters_values[base_value];
  for (int i = 0; i < base_value; i++) {
    characters_values[i] = charToInt(characters[i]);
    printf("test, value at %d is %d\n", i, i);
  }
  printf("Passed.\nPlease enter the base you'd like to translate from to your "
         "base %d: \n",
         base_value);
  int translate_base;
  scanf("%d", &translate_base);
  char lexeme[translate_base];
  printf("Enter the value you want to translate: \n");
  getchar(); // Consume the newline character left in the buffer
  fgets(lexeme, 100, stdin);
  for (int i = 0; i < strlen(lexeme); i++) {
    if (lexeme[i] != '0' || lexeme[i] != '1') {
      return 1;
    }
  }

  if (translate_base < base_value) { // from TL -> base. e.g. TL = 2, Base = 10
    int length = strlen(lexeme);
    int i = length - 2; // -1 because index starts at 0, -2 to not capture \0
    int value = 0;
    while (i >= 0) {
      int power_at_i = power(translate_base, length - 2 - i);
      printf("Current lemexe: %c. Its value is: %d", lexeme[i],
             charToInt(lexeme[i]));
      value += charToInt(lexeme[i]) * power_at_i;
      i--;
    }
    printf("Translated from base %d -> base %d.\nOriginal: %s, Translation: %d",
           base_value, translate_base, lexeme, value);
  } else {
    printf("No support for base conversion from larger to smaller yet.\n");
    return 1;
  }

  return 0;
}

int power(int base, int exponent) {
  if (exponent == 0) {
    return 1; // When exponent is 0, the result is 1
  }

  int result = 1; // Initialize result to 1
  while (exponent > 0) {
    result *= base; // Multiply result by the base value
    exponent--;
  }

  return result;
}
int charToInt(char c) {
  // Subtract the ASCII value of '0' to get the integer value
  int result = c - '0';
  return result;
}
