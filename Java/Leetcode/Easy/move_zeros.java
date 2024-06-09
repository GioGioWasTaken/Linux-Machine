class Solution {
  public void moveZeroes(int[] nums) {
    int current_index = 0;
    for (int i = 0; i < nums.length; i++) {
      if (nums[i] == 0) {
        current_index++;
        continue;
      } else {
        nums[i - current_index] = nums[i];
      }
    }

    for (int i = nums.length - 1; i > nums.length - 1 - current_index; i--) {
      nums[i] = 0;
    }
  }

  public void fasterMoveZeroes(int[] nums) {
    int slower = 0;
    int faster = 1;
    while (faster < nums.length) {
      if (nums[faster] != 0) {
        nums[slower] = nums[faster];
        nums[faster] = 0;
        slower++;
        faster++;
      } else {
        faster++;
      }
    }
  }
}
