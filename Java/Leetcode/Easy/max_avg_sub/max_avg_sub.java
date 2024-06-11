class Solution {
  public double findMaxAverage(int[] nums, int k) {
    int sum = 0.0;
    for (int i = 0; i < k; i++) {
      sum += nums[i];
    }
    double globalMax = sum / k;

    for (int i = 1; i <= nums.length - k; i++) {
      sum = sum - nums[i - 1] + nums[i + k - 1];
      double avg = sum / k;
      globalMax = Math.max(globalMax, avg);
    }
    return globalMax;
  }
}
