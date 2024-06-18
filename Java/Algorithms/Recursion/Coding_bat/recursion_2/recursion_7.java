public class recursion_7 {
  public boolean split53(int[] nums) {
    return split53(0, nums, 0, 0);
  }

  public boolean split53(int start, int[] nums, int group1, int group2) {
    if (start == nums.length) {
      return group1 == group2;
    }
    if (nums[start] % 5 == 0) {
      return split53(start + 1, nums, group1 + nums[start], group2);
    }
    if (nums[start] % 3 == 0 && nums[start] % 5 != 0) {
      return split53(start + 1, nums, group1, group2 + nums[start]);
    }
    return split53(start + 1, nums, group1, group2 + nums[start]) ||
        split53(start + 1, nums, group1 + nums[start], group2);
  }
}
