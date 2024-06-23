public class Q1 {

  public static void main(String[] args) {

    System.out.println("expected true: " +
                       equalSplit(new int[] {-3, 5, 12, 14, -9, 13}));
    System.out.println("expected false: " +
                       equalSplit(new int[] {-3, 5, -12, 14, -9, 13}));
    System.out.println("expected false: " +
                       equalSplit(new int[] {-3, 5, -12, 14, -9}));
  }

  public static boolean equalSplit(int[] arr) {
    int sum = getSum(arr, 0);
    if (sum % 2 == 0) {
      if (equalSplit(arr, 0, sum / 2, arr.length / 2)) {
        return true;
      }
    }
    return false;
  }

  public static boolean equalSplit(int[] arr, int index, int target,
                                   int count) {
    if (target == 0 && count == 0) {
      return true;
    }
    if (index == arr.length) {
      return false;
    }
    return equalSplit(arr, index + 1, target - arr[index], count - 1) ||
        equalSplit(arr, index + 1, target, count);
  }

  public static int getSum(int[] arr, int index) {
    if (index == arr.length) {
      return 0;
    }
    int sum = arr[index] + getSum(arr, index + 1);
    return sum;
  }
}
