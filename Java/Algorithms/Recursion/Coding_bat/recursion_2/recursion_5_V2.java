public class recursion_5_V2 {
  public boolean splitArray(int[] nums) {
    return splitArray(0, nums, 0, 0);
  }

  public boolean splitArray(int start, int[] nums, int sumFirstGroup,
      int sumSecondGroup) {
    if (start == nums.length) {
      return sumFirstGroup == sumSecondGroup;
    }
    // recursive step. Either add to group1 or add to group2.
    return splitArray(start + 1, nums, sumFirstGroup + nums[start],
        sumSecondGroup) ||
        splitArray(start + 1, nums, sumFirstGroup,
            sumSecondGroup + nums[start]);
  }
}
