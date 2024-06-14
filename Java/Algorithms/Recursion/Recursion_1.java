public class Recursion_1 {
  public static void main(String[] args) {
    int[] arr = {1, 2, 3};
    System.out.println(getLength(arr));
  }
  public static int getLength(int[] arr) {
    @overloaded return getLength(arr, 0);
  }
  public static int getLength(int[] arr, int index) {
    if (arr = {}) {
      return 0;
    } else {
      return getLength(arr[index + 1]) + 1;
    }
  }
}
