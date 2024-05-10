/* Code Author: Iyar Segev
 * Script's purpose: partialSums.c is a simple program that takes from the user as input an array size,
 * and the array elements to make an array arr 
 * and returns an array res, s.t. the ith element of res is equal the sum between the 0th and i (inclusive) elements of arr*/

#include <stdio.h>
#include <stdlib.h>

/* Function prototypes: */

/*
 * Function: printArray
 * ---------------------
 * Prints the elements of an array in an organized manner. Is used as a helper function.
 *
 * arr: Pointer to the array.
 * size: Size of the array.
 */
void printArray(int *arr, int size);

/*
 * Function: partialSums
 * ---------------------
 * Calculates the partial sums of an array. As per the definition of a partial sum in the MMN12 document.
 *
 * arr: Array of integers.
 * size: Size of the array.
 *
 * Returns: Pointer to the array of partial sums.
 */
int *partialSums(int arr[], int size);



int main(int argc, char *argv[]) {
  /* Local variables */
  int size;
  int *arr;
  int *res;
  int i;

  printf("Please enter the size of the array here:\n");
  scanf("%d", &size);
  arr = malloc(sizeof(int) * size);
  for (i = 0; i < size; i++) {
    printf("Please enter the #%d array entry\n", i + 1);
    scanf("%d", &arr[i]);
  }
  /* Print the input data for the end user's comfort */
  printf("The array size is: %d\n", size);
  printf("The array is: ");
  printArray(arr, size);
  res = partialSums(arr, size);
  printArray(res, size);
  /* Free heap allocated data */
  free(arr);
  free(res);
  return EXIT_SUCCESS;
}

int *partialSums(int arr[], int size) {
  int *p = malloc(sizeof(int) * size);
  int i;
  int sum = 0;
  for (i = 0; i < size; i++) {
    sum += arr[i];
    p[i] = sum;
  }
  return p;
}

void printArray(int *arr, int size) {
  int j;
  printf("[");
  for (j = 0; j < size - 1; j++) {
    printf("%d, ", arr[j]);
  }
  if (size > 0) {
    printf("%d", arr[size - 1]);
  }
  printf("]\n");
}
