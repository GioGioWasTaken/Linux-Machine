/*The my_suffix.c script takes a character and string and prints all the
 * suffixes that start with that character, as found in that string. It also
 * counts how many suffixes of said description were found.  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function: substring
 * --------------------
 * Extracts a substring from the given string.
 *
 * start: The starting index of the substring (inclusive).
 * end: The ending index of the substring (exclusive).
 * string: The input string.
 *
 * returns: The extracted substring.
 */
char *substring(int start, int end, char *string);

/**
 * Function: suffix
 * ----------------
 * Counts the occurrences of the given suffix character in the string and prints
 * out each suffix found.
 *
 * str: The input string.
 * c: The suffix character to search for.
 *
 * returns: The count of suffix occurrences.
 */
int suffix(char str[], char c);

int main() {
  char *StringInput = malloc(128); /* Allocate memory for the input string */
  char char_to_read;
  if (StringInput == NULL) {
    printf("Memory allocation failed. Exiting...\n");
    return 1;
  }

  printf("Enter a string: ");
  scanf("%s", StringInput);

  printf("Enter a character to count as suffix: ");
  scanf(
      " %c",
      &char_to_read); /* Added space before %c to consume leading whitespace */

  int count_suffix =
      suffix(StringInput, char_to_read); /* Unfortunately this statement cannot
                                            be moved to the top. */
  printf("Number of suffix occurrences: %d\n", count_suffix);

  free(StringInput); /* Free dynamically allocated memory */
  return 0;
}

int suffix(char str[], char c) {
  int size = strlen(str);
  int suffix_count = 0;
  int i;
  for (i = 0; i < size; i++) {
    if (str[i] == c) {
      suffix_count++;
      printf("Suffix found: %s\n", substring(i, size, str));
      free(substring(i, size,
                     str)); /* Free memory allocated for the substring */
    }
  }
  return suffix_count;
}

char *substring(int start, int end, char *string) {
  int i;
  int length = end - start;
  char *res = malloc(length + 1);
  if (res == NULL) {
    return NULL; /* Handle allocation failure */
  }

  for (i = 0; i < length; i++) {
    res[i] = string[start + i];
  }
  res[length] = '\0'; /* Null-terminate the substring */

  return res;
}
