public class print_groups {
  public static void CountGroupSum(int index, int[] arr, int sum, int target) {
    if (sum == target) {
      System.out.println();
    }
    if (index == arr.length) {
      return sum == target;
    }

    return CountGroupSum(index + 1, arr, sum + arr[index], target) +
        CountGroupSum(index + 1, arr, sum, target);
  }
}
