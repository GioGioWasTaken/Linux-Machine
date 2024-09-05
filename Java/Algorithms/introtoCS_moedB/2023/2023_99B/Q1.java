public class Q1{
	public static void main(String[] args) {
		int nums[] = { 1, 1, 4, 10, 10, 4, 3, 10, 10 };
		int nums2[] = { 1, 2, 3, 4 };
		int nums3[] = {3,1,1,1,1,3};
		System.out.println(
			longestAlmostPalindrome(nums)
		);

		System.out.println(
			longestAlmostPalindrome(nums2)
		);

		System.out.println(
			longestAlmostPalindrome(nums3)
		);

	}
	public static int longestAlmostPalindrome(int[] nums) {
		return longestAlmostPalindrome(nums, 0);
	}

	public static int longestAlmostPalindrome(int[] nums, int startIndex) {
		if(startIndex ==nums.length){
			return Integer.MIN_VALUE;
		}
		int option1 = longestAlmostPalindromeHelper(nums,startIndex, nums.length-1);
		int option2 = longestAlmostPalindrome(nums,startIndex + 1);
		return Math.max(option1, option2);
	}


	public static int longestAlmostPalindromeHelper(int[] nums, int startIndex, int endIndex) {
		if(endIndex < 0 || startIndex > nums.length-1){
			return Integer.MIN_VALUE;
		}
		if(nums[startIndex] != nums[endIndex]){
			return Math.max(1, longestAlmostPalindromeHelper(nums, startIndex, endIndex-1));
		} else if(nums[startIndex] == nums[endIndex] && startIndex!= endIndex){
			return 1+longestAlmostPalindromeHelper(nums, startIndex+1, endIndex-1);
		} else{
			return 1;
		}

	}

}
