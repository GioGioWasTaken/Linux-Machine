public class Q1{
	public static void main(String[] args){
		int nums[] = { 2, 6, 0, 1, 9, 7, 3, 1, 4, 1, 8 };
		findSubarrayWithTargetSum(nums,22);

	}


	public static void findSubarrayWithTargetSum(int[] nums, int target)	{
		findSubarrayWithTargetSum(nums,target,0);
		return;
	}

	public static void findSubarrayWithTargetSum(int[] nums, int target, int start_index)	{
		if(start_index==nums.length){
			return;
		}
		findSubarrayWithTargetSumHelper(nums,target, start_index, start_index);

		findSubarrayWithTargetSum(nums,target,start_index+1);
	}

	public static void findSubarrayWithTargetSumHelper(int[] nums, int target, int startIndex, int currIndex)	{
		if(currIndex == nums.length-1 && target!=0){
			return;
		}
		if(target==0){
			int actual_ind = currIndex -1;
			System.out.println(
				"Subarray found between indexes " +startIndex + " and" + actual_ind
			);
			return;
		}
		findSubarrayWithTargetSumHelper(nums,target-nums[currIndex],startIndex,currIndex+1);
	}
}

// to make this only print the first one 
// modify the helper function to return 1 on success and 0 on failure
