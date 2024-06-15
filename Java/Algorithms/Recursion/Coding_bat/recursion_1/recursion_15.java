public class recursion_15 {
  public boolean array6(int[] nums, int index) {
    if (index == nums.length) {
      return false;
    } else if (nums[index] == 6) {
      return true;
    } else {
      return array6(
          nums,
          index + 1); // assuming the given index is always 0. Otherwise we are
                      // only looking if 6 exists in the range [index , length)
    }
  }
}
