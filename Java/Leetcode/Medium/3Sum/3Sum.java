class Solution {
  public int[] twoSum(int[] numbers, int target) {
    // first element of binary add operation, we iterate until the second last
    // array element. last one already had all combinations tried.
    // binary search pointers
    int l = 0;
    int r = numbers.length - 1;
    while (l < r) {
      int complement = target - numbers[l];
      if (numbers[r] == complement) {
        return new int[] {l + 1, r + 1};
      } else if (numbers[r] > complement) {
        r--;
      } else {
        l++;
      }
    }
    return new int[] {-1, -1};
    // unreachable if the two elements are
    // guranteed to exist.
  }
}
