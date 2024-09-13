/**
 * Q2
 */
public class Q2 {
	public static void main(String[] args) {
		int[] arr = {2,3,8,27};
		System.out.println(
			superInc(arr, 35)
		);
	}
	public static boolean superInc(int[] arr, int k){
		// this method checks if the given array has a subset of values that add up to k, given that arr is super ascending(every element is bigger then the sum of all former elements)
		int sum = k;
		for(int i = arr.length-1; i >= 0; i--){
			int val = arr[i] ;
			if(val > sum){
				continue;
			} else if(val == sum){
				return true;
			} else if (val <sum){
				sum-=val;
			}
		}
		return false;
	}
}
