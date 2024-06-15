public class recursion_3 {
  public boolean groupNoAdj(int start, int[] nums, int target) {
    if (start >= nums.length) {
      return (target == 0); // base case, if we have finished iterating over all
                            // elements, check if target is proper
    }
    return groupNoAdj(
        start + 2, nums,
        target -
            nums[start])
        || // our choices: either including 1 and
           // skipping the next, or not including one
        groupNoAdj(start + 1, nums, target);
  }
}
