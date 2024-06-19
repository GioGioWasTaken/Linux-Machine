public class print_groups {

  public static void PrintGroupSum(int[] arr, int target) {
    PrintGroupSum(0, arr, target,"");
  }
  public static void PrintGroupSum(int index, int[] arr, int sum, String s) {
    if (sum == 0) {
      System.out.println(s);
    }
    if (index == arr.length) {
      return;
    }
    // Include the current element
    PrintGroupSum(index + 1, arr, sum + arr[index], s + arr[index] + " ");

    // Exclude the current element
    PrintGroupSum(index + 1, arr, sum, s);



  }
}
