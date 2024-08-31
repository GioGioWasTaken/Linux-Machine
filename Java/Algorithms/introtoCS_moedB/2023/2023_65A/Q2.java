/**
 * Q2
 */
public class Q2 {
	public static void main(String[] args) {
		
	}
	public static boolean superInc (int [] arr, int k){
		if(k ==0){
			return true;
		}
		int sum = k;
		for (int i = arr.length-1; i >= 0; i--) {
			if(arr[i] == sum){
				return true;
			} else if(arr[i] <sum){
				sum-=arr[i];
			}
		}
		return false;
	}
}
