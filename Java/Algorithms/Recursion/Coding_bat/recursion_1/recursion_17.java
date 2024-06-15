public class recursion_17 {
  public boolean array220(int[] nums, int index) {
    if (nums.length == 0)
      return false;
    if (index == nums.length - 1)
      return false;
    else {
      int currentVal = nums[index];
      int nextVal = nums[index + 1];
      if (nextVal == currentVal * 10)
        return true;
      else {
        return array220(nums, index + 1);
      }
    }
  }
}
