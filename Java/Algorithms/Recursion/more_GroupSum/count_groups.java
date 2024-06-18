public class count_groups {
  public static void main(String[] args) {
    int[] arr1 = { 1, 2, 2, 5 };
    System.out.println(CountGroupSum(arr1, 5));
  }

  public static int CountGroupSum(int[] arr, int target) {
    return CountGroupSum(0, arr, 0, target);
  }

  public static int CountGroupSum(int index, int[] arr, int sum, int target) {
    if (sum == target) {
      return 1;
    }
    if (index == arr.length) {
      return 0;
    }

    return CountGroupSum(index + 1, arr, sum + arr[index], target) +
        CountGroupSum(index + 1, arr, sum, target);
  }
}
