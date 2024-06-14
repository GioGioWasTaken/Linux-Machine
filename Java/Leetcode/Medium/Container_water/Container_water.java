class Solution {
  public int maxArea(int[] height) {
    int l = 0;
    int r = height.length - 1;
    int global_max = Integer.MIN_VALUE;
    while (l < r) {
      int width = r - l;
      int water_volume = width * Math.min(height[l], height[r]);
      if (water_volume > global_max) {
        global_max = water_volume;
      }
      if (height[l] > height[r]) {
        r--;
      } else {
        l++;
      }
    }
    return global_max;
  }
}
