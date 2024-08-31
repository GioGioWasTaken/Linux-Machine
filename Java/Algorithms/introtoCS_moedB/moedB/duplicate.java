public class duplicate {
  public static void main(String[] args) {
    int[] arr1 = { 2, 4, 5, 3, 5, 1 };
    int[] arr2 = { 1, 1, 1, 2, 2, 2, 2 };
    System.out.println(findDuplicate(arr1));
    System.out.println(findDuplicate(arr2));
  }

  public static int findDuplicate(int[] nums) {
    for (int i = 0; i < nums.length; i++) {
      int index = Math.abs(nums[i]);
      if (nums[index] < 0) {
        return index;
      }
      nums[index] = -nums[index];
    }
    return -1; // This should never be reached if there is guaranteed to be a
               // duplicate
  }

  // The time complexity of this is O(N) since we are doing one pass over the
  // array (n being the array size) and space complexity is O(1). There doesn't
  // exist a more efficient approach, intuively, since it's impossible to know
  // whether an array has a duplicate or not without checking all of its
  // elements.
}
