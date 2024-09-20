
/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		int [] arr = {1,2,3};
		System.out.println(
			countEqualDiff(arr)
		);
	}

	public static int countEqualDiff(int[] arr){
		int FullSum = arr.length; // a set length is not 0 indexed
		return countEqualDiff(arr,-1, FullSum, 0, 0);

	}
	
	public static int countEqualDiff(int[] arr, int index, int fullSum, int sum2, int currLength) {
		int FullLength = arr.length;

		// Base case: when index reaches array length
		if (index == FullLength) {
			return 0;
		}
		// base case: first iteration. Empty set.
		if(index ==-1){
			int value = 0;
			return 0 + countEqualDiff(arr, index + 1, fullSum, sum2 + value, currLength); // empty set is included
			
		}
		int value = arr[index]; 

		// Calculate sum1 and length2 based on complement of sum2 and currLength
		int sum1 = fullSum - sum2;
		int length2 = FullLength - currLength;

		// Calculate differences between sums and lengths
		int absDiff = Math.abs(sum1 - sum2);
		int lengthDiff = Math.abs(currLength - length2);

		// If the differences match, count the pair
		int count = 0;
		if (absDiff == lengthDiff) {
			System.out.println(
				"Sum1 : " + sum1 + "\n" +
				"Sum2 : " + sum2 + "\n" +
				"Length 1: " + currLength + "\n" + 
				"Length 2: " + length2
			);
			count = 1;
		}

		// Recursive calls: include current element or exclude it
		return count + countEqualDiff(arr, index + 1, fullSum, sum2 + value, currLength + 1) 
		+ countEqualDiff(arr, index + 1, fullSum, sum2, currLength);
	}

}
