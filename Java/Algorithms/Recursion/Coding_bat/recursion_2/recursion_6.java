public class recursion_6 {
  public boolean splitOdd10(int[] nums) {
    return splitOdd10(0, nums, 0, 0);
  }

  public boolean splitOdd10(int start, int[] nums, int group1, int group2) {
    if (start = nums.length) {
      return (group1 % 10 == 0 && group2 % 2 != 0) ||
          (group2 % 10 == 0 && group1 % 2 != 0);
    }

    return splitOdd10(start + 1, nums, group1 + nums[start], group2) ||
        splitOdd10(start + 1, nums, group1, group2 + nums[start]);
  }
}
