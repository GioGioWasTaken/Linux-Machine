public class recursion_5 {
  public static boolean splitArray(int[] nums) {
    int sum = getSum(0, nums);
    if (sum % 2 != 0) {
      return false;
    } else {
      return groupSum(0, nums, sum / 2);
    }
  }

  public static boolean groupSum(int start, int[] nums, int target) {
    if (target == 0)
      return true;
    if (start == nums.length)
      return false;

    return groupSum(start + 1, nums, target - nums[start]) ||
        groupSum(start + 1, nums, target);
  }

  public static int getSum(int start, int[] nums) {
    if (start == nums.length) {
      return 0;
    }
    return nums[start] + getSum(start + 1, nums);
  }
}
