class Solution {
  public static void main(String[] args) {
    int[] nums = { 1, 3, 5, 6 };
    int res = searchInsert(nums, 7);
    System.out.println(res);
    
  }

  static public int searchInsert(int[] nums, int target) {
    int l = 0;
    int r = nums.length - 1;
    while (l < r) {
      int m = (l + r) / 2;
      if (nums[m] > target) {
        r = m - 1;
        globalM = r; // the program always terminates when l==r so l+r/2 =l = r
      } else if (nums[m] < target) {
        l = m + 1;
        globalM = l;
      } else {
        return m;
      }
    }
    return l;
  }
}
