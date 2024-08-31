public class Q1_kAlmost {
  public static void main(String[] args) {
    int[] arr = { 3, 0, 0, 4, 7, 9, 0, 0, 0, 0,
        11, 15, 0, 19, 20, 0, 0, 31, 40, 0 };
    System.out.println(kAlmostSearch(arr, 9)); // output: 5
    System.out.println(kAlmostSearch(arr, 31)); // output: 17
    System.out.println(kAlmostSearch(arr, 30)); // output: -1
    int[] arr2 = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int[] arr3 = { 0, 0, 0, 0, 0, 0, 0, 0 };
    System.out.println(kAlmostSearch(arr2, 1)); // output 0
    System.out.println(kAlmostSearch(arr3, 1)); // output -1
  }

  public static int kAlmostSearch(int[] nums, int target) {
    int l = 0;
    int r = nums.length - 1;
    while (l <= r) {
      int m = l + (r - l) / 2;
      if (nums[m] == target) {
        return m;
      } else if (nums[m] == 0) {
        int rightM = m + 1;
        int leftM = m - 1;
        while (nums[rightM] == 0 && rightM < r)
          rightM++;
        while (nums[leftM] == 0 && rightM >= 0)
          leftM--;
        if (nums[leftM] >= target) {
          r = leftM;
        }
        if (nums[rightM] <= target) {
          l = rightM;
        }
      } else if (nums[m] > target) {
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    return -1;
  }
}
