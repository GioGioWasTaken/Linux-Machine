class Solution {
  public int minSubArrayLen(int target, int[] nums) {
    if (nums.length == 0) {
      return 0;
    }
    int l = 1;
    int r = nums.length;
    int globalMin = Integer.MAX_VALUE;

    while (l <= r) {
      int m = l + (r - l) / 2;
      if (findMaxSubarr(nums, m, target)) {
        globalMin = m;
        r = m - 1;
      } else {
        l = m + 1;
      }
    }

    return globalMin == Integer.MAX_VALUE ? 0 : globalMin;
  }

  public static boolean findMaxSubarr(int[] nums, int k, int target) {
    int sum = 0;
    for (int i = 0; i < k; i++) {
      sum += nums[i];
    }
    if (sum >= target) {
      return true;
    }
    for (int i = k; i < nums.length; i++) {
      sum = sum - nums[i - k] + nums[i];
      if (sum >= target) {
        return true;
      }
    }
    return false;
  }
}
