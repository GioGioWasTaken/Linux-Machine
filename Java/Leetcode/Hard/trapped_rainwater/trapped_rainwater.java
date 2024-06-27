import java.util.Scanner;

public class trapped_rainwater {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter arr length: ");
    int length = scanner.nextInt();
    int[] arr = getArray(length);
    // int[] arr = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    int[] leftMax = getMaxLeft(arr);
    int[] rightMax = getMaxRight(arr);
    int sum = 0;
    for (int i = 0; i < arr.length; i++) {
      int available_rain = Math.min(leftMax[i], rightMax[i]) - arr[i];
      if (available_rain > 0) {
        System.out.println("Available rain at " + i + " is " + available_rain);
        sum += available_rain;
      }
    }
    System.out.println("The sum is: " + sum);
    scanner.close();
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

  public static int[] getMaxLeft(int[] arr) {
    int[] res = new int[arr.length + 1];
    int max = 0;
    for (int i = 0; i < arr.length; i++) {
      res[i] = max;
      if (arr[i] > max) {
        max = arr[i];
      }
    }

    return res;
  }

  public static int[] getMaxRight(int[] arr) {
    int[] res = new int[arr.length];
    int max = 0;
    for (int i = arr.length - 1; i > 0; i--) {
      res[i] = max;
      if (arr[i] > max) {
        max = arr[i];
      }
    }

    return res;
  }
}
