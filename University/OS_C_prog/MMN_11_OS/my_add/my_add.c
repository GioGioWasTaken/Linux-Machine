/* The my_add.c script takes 2 integers as an input and using binary logic adds
 * them together, and prints the result to STDOUT. it accomplishes this by
 * carrying digits as needed.*/

#include <stdio.h>
#include <stdlib.h>

#define BYTE 8 /* size of a byte. */

/* Function: my_add
 * --------------------
 * Adds two unsigned integers using binary logic and prints the result in
 * binary.
 *
 * a: The first operand.
 * b: The second operand.
 *
 * returns: The sum of a and b.
 */
unsigned int my_add(unsigned int a, unsigned int b);

/* Function: getBinary
 * --------------------
 * Converts a number from a decimal representation to a binary representation.
 *
 * num: The number to convert.
 *
 * returns: A string representing the binary representation of the number.
 */
char *getBinary(unsigned int num);

int main() {
  unsigned int a;
  unsigned int b;

  printf("Please enter the first operand: \n");
  scanf("%u", &a);
  printf("Please enter the second operand: \n");
  scanf("%u", &b);
  printf("The received operands are:\nOperand One: %u\nOperand Two: %u\n ", a,
         b);

  unsigned int res = my_add(a, b);
  printf("The received operands are (in base 10):\nOperand One: %u\nOperand "
         "Two: %u\n ",
         a, b);
  printf("The result (Base 10) is: %u\n", res);

  return 0;
}

char *getBinary(unsigned int num) {
  int i;
  unsigned int bitAmount = sizeof(unsigned int) * BYTE;
  char *binaryStr = malloc(bitAmount + 1);

  for (i = bitAmount - 1; i >= 0; i--) {
    if (num & (1 << i)) {
      binaryStr[bitAmount - 1 - i] = '1';
    } else {
      binaryStr[bitAmount - 1 - i] = '0';
    }
  }
  binaryStr[bitAmount] = '\0';

  return binaryStr;
}

unsigned int my_add(unsigned int a, unsigned int b) {
  unsigned int res = 0;
  unsigned int carry = 0;
  unsigned int mask = 1;
  int i = 0; /* Bit position counter */
  printf("The Operands (base 2) are:\nOperand One: %s\nOperand Two: %s\n ",
         getBinary(a), getBinary(b));
  while (a || b || carry) {
    unsigned int bit_a = a & mask;
    unsigned int bit_b = b & mask;
    unsigned int bit_carry = carry & mask;

    res |= ((bit_a ^ bit_b ^ carry) << i);
    carry = (bit_a & bit_b) | (bit_carry & (bit_a ^ bit_b));

    a >>= 1;
    b >>= 1;
    i++;
  }
  printf("The result (Base 2) is: %s\n", getBinary(res));
  return res;
}
