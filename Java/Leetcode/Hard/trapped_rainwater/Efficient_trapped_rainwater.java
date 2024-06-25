
/**
 * Efficient_trapped_rainwater
 */
import java.util.Scanner;

public class Efficient_trapped_rainwater {

  public static void main(String[] args) {

    // int[] arr = getArray(length);
    int[] arr = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    int ptrLeft = 0;
    int ptrRight = arr.length - 1;
    int maxLeft = arr[ptrLeft];
    int maxRight = arr[ptrRight];
    int sum = 0;
    while (ptrLeft < ptrRight) {
      if (maxRight > maxLeft) {
        ptrLeft++;
        if (maxLeft - arr[ptrLeft] > 0) {
          sum += maxLeft - arr[ptrLeft];
        }
        if (arr[ptrLeft] > maxLeft) {
          maxLeft = arr[ptrLeft];
        }
      } else { // if maxRight<=maxLeft
        ptrRight--;
        if (maxRight - arr[ptrRight] > 0) {
          sum += maxRight - arr[ptrRight];
        }
        if (arr[ptrRight] > maxRight) {
          maxRight = arr[ptrRight];
        }
      }
    }
    System.out.println("The sum is: " + sum);
  }

  public static int[] getArray(int size) {
    Scanner scanner = new Scanner(System.in);
    int[] arr = new int[size];
    for (int i = 0; i < size; i++) {
      System.out.println("Please enter your number: ");
      arr[i] = scanner.nextInt();
    }
    scanner.close();
    return arr;
  }
}
