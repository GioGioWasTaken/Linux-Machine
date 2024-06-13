class Solution {
  public int[] sortedSquares(int[] nums) {
    int[] res = new int[nums.length];
    int l = 0;
    int r = nums.length - 1;
    int writeIndex = r;
    while (l <= r && writeIndex >= 0) {
      if (Math.abs(nums[l]) > Math.abs(nums[r])) {
        res[writeIndex] = nums[l] * nums[l];
        l++;
      } else {
        res[writeIndex] = nums[r] * nums[r];
        r--;
      }
      writeIndex--;
    }
    return res;
  }
}
